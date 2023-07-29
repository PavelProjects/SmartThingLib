#ifndef CONFIG_ENTRIES_LIST 
#define CONFIG_ENTRIES_LIST 

#include <ArduinoJson.h>
#include "smartthing/utils/List.h"
#define CONFIG_ENTRIES_LIST_TAG "config_entries_list"

namespace Configurable {
    namespace Config {
        struct ConfigEntry {
            ConfigEntry(const char * n, const char * c, const char * t): 
                name(n), caption(c), type(t){};
            const char * name;
            const char * caption;
            const char * type;
        };

        class ConfigEntriesList:public List<ConfigEntry> {
            public:
                bool add(const char * name, const char * caption, const char * type) {
                    if (findConfigEntry(name) != nullptr) {
                        LOGGER.warning(CONFIG_ENTRIES_LIST_TAG, "Config entry %s already exists!", name);
                        return false;
                    }
                    ConfigEntry * entry = new ConfigEntry(name, caption, type);
                    if (append(entry) > -1 ) {
                        LOGGER.debug(CONFIG_ENTRIES_LIST_TAG, "Added new config entry - %s:%s", name, caption);
                        return true;
                    } else {
                        if (entry != nullptr) {
                            delete(entry);
                        }
                        LOGGER.error(CONFIG_ENTRIES_LIST_TAG, "Failed to add new config entry - %s:%s", name, caption);
                        return false;
                    }
                };
                DynamicJsonDocument getInfo() {
                    DynamicJsonDocument doc(size() * 64);
                    forEach([&](ConfigEntry * current) {
                        JsonObject obj = doc.createNestedObject(current->name);
                        obj["caption"] = current->caption;
                        obj["type"] = current->type;
                    });
                    return doc;
                }
            private:
                const ConfigEntry * findConfigEntry(const char * name) {
                    return findValue([&](ConfigEntry * current) {
                        return strcmp(current->name, name) == 0;
                    });
                };

        };
    }
}

#endif