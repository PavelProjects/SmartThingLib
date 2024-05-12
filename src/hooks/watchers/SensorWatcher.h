#ifndef SENSOR_WATCHER_H
#define SENSOR_WATCHER_H

#include "Features.h"
#if ENABLE_SENSORS 

#include "hooks/impls/Hook.h"
#include "hooks/watchers/Watcher.h"
#include "configurable/ConfigurableObjects.h"
#include "logs/BetterLogger.h"

#define SENSOR_WATCHER_TAG "sensor_watcher"
#define SENSOR_WATCHER_TYPE "sensor"

namespace Hook {
class SensorWatcher : public Watcher<int16_t> {
 public:
  SensorWatcher(const Configurable::Sensor::Sensor* sensor)
      : Watcher<int16_t>(sensor, -1){};
  bool check() {
    if (_observable != nullptr) {
      int16_t newValue = _observable->valueProvider();
      if (_oldValue == -1) {
        _oldValue = newValue;
        return false;
      }
      if (newValue != _oldValue) {
        LOGGER.debug(SENSOR_WATCHER_TAG, "Sensor [%s] value changed %d->%d.",
                     _observable->name, _oldValue, newValue);
        callHooks(newValue);
        _oldValue = newValue;
        return true;
      }
    }
    return false;
  };

  const char* getObservableInfo() { return _observable->name; };
};
}  // namespace Hook

#endif
#endif