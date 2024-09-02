#ifndef SettingsManager_H
#define SettingsManager_H

#include <ArduinoJson.h>

#include "logs/BetterLogger.h"

#define SSID_SETTING "ss"
#define PASSWORD_SETTING "ps"
#define WIFI_MODE_SETTING "md"
#define LOGGER_ADDRESS_CONFIG "laddr"
#define GATEWAY_CONFIG "gtw"

#ifndef EEPROM_LOAD_SIZE
#define EEPROM_LOAD_SIZE 2048
#endif

class SettingsManager {
 private:
  JsonDocument _settings;
  String loadFromEeprom();
  bool _loaded = false;

  JsonObject getOrCreateObject(const char* name);
  void removeIfEmpty(const char* group);
  void addDefaultSettings();
  void clear();
 public:
  SettingsManager();
  ~SettingsManager();

  void loadSettings();
  void removeSetting(const char* name);
  void wipeAll();
  bool save();

  JsonObject getConfig();
  void dropConfig();

  JsonObject getWiFi();
  void dropWifiCredits();

  const char * getDeviceName();
  void setDeviceName(String name);

  void setHooks(JsonArray doc);
  JsonArray getHooks();
  void dropAllHooks();

  const JsonDocument exportSettings();
  bool importSettings(JsonDocument doc);

  const JsonDocument getAllSettings();
};

extern SettingsManager STSettings;

#endif