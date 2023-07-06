#ifndef DEVICE_STATE_WATCHER_H
#define DEVICE_STATE_WATCHER_H

#include "smartthing/watcher/Watcher.h"
#include "smartthing/watcher/callback/WatcherCallback.h"
#include "smartthing/configurable/ConfigurableObjects.h"
#include "smartthing/logs/BetterLogger.h"

#define DEVICE_STATE_WATCHER_TAG "device_state_watcher"

using namespace Configurable::Sensor;

namespace Watcher {
    class DeviceStateWatcher: public Watcher {
        public:
            DeviceStateWatcher(const Configurable::DeviceState::DeviceState * deviceState, Callback::WatcherCallback<const char *> * callback): 
                _observable(deviceState), _callback(callback){};
            bool check() {
                if (_observable != nullptr) {
                    const char * newValue = _observable->valueGenerator();
                    if (_oldValue == nullptr) {
                        copyValue(newValue);
                        return false;
                    }
                    if (strcmp(newValue, _oldValue) != 0) {
                        LOGGER.debug(
                            DEVICE_STATE_WATCHER_TAG, 
                            "Device state %s value changed %s->%s. Calling callback.", 
                            _observable->name, _oldValue, newValue
                        );
                        _callback->call(&newValue);
                        copyValue(newValue);
                        return true;
                    }
                }
                return false;
            };

            StaticJsonDocument<WATCHERS_INFO_DOC_SIZE> getInfo() {
                StaticJsonDocument<WATCHERS_INFO_DOC_SIZE> doc;
                doc["type"] = DEVICE_STATE_WATCHER_TAG;
                doc["stateName"] = _observable->name;
                doc["callback"] = _callback->getInfo();
                return doc;
            };

        protected:
            const Configurable::DeviceState::DeviceState * _observable;
            char * _oldValue = nullptr;
            Callback::WatcherCallback<const char *> * _callback;
            void copyValue(const char * value) {
                if (_oldValue != nullptr) {
                    delete(_oldValue);
                }
                int size = strlen(value) + 1;
                _oldValue = new char[size];
                strncpy(_oldValue, value, size);
                _oldValue[size - 1] = '\0';
            }
    };
}

#endif