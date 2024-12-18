#ifndef SettingsRepository_H
#define SettingsRepository_H

#include <ArduinoJson.h>

#include "logs/BetterLogger.h"
#include "settings/ConfigEntriesList.h"

#define LOGGER_ADDRESS_CONFIG "laddr"
#define GATEWAY_CONFIG "gtw"

struct WiFiConfig {
  String ssid;
  String password;
  uint8_t mode;
};

class SettingsRepositoryClass {
 private:
  ConfigEntriesList _configEntriesList;

  void read(uint16_t address, char * buff, uint16_t length);
  void write(uint16_t address, const char * buff, uint16_t length);

  int getLength(uint8_t index);
  int writeLength(uint8_t index, int length);

  String readData(uint8_t index, const char * defaultValue = "");
  int writeData(uint8_t index, const char * data);

  JsonDocument stringToObject(String& data);
  String objectToString(JsonDocument doc);
 public:
  SettingsRepositoryClass();
  ~SettingsRepositoryClass();

  String getName();
  bool setName(String name);

  WiFiConfig getWiFi();
  bool setWiFi(WiFiConfig settings);
  bool dropWiFi();

  JsonDocument getConfig();
  bool setConfig(JsonDocument conf);
  bool dropConfig();
  JsonDocument getConfigInfoJson();
  ConfigEntriesList * getConfigInfo() {
    return &_configEntriesList;
  }
  bool addConfigEntry(const char* name, const char* caption, ConfigEntryType type = CONFIG_STRING);

  #if ENABLE_HOOKS
  String getHooks();
  bool setHooks(String &data);
  bool dropHooks();
  #endif

  #if ENABLE_ACTIONS_SCHEDULER
  bool setActions(JsonDocument conf);
  JsonDocument getActions();
  #endif

  String exportSettings();
  bool importSettings(String &dump);
  
  void clear();
};

extern SettingsRepositoryClass SettingsRepository;

#endif