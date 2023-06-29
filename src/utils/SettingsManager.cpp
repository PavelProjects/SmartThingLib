#include <utils/SettingsManager.h>
#include <EEPROM.h>

#define GROUP_CONFIG "cg"
#define GROUP_WIFI "wf"
#define GROUP_STATE "st"
#define DEVICE_NAME "dn"

SettingsManager STSettings;

SettingsManager::SettingsManager() {}

SettingsManager::~SettingsManager() {
    _settings.garbageCollect();
}

void SettingsManager::loadSettings() {
    LOGGER.info(SETTINGS_MANAGER_TAG, "Loading data from eeprom...");
    const char * loaddedSettings = loadFromEeprom();
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
    saveSettings();
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

const char * SettingsManager::loadFromEeprom() {
    if (EEPROM.begin(EEPROM_LOAD_SIZE)) {
        String data = "{";
        uint8_t val;
        bool completed = false;
        for (int i = 0; i < EEPROM_LOAD_SIZE; i++){
            val = EEPROM.read(i);
            if (isAscii(val)) {
                if (val == '\n') {
                    completed = true;
                    break;
                }
                data += (char) val;
            }
        }
        EEPROM.commit();

        if (!completed) {
            LOGGER.error(SETTINGS_MANAGER_TAG, "Settings string not completed. Missing \\n ?");
            LOGGER.error(SETTINGS_MANAGER_TAG, "%s", data.c_str());
            return "";
        }

        data += "}";

        LOGGER.debug(SETTINGS_MANAGER_TAG, "Loaded from eeprom: %s [%u]", data.c_str(), data.length());
        return data.c_str();
    } else {
        LOGGER.error(SETTINGS_MANAGER_TAG, "Failed to open EEPROM");
        return "";
    }
}

void SettingsManager::removeIfEmpty(const char * group) {
    if (_settings[group].size() == 0) {
        _settings.remove(group);
        LOGGER.debug(SETTINGS_MANAGER_TAG, "Removed group %s from settings - it's empty", group);
    }
}

void SettingsManager::saveSettings() {
    removeIfEmpty(GROUP_WIFI);
    removeIfEmpty(GROUP_CONFIG);
    removeIfEmpty(GROUP_STATE);
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
        LOGGER.error(SETTINGS_MANAGER_TAG, "Settings are too long! Expected less then %d, got %d", EEPROM_LOAD_SIZE, data.length());
        return;
    }

    if (EEPROM.begin(EEPROM_LOAD_SIZE)) {
        LOGGER.debug(SETTINGS_MANAGER_TAG, "Saving settings (length [%u]): %s", data.length(), data.c_str());
        for (int i = 0; i < data.length(); i++) {
            EEPROM.write(i, data.charAt(i));
        }

        EEPROM.commit();
        LOGGER.info(SETTINGS_MANAGER_TAG, "Settings saved");
    } else {
       LOGGER.error(SETTINGS_MANAGER_TAG, "Failed to open EEPROM");
    }
}

void SettingsManager::removeSetting(const char * name) {
    if (name == SSID_SETTING || name == PASSWORD_SETTING || name == GROUP_WIFI) {
        LOGGER.warning(SETTINGS_MANAGER_TAG, "U can't remove Wifi credits with this function! Use dropWifiCredits insted.");
        return;
    }
    _settings.remove(name);
}

void SettingsManager::dropAll() {
    _settings.clear();
    clear();
}

void SettingsManager::dropWifiCredits() {
    _settings.remove(GROUP_WIFI);
}

JsonObject SettingsManager::getOrCreateObject(const char * name) {
    if (_settings.containsKey(name)){
        return _settings[name];
    }
    LOGGER.debug(SETTINGS_MANAGER_TAG, "Creating new nested object %s", name);
    return _settings.createNestedObject(name);
}

JsonObject SettingsManager::getConfig() {
    return getOrCreateObject(GROUP_CONFIG);
}

JsonObject SettingsManager::getState() {
    return getOrCreateObject(GROUP_STATE);
}

JsonObject SettingsManager::getWiFi() {
    return getOrCreateObject(GROUP_WIFI);
} 

void SettingsManager::setDeviceName(const char * name) {
    _settings[DEVICE_NAME] = name;
}

const char * SettingsManager::getDeviceName() {
    if (_settings.containsKey(DEVICE_NAME)) {
        return _settings[DEVICE_NAME];
    }
    return "";
}

const JsonObject SettingsManager::getAllSettings() {
    return _settings.to<JsonObject>();
}