#include "smartthing/watcher/WatchersManager.h"
#include "smartthing/watcher/SensorWatcher.h"
#include "smartthing/watcher/DeviceStateWatcher.h"

#define WATCHERS_LIST_TAG "watchers_list"


namespace Watcher {
    using namespace Configurable::Sensor;
    using namespace Configurable::DeviceState;

    WatchersManager::~WatchersManager() {
        Watcher * current = _head;
        while (current->next != nullptr) {
            current = current->next;
            delete(current->previous);
        }
        delete(current);
    }

    bool WatchersManager::registerSensorWatcher(const Configurable::Sensor::Sensor * sensor, Callback::WatcherCallback<uint16_t> * callback) {
        if (sensor == nullptr) {
            LOGGER.error(WATCHERS_LIST_TAG, "Sensor object is missing, skipping...");
            return false;
        }
        append(new SensorWatcher(sensor, callback));
        LOGGER.debug(WATCHERS_LIST_TAG, "Registered new watcher for sensor %s", sensor->name);
        return true;
    }

    bool WatchersManager::registerDeviceStateWatcher(const DeviceState * state, Callback::WatcherCallback<const char *> * callback) {
        if (state == nullptr) {
            LOGGER.error(WATCHERS_LIST_TAG, "Device state object is missing, skipping...");
            return false;
        }
        append(new DeviceStateWatcher(state, callback));
        LOGGER.debug(WATCHERS_LIST_TAG, "Registered new watcher for device state %s", state->name);
        return true;
    }

    void WatchersManager::check() {
        if (_count == 0) {
            return;
        }
        Watcher * current = _head;
        while (current != nullptr) {
            current->check();
            current = current->next;
        }
    }

    void WatchersManager::append(Watcher * watcher) {
        watcher->next = _head;
        if (_head != nullptr) {
            _head->previous = watcher;
        }
        _head = watcher;
        _count++;
    }
}