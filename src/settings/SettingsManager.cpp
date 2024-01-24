#include "settings/SettingsManager.h"
#include "SmartThing.h"

#include <EEPROM.h>

#define GROUP_CONFIG "cg"
#define GROUP_WIFI "wf"
#define DEVICE_NAME "dn"
#define GROUP_CALLBACKS "cb"

SettingsManager STSettings;

SettingsManager::SettingsManager() {}

SettingsManager::~SettingsManager() { _settings.garbageCollect(); }

void SettingsManager::loadSettings() {
  LOGGER.info(SETTINGS_MANAGER_TAG, "Loading data from eeprom...");
  const char* loaddedSettings = loadFromEeprom();
  if (strlen(loaddedSettings) == 0) {
    LOGGER.warning(SETTINGS_MANAGER_TAG, "Settings empty! Adding default");
    addDefaultSettings();
    return;
  }
  deserializeJson(_settings, loaddedSettings);
  _loaded = true;
}

void SettingsManager::addDefaultSettings() {
  _settings[DEVICE_NAME] = ESP.getChipModel();
  save();
}

void SettingsManager::clear() {
  if (EEPROM.begin(EEPROM_LOAD_SIZE)) {
    for (int i = 0; i < EEPROM_LOAD_SIZE; i++) {
      EEPROM.write(i, 0);
    }
    LOGGER.warning(SETTINGS_MANAGER_TAG, "EEprom clear");
  } else {
    LOGGER.error(SETTINGS_MANAGER_TAG, "Failed to open EEPROM");
  }
}

const char* SettingsManager::loadFromEeprom() {
  if (EEPROM.begin(EEPROM_LOAD_SIZE)) {
    String data = "{";
    uint8_t val;
    bool completed = false;
    // todo replace with readString?
    for (int i = 0; i < EEPROM_LOAD_SIZE; i++) {
      val = EEPROM.read(i);
      if (isAscii(val)) {
        if (val == '\n') {
          completed = true;
          break;
        }
        data += (char)val;
      }
    }
    EEPROM.commit();

    if (!completed) {
      LOGGER.error(SETTINGS_MANAGER_TAG,
                   "Settings string not completed. Missing \\n ?");
      LOGGER.error(SETTINGS_MANAGER_TAG, "%s", data.c_str());
      return "";
    }

    data += "}";

    LOGGER.debug(SETTINGS_MANAGER_TAG, "Loaded from eeprom: %s [%u]",
                 data.c_str(), data.length());
    return data.c_str();
  } else {
    LOGGER.error(SETTINGS_MANAGER_TAG, "Failed to open EEPROM");
    return "";
  }
}

void SettingsManager::removeIfEmpty(const char* group) {
  if (_settings[group].size() == 0) {
    _settings.remove(group);
    LOGGER.debug(SETTINGS_MANAGER_TAG,
                 "Removed group %s from settings - it's empty", group);
  }
}

bool SettingsManager::save() {
  LOGGER.info(SETTINGS_MANAGER_TAG, "Saving settings");
  removeIfEmpty(GROUP_WIFI);
  removeIfEmpty(GROUP_CONFIG);
  removeIfEmpty(GROUP_CALLBACKS);
  _settings.garbageCollect();

  String data;
  serializeJson(_settings, data);
  LOGGER.debug(SETTINGS_MANAGER_TAG, "Parsed json: %s", data.c_str());

  if (data == "null") {
    data.clear();
  } else {
    data.remove(0, 1);
    data.remove(data.length() - 1);
    data += "\n";
  }

  if (data.length() > EEPROM_LOAD_SIZE) {
    LOGGER.error(SETTINGS_MANAGER_TAG,
                 "Save failed, data are too long! Expected less then %d, got %d",
                 EEPROM_LOAD_SIZE, data.length());
    return false;
  }

  if (EEPROM.begin(EEPROM_LOAD_SIZE)) {
    // todo replace with write string?
    LOGGER.debug(SETTINGS_MANAGER_TAG, "Wrtining data to EEPROM (length [%u]): %s",
                 data.length(), data.c_str());
    for (int i = 0; i < data.length(); i++) {
      EEPROM.write(i, data.charAt(i));
    }
    EEPROM.commit();
    LOGGER.info(SETTINGS_MANAGER_TAG, "Settings saved");
    return true;
  } else {
    LOGGER.error(SETTINGS_MANAGER_TAG, "Save failed, can't open EEPROM");
    return false;
  }
}

void SettingsManager::removeSetting(const char* name) {
  if (name == SSID_SETTING || name == PASSWORD_SETTING || name == GROUP_WIFI) {
    LOGGER.warning(SETTINGS_MANAGER_TAG,
                   "You can't remove Wifi credits with this function! Use "
                   "dropWifiCredits insted.");
    return;
  }
  _settings.remove(name);
  _settings.garbageCollect();
}

void SettingsManager::dropAll() {
  _settings.clear();
  clear();
}

void SettingsManager::dropWifiCredits() { _settings.remove(GROUP_WIFI); }

JsonObject SettingsManager::getOrCreateObject(const char* name) {
  if (_settings.containsKey(name)) {
    return _settings[name];
  }
  LOGGER.debug(SETTINGS_MANAGER_TAG, "Creating new nested object %s", name);
  return _settings.createNestedObject(name);
}

JsonObject SettingsManager::getConfig() {
  return getOrCreateObject(GROUP_CONFIG);
}

void SettingsManager::dropConfig() {
  if (_settings.containsKey(GROUP_CONFIG)) {
    _settings.remove(GROUP_CONFIG);
    LOGGER.warning(SETTINGS_MANAGER_TAG, "All config values were removed!");
  } else {
    LOGGER.debug(SETTINGS_MANAGER_TAG, "Config settings not exists");
  }
}

JsonObject SettingsManager::getWiFi() { return getOrCreateObject(GROUP_WIFI); }

void SettingsManager::setDeviceName(const char* name) {
  _settings[DEVICE_NAME] = name;
}

String SettingsManager::getDeviceName() {
  if (_settings.containsKey(DEVICE_NAME)) {
    return _settings[DEVICE_NAME];
  }
  return "";
}

void SettingsManager::setCallbacks(JsonArray doc) {
  _settings[GROUP_CALLBACKS] = doc;
}

JsonArray SettingsManager::getCallbacks() {
  if (_settings.containsKey(GROUP_CALLBACKS)) {
    return _settings[GROUP_CALLBACKS];
  }
  return _settings.createNestedArray(GROUP_CALLBACKS);
}

void SettingsManager::dropAllCallbacks() {
  _settings.remove(GROUP_CALLBACKS);
  _settings.garbageCollect();
}

const DynamicJsonDocument SettingsManager::exportSettings() {
  DynamicJsonDocument doc(JSON_SETTINGS_DOC_SIZE);
  doc[GROUP_CONFIG] = getConfig();
  doc[GROUP_CALLBACKS] = getCallbacks();
  doc[DEVICE_NAME] = getDeviceName();
  return doc;
}

bool SettingsManager::importSettings(DynamicJsonDocument doc) {
  if (doc.size() == 0) {
    LOGGER.info(SETTINGS_MANAGER_TAG, "Empty settings json!");
    return false;
  }
  bool res = true;
  String old;
  serializeJson(_settings, old);
  LOGGER.debug(SETTINGS_MANAGER_TAG, "Old settings save: %s", old.c_str());

  String name = doc[DEVICE_NAME];
  if (!name.isEmpty()) {
    if (name.length() > DEVICE_NAME_LENGTH_MAX) {
      res = false;
      LOGGER.error(SETTINGS_MANAGER_TAG, "Device name is too long! Max length: %d", DEVICE_NAME_LENGTH_MAX);
    } else {
      LOGGER.info(SETTINGS_MANAGER_TAG, "New name: %s", name.c_str());
      _settings[DEVICE_NAME] = name;
    }
  }
  
  if (doc[GROUP_CONFIG].size() > 0 && !doc[GROUP_CONFIG].is<JsonObject>()) {
    LOGGER.error(SETTINGS_MANAGER_TAG, "Expected %s to be JsonObject!", GROUP_CONFIG);
    res = false;
  } else {
    _settings[GROUP_CONFIG] = doc[GROUP_CONFIG];
  }
  if (doc[GROUP_CALLBACKS].size() > 0 && !doc[GROUP_CALLBACKS].is<JsonArray>()) {
    LOGGER.error(SETTINGS_MANAGER_TAG, "Expected %s to be JsonArray!", GROUP_CALLBACKS);
    res = false;
  } else {
    _settings[GROUP_CALLBACKS] = doc[GROUP_CALLBACKS];
  }

  if (res) {
    res = save();
  }

  if (!res) {
    LOGGER.info(SETTINGS_MANAGER_TAG, "Import failed, rollback old settings");
    deserializeJson(_settings, old);
    save();
  }

  return res;
}

const DynamicJsonDocument SettingsManager::getAllSettings() {
  return _settings;
}