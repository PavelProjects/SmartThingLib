#include "settings/SettingsRepository.h"
#include "SmartThing.h"

#include <EEPROM.h>

#define EEPROM_LOAD_SIZE 1024

// [offsets][name][wifi][config][hooks][actions]
#define SETTINGS_TEMPLATE "%03d%03d%03d%03d%03d%s%s%s%s%s"
#define LENGTH_PARTITION_SIZE 3
#define DATA_OFFSET 15

const char * const _errorConfigEntryNotFound = "Config entry with name %s not found";

#ifdef ARDUINO_ARCH_ESP32
bool eepromBegin() {
  return EEPROM.begin(EEPROM_LOAD_SIZE);
}
#endif

#ifdef ARDUINO_ARCH_ESP8266
bool eepromBegin() {
  EEPROM.begin(EEPROM_LOAD_SIZE);
  return true;
}
#endif

// todo remove unused parttions when feature disabled
enum DataIndex {
  WIFI_INDEX,
  NAME_INDEX,
  CONFIG_INDEX,
  HOOKS_INDEX,
  ACTIONS_INDEX,
  FIRST_INDEX = WIFI_INDEX,
  LAST_INDEX = ACTIONS_INDEX
};

const char * const _SETTINGS_MANAGER_TAG = "settings_manager";
const char * const _errorEepromOpen = "Failed to open EEPROM";

SettingsRepositoryClass SettingsRepository;

SettingsRepositoryClass::SettingsRepositoryClass() {}
SettingsRepositoryClass::~SettingsRepositoryClass() {}

void SettingsRepositoryClass::clear() {
  if (eepromBegin()) {
    for (int i = 0; i < EEPROM_LOAD_SIZE; i++) {
      EEPROM.write(i, 0);
    }
    EEPROM.commit();
    EEPROM.end();
    st_log_warning(_SETTINGS_MANAGER_TAG, "EEPROM clear");
  } else {
    st_log_error(_SETTINGS_MANAGER_TAG, _errorEepromOpen);
  }
}

void SettingsRepositoryClass::read(uint16_t address, char * buff, uint16_t length) {
  for (uint16_t i = 0; i < length; i++) {
    buff[i] = (char) EEPROM.read(address + i);
  }
  buff[length] = 0;
}

void SettingsRepositoryClass::write(uint16_t address, const char * buff, uint16_t length) {
  for (uint16_t i = 0; i < length; i++) {
    EEPROM.write(address + i, buff[i]);
  }
}

int SettingsRepositoryClass::getLength(uint8_t index) {
  if (index < FIRST_INDEX || index > LAST_INDEX) {
    return -1;
  }
  char buff[LENGTH_PARTITION_SIZE + 1];
  read(index * LENGTH_PARTITION_SIZE, buff, LENGTH_PARTITION_SIZE);
  int result = atoi(buff);
  return result;
}

int SettingsRepositoryClass::writeLength(uint8_t index, int length) {
  if (index < FIRST_INDEX || index > LAST_INDEX) {
    return -1;
  }
  char buff[LENGTH_PARTITION_SIZE + 1];
  sprintf(buff, "%03d", length);
  write(index * LENGTH_PARTITION_SIZE, buff, LENGTH_PARTITION_SIZE);
  return length;
}

String SettingsRepositoryClass::readData(uint8_t index, const char * defaultValue) {
  if (index < FIRST_INDEX || index > LAST_INDEX) {
    return defaultValue;
  }
  if (eepromBegin()) {
    int targetLength = getLength(index);
    if (targetLength == 0) {
      EEPROM.end();
      return defaultValue;
    }

    int offset = DATA_OFFSET;
    for (int i = 0; i < index; i++) {
      offset += getLength(i);
    }

    char buff[targetLength + 1];
    read(offset, buff, targetLength);

    String result = buff;

    EEPROM.end();
    return result;
  } else {
    st_log_error(_SETTINGS_MANAGER_TAG, _errorEepromOpen);
    return defaultValue;
  }
}

int SettingsRepositoryClass::writeData(uint8_t index, const char * data) {
  if (index < FIRST_INDEX || index > LAST_INDEX || data == nullptr) {
    return -1;
  }

  if (eepromBegin()) {
    int tmp = 0, offset = DATA_OFFSET, targetLength = 0, tailLength = 0;
    targetLength = getLength(index);
    if (targetLength < 0) {
      return -1;
    }

    for (int i = 0; i < index; i++) {
      tmp = getLength(i);
      if (tmp < 0) {
        return -1;
      }
      offset += tmp;
    }

    char oldData[targetLength + 1];
    read(offset, oldData, targetLength);
    if (strcmp(oldData, data) == 0) {
      st_log_debug(_SETTINGS_MANAGER_TAG, "Old data equals new, not writing");
      return targetLength;
    }

    for (int i = index + 1; i <= LAST_INDEX; i++) {
      tmp = getLength(i);
      if (tmp < 0) {
        return -1;
      }
      tailLength += tmp;
    }

    char buffTail[tailLength + 1];
    read(offset + targetLength, buffTail, tailLength);
    
    int dataLen = strlen(data);

    write(offset, data, dataLen);
    write(offset + dataLen, buffTail, strlen(buffTail));
    writeLength(index, dataLen);

    EEPROM.commit();
    EEPROM.end();

    return dataLen;
  } else {
    st_log_error(_SETTINGS_MANAGER_TAG, _errorEepromOpen);
    return -1;
  }
}

// todo deprecated
JsonDocument SettingsRepositoryClass::stringToObject(String& data) {
  JsonDocument doc;
  doc.to<JsonObject>();
  if (!data.isEmpty()) {
    String buff, key;
    char tmp;
    bool escaped = false, buildKey = true;
    for (uint8_t i = 0; i < data.length(); i++) {
      tmp = data.charAt(i);

      if (!escaped && tmp == '|') {
        escaped = true;
      } else if (!escaped && tmp == ';') {
        if (buildKey) {
          key = buff;
          buff.clear();
          buildKey = false;
        } else {
          doc[key] = buff;
          key.clear();
          buff.clear();
          buildKey = true;
        }
      } else {
        if (escaped && tmp != ';') {
          buff += '|';
        }
        buff += tmp;
        escaped = false;
      }
    }
    doc[key] = buff;
  }
  return doc;
}

String SettingsRepositoryClass::objectToString(JsonDocument doc) {
  String res = "";
  JsonObject root = doc.as<JsonObject>();
  for (JsonPair pair: root) {
    if (!pair.value().isNull()) {
      String value = pair.value().as<String>();
      if (value.isEmpty()) {
        continue;
      }
      String key = pair.key().c_str();
      key.replace(";", "|;");
      value.replace(";", "|;");

      res += key;
      res += ';';
      res += value;
      res += ';';
    }
  }
  res.remove(res.length() - 1);
  return res;
}

String SettingsRepositoryClass::getName() {
  return readData(NAME_INDEX, ST_DEFAULT_NAME);
}

bool SettingsRepositoryClass::setName(String name) {
  if (name.length() > DEVICE_NAME_LENGTH_MAX) {
    st_log_error(_SETTINGS_MANAGER_TAG, "Name is too big! Max name length=%d", DEVICE_NAME_LENGTH_MAX);
    return false;
  }
  
  if (writeData(NAME_INDEX, name.c_str()) >= 0) {
    return true;
  } else {
    st_log_error(_SETTINGS_MANAGER_TAG, "Name update failed");
    return false;
  }
}

WiFiConfig SettingsRepositoryClass::getWiFi() {
  WiFiConfig settings;

  String settingsStr = readData(WIFI_INDEX);
  if (settingsStr.isEmpty()) {
    st_log_warning(_SETTINGS_MANAGER_TAG, "WiFi config empty");
    return settings;
  }

  String buff;
  char tmp;
  bool ssid = true, escaped = false;
  for (uint8_t i = 0; i < settingsStr.length(); i++) {
    tmp = settingsStr.charAt(i);
    if (!escaped && tmp == '|') {
      escaped = true;
    } else if (!escaped && tmp == ';') {
      if (ssid) {
        settings.ssid = buff;
        ssid = false;
      } else {
        settings.password = buff;
      }
      buff.clear();
    } else {
      if (escaped && tmp != ';') {
        buff += '|';
      }
      buff += tmp;
      escaped = false;
    }
  }
  settings.mode = static_cast<StWiFiMode>(buff.toInt());
  return settings;
}

bool SettingsRepositoryClass::setWiFi(WiFiConfig settings) {
  settings.ssid.replace(";", "|;");
  settings.password.replace(";", "|;");

  char buff[settings.ssid.length() + settings.password.length() + 4];
  sprintf(
    buff,
    "%s;%s;%d",
    settings.ssid.c_str(),
    settings.password.c_str(),
    settings.mode
  );

  bool res = false;
  if (writeData(WIFI_INDEX, buff) > 0) {
    st_log_debug(_SETTINGS_MANAGER_TAG, "WiFi config updated: %s", buff);
    res = true;
  } else {
    st_log_error(_SETTINGS_MANAGER_TAG, "WiFi config update failed");
  }
  return res;
}

bool SettingsRepositoryClass::dropWiFi() {
  bool res = false;
  if (writeData(WIFI_INDEX, "") == 0) {
    st_log_warning(_SETTINGS_MANAGER_TAG, "WiFi config droped");
    res = true;
  } else {
    st_log_error(_SETTINGS_MANAGER_TAG, "WiFi conig drop failed");
  }
  return res;
}

#if ENABLE_HOOKS
bool SettingsRepositoryClass::setHooks(String &data) {
  bool res = false;
  if (writeData(HOOKS_INDEX, data.c_str()) >= 0) {
    st_log_debug(_SETTINGS_MANAGER_TAG, "Hooks data updated");
    res = true;
  } else {
    st_log_error(_SETTINGS_MANAGER_TAG, "Failed to update hooks data");
  }
  return res;
}

String SettingsRepositoryClass::getHooks() {
  return readData(HOOKS_INDEX, "");
}

bool SettingsRepositoryClass::dropHooks() {
  bool res = false;
  if (writeData(CONFIG_INDEX, "")) {
    st_log_debug(_SETTINGS_MANAGER_TAG, "Hooks dropped");
    res = true;
  } else {
    st_log_error(_SETTINGS_MANAGER_TAG, "Failed to drop hooks");
  }
  return res;
}
#endif

#if ENABLE_ACTIONS_SCHEDULER
bool SettingsRepositoryClass::setActions(JsonDocument conf) {
  String data = objectToString(conf);
  bool res = false;
  if (writeData(ACTIONS_INDEX, data.c_str()) >= 0) {
    st_log_debug(_SETTINGS_MANAGER_TAG, "Actions config updated to %s", data.c_str());
    res = true;
  } else {
    st_log_error(_SETTINGS_MANAGER_TAG, "Actions config update failed");
  }
  return res;
}

JsonDocument SettingsRepositoryClass::getActions() {
  String data = readData(ACTIONS_INDEX);
  return stringToObject(data);
}
#endif

#if ENABLE_CONFIG
bool SettingsRepositoryClass::addConfigEntry(const char* name) {
  if (name == nullptr) {
    return false;
  }
  size_t len = strlen(name);
  if (len == 0 || len > MAX_CONFIG_ENTRY_NAME_LENGTH) {
    st_log_warning(_SETTINGS_MANAGER_TAG, "Config entry name is too long! Max length = %d", MAX_CONFIG_ENTRY_NAME_LENGTH);
    return false;
  }
  
  char fixedName[len + 1];
  for (int i = 0; i < len; i++) {
    if (name[i] == ' ' || name[i] == ';') {
      fixedName[i] = '-';
    } else {
      fixedName[i] = name[i];
    }
  }
  fixedName[len] = '\0';

  ConfigEntry * existing = _config.findValue([&](ConfigEntry* current) { return strcmp(current->name(), fixedName) == 0; });
  if (existing != nullptr) {
    st_log_warning(_SETTINGS_MANAGER_TAG, "Config entry %s already exists!", fixedName);
    return false;
  }

  ConfigEntry* entry = new ConfigEntry(fixedName);
  if (_config.append(entry) > -1) {
    st_log_debug(_SETTINGS_MANAGER_TAG, "Added new config entry - %s", fixedName);
    return true;
  } else {
    if (entry != nullptr) {
      delete entry;
    }
    st_log_error(_SETTINGS_MANAGER_TAG, "Failed to add new config entry - %s", fixedName);
    return false;
  }
}

String SettingsRepositoryClass::getConfigJson() {
  String result = "{";
  int lastIndex = _config.size() - 1;

  _config.forEach([&](ConfigEntry * current, int index) {
    char buff[strlen(current->name()) + strlen(current->value()) + 7];
    sprintf(
      buff,
      "\"%s\":\"%s\"%s",
      current->name(),
      current->value(),
      index == lastIndex ? "" : "," 
    );
    result += String(buff);
  });

  result += "}";
  return result;
}


const char * SettingsRepositoryClass::getConfigValue(const char * name) const {
  if (name == nullptr || strlen(name) == 0) {
    return "";
  }

  ConfigEntry * entry = _config.findValue([name](ConfigEntry * current) {
    return strcmp(current->name(), name) == 0;
  });

  if (entry == nullptr) {
    st_log_warning(_SETTINGS_MANAGER_TAG, _errorConfigEntryNotFound, name);
    return "";
  }

  return entry->value();
}

bool SettingsRepositoryClass::setConfigValueWithoutSave(const char * name, const char * value) {
  if (name == nullptr) {
    return false;
  }

  ConfigEntry * entry = _config.findValue([name](ConfigEntry * current) {
    return strcmp(current->name(), name) == 0;
  });

  if (entry == nullptr) {
    st_log_warning(_SETTINGS_MANAGER_TAG, _errorConfigEntryNotFound, name);
    return false;
  }

  entry->setValue(value);
  return true;
}

bool SettingsRepositoryClass::setConfigValue(const char * name, const char * value) {
  if (setConfigValueWithoutSave(name, value)) {
    return saveConfig();
  }
  return false;
}

bool SettingsRepositoryClass::setConfig(JsonDocument conf) {
  if (_config.size() == 0) {
    st_log_error(_SETTINGS_MANAGER_TAG, "No config entries were added");
    return false;
  }
  
  _config.forEach([conf](ConfigEntry * current) {
    if (conf[current->name()].is<String>()) {
      String value = conf[current->name()].as<String>();
      current->setValue(value.isEmpty() ? nullptr : value.c_str());
    } else {
      current->setValue(nullptr);
    }
  });
  
  return saveConfig();
}

bool SettingsRepositoryClass::dropConfig() {
  bool res = false;
  if (writeData(CONFIG_INDEX, "") == 0) {
    _config.forEach([](ConfigEntry * current) {current->setValue(nullptr);});
    st_log_warning(_SETTINGS_MANAGER_TAG, "Config droped");
    callConfigUpdateHook();
    res = true;
  } else {
    st_log_error(_SETTINGS_MANAGER_TAG, "Configuration drop failed");
  }
  return res;
}

bool SettingsRepositoryClass::saveConfig() {
  bool res = false;
  if (_config.size() == 0) {
    return res;
  }

  // todo probably can be optimized
  String data;
  int lastIndex = _config.size() - 1;
  _config.forEach([&](ConfigEntry * entry, int index) {
    if (entry->value() != nullptr && strlen(entry->value()) > 0) {
      String value = entry->value();
      value.replace(";", "|;");

      char buff[strlen(entry->name()) + value.length() + 3];
      sprintf(
        buff,
        "%s;%s%s",
        entry->name(),
        value.c_str(),
        index == lastIndex ? "" : ";"
      );

      data += String(buff);
    }
  });

  if (writeData(CONFIG_INDEX, data.c_str()) >= 0) {
    res = true;
    st_log_debug(_SETTINGS_MANAGER_TAG, "Configuration updated");
    callConfigUpdateHook();
  } else {
    st_log_error(_SETTINGS_MANAGER_TAG, "Configuration update failed");
  }
  return res;
}

void SettingsRepositoryClass::loadConfigValues() {
  String data = readData(CONFIG_INDEX);

  if (data.isEmpty()) {
    return;
  }

  String buff, key;
  char tmp;
  bool escaped = false, buildKey = true;
  for (uint8_t i = 0; i < data.length(); i++) {
    tmp = data.charAt(i);

    if (!escaped && tmp == '|') {
      escaped = true;
    } else if (!escaped && tmp == ';') {
      if (buildKey) {
        key = buff;
        buff.clear();
        buildKey = false;
      } else {
        setConfigValueWithoutSave(key.c_str(), buff.c_str());
        key.clear();
        buff.clear();
        buildKey = true;
      }
    } else {
      if (escaped && tmp != ';') {
        buff += '|';
      }
      buff += tmp;
      escaped = false;
    }
  }
  setConfigValueWithoutSave(key.c_str(), buff.c_str());
}

void SettingsRepositoryClass::onConfigUpdate(ConfigUpdatedHook hook) {
  _configUpdatedHook = hook;
}

void SettingsRepositoryClass::callConfigUpdateHook() {
  st_log_debug(_SETTINGS_MANAGER_TAG, "Config updated, calling hooks");
  #if ENABLE_LOGGER
    LOGGER.updateAddress(SettingsRepository.getConfigValue(LOGGER_ADDRESS_CONFIG));
  #endif
  _configUpdatedHook();
}
#endif

String SettingsRepositoryClass::exportSettings() {
  String result = "";
  if (eepromBegin()) {
    uint8_t tmp = 0;
    int actualSize = DATA_OFFSET;
    for (uint8_t i = 0; i <= LAST_INDEX; i++) {
      actualSize += getLength(i);
    }

    char buff[actualSize + 1];
    for (uint16_t i = 0; i < actualSize; i++) {
      tmp = EEPROM.read(i);
      if (i < DATA_OFFSET && (tmp < '0' || tmp > '9')) {
        tmp = '0';
      }
      buff[i] = (char) tmp;
    }
    buff[actualSize] = 0;
    EEPROM.end(); 
    result = buff;

    result.replace("\n", "\\n");
    result.replace("\t", "\\t");

    return result;
  } else {
    st_log_error(_SETTINGS_MANAGER_TAG, _errorEepromOpen);
    return result;
  }
}

bool SettingsRepositoryClass::importSettings(String &dump) {
  if (dump.length() < LENGTH_PARTITION_SIZE) {
    st_log_error(_SETTINGS_MANAGER_TAG, "Bad dump - too short");
    return false;
  }

  if (dump.charAt(0) == '{' || dump.charAt(0) == '[') {
    st_log_error(_SETTINGS_MANAGER_TAG, "Bad dump - got json?");
    return false;
  }

  bool valid = true;
  uint8_t tmp;
  for (uint8_t i = 0; i < DATA_OFFSET; i++) {
    tmp = dump.charAt(i) - '0';
    if ('0' < tmp || tmp > '9') {
      valid = false;
      break;
    }
  }
  // todo check if dump contains only ascii?
  if (!valid) {
    st_log_error(_SETTINGS_MANAGER_TAG, "Bad dump - worng partitions lengths");
    return false;
  }

  dump.replace("\\n", "\n");
  dump.replace("\\t", "\t");
  
  if (eepromBegin()) {
    st_log_warning(_SETTINGS_MANAGER_TAG, "Writing dump in eeprom (size=%d)", dump.length());
    st_log_debug(_SETTINGS_MANAGER_TAG, "Dump=%s", dump.c_str());

    for (uint16_t i = 0; i < dump.length(); i++) {
      EEPROM.write(i, dump.charAt(i));
    }
    EEPROM.commit();
    EEPROM.end();
    st_log_warning(_SETTINGS_MANAGER_TAG, "Dump write finished");
    return true;
  } else {
    st_log_error(_SETTINGS_MANAGER_TAG, _errorEepromOpen);
    return false;
  }
}