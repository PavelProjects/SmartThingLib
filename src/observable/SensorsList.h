#ifndef SENSORS_LIST_H
#define SENSORS_LIST_H

#include "Features.h"
#if ENABLE_SENSORS 

#include <Arduino.h>
#include <ArduinoJson.h>

#include "logs/BetterLogger.h"
#include "observable/ObservableObjects.h"
#include "utils/List.h"

const char * const _SENSORS_LIST_TAG = "sensors_list";

class SensorsList : public List<Sensor> {
 public:
  bool add(const char* name,
           ObservableObject<SENSOR_DATA_TYPE>::ValueProviderFunction
               valueProvider) {
    return add(name, TYPE_CUSTOM, valueProvider);
  };
  bool addDigital(const char* name, int pin) {
    if (pin < 0) {
      st_log_warning(_SENSORS_LIST_TAG,
                     "Pin value can't be negative for sensor! Skipping...");
      return false;
    }
    return add(name, TYPE_DIGITAL, [pin]() {
      if (pin > 0) {
        return digitalRead(pin);
      }
      return -1;
    });
  };
  bool addAnalog(const char* name, int pin) {
    if (pin < 0) {
      st_log_warning(_SENSORS_LIST_TAG,
                     "Pin value can't be negative for sensor! Skipping...");
      return false;
    }
    return add(name, TYPE_ANALOG, [pin]() {
      if (pin > 0) {
        return (int)analogRead(pin);
      }
      return -1;
    });
  };

  JsonDocument getValues() {
    JsonDocument doc;
    forEach([&](Sensor* current) {
      doc[current->name] = current->valueProvider();
    });
    return doc;
  };
  JsonDocument getTypes() {
    JsonDocument doc;
    forEach([&](Sensor* current) {
      doc[current->name] = sensorTypeName(current->sensorType);
    });
    return doc;
  }

  const Sensor* findSensor(const char* name) {
    return findValue(
      [&](Sensor* current) {
        return strcmp(current->name, name) == 0;
      }
    );
  };

 private:
  bool add(const char* name, SensorType type,
           ObservableObject<SENSOR_DATA_TYPE>::ValueProviderFunction
               valueProvider) {
    if (findSensor(name) != nullptr) {
      st_log_warning(_SENSORS_LIST_TAG,
                     "Sensor with name %s already exist! Skipping...", name);
      return false;
    }
    Sensor* sensor = new Sensor();
    sensor->name = name;
    sensor->valueProvider = valueProvider;
    sensor->sensorType = type;
    if (append(sensor) > -1) {
      st_log_debug(_SENSORS_LIST_TAG, "Added new sensor %s", name);
      return true;
    } else {
      if (sensor != nullptr) {
        delete sensor;
      }
      st_log_error(_SENSORS_LIST_TAG, "Failed to add new sensor %s", name);
      return false;
    }
  };
};

#endif

#endif