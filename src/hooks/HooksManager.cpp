#include "hooks/HooksManager.h"

#if ENABLE_HOOKS

#include <type_traits>

#include "sensors/SensorsManager.h"
#include "hooks/builders/HooksBuilder.h"
#include "hooks/watcher/Watcher.h"
#include "settings/SettingsRepository.h"

#if ENABLE_LOGGER
  const char * const _HOOKS_MANAGER_TAG = "hooks_manager";

  const char * const _errorSensorNameMissing = "Sensor name is missing";
  const char * const _errorSensorObjectMissing = "Sensor object is missing";
  const char * const _errorNoSuchSensor = "No such sensor";
#endif

HooksManagerClass HooksManager;

int HooksManagerClass::add(const char * sensorName, const char * data) {
  SensorType type = SensorsManager.getSensorType(sensorName);
  if (type == UNKNOWN_SENSOR) {
    st_log_error(_HOOKS_MANAGER_TAG, _errorNoSuchSensor);
    return -1;
  }

  #if ENABLE_TEXT_SENSORS
  if (type == TEXT_SENSOR) {
    return HooksManager.add<TEXT_SENSOR_DATA_TYPE>(SensorsManager.getSensor<TEXT_SENSOR_DATA_TYPE>(sensorName), data);
  }
  #endif
  #if ENABLE_NUMBER_SENSORS 
  if (type == NUMBER_SENSOR) {
    return HooksManager.add<NUMBER_SENSOR_DATA_TYPE>(SensorsManager.getSensor<NUMBER_SENSOR_DATA_TYPE>(sensorName), data);
  }
  #endif
  
  st_log_error(_HOOKS_MANAGER_TAG, "This sensor type is not supported");
  return -1;
}

template<typename T>
int HooksManagerClass::add(const Sensor<T> * sensor, const char * data) {
  if (sensor == nullptr) {
    st_log_error(_HOOKS_MANAGER_TAG, _errorSensorObjectMissing);
    return -1;
  }

  if (data == nullptr || strlen(data) == 0) {
    st_log_error(_HOOKS_MANAGER_TAG, "Hook's data string can't be empty");
    return -1;
  }

  int id = -1;
  Hook<T> * hook = HooksBuilder::build<T>(data);
  if (hook != nullptr) {
    id = add<T>(sensor, hook);
  }
  
  if (id == -1) {
    st_log_error(_HOOKS_MANAGER_TAG, "Failed to build hook from string: %s", data);
    
    if (hook != nullptr) {
      delete hook;
    }
  }

  return id;
}

template <typename T>
int HooksManagerClass::add(const Sensor<T> *sensor, Hook<T> *hook) {
  if (sensor == nullptr) {
    st_log_error(_HOOKS_MANAGER_TAG, _errorSensorObjectMissing);
    return -1;
  }
  if (hook == nullptr) {
    st_log_error(_HOOKS_MANAGER_TAG, "Hook is missing, skipping...");
    return -1;
  }

  Watcher<T> *watcher = getWatcherOrCreate<T>(sensor);
  if (watcher == nullptr) {
    st_log_error(_HOOKS_MANAGER_TAG, "Failed to get watcher!");
    return -1;
  }

  if (!watcher->add(hook)) {
    st_log_error(_HOOKS_MANAGER_TAG, "Failed to add hook in watcher");
    return -1;
  }
  _hooksCount++;
  st_log_info(_HOOKS_MANAGER_TAG, "Added new hook(id=%d) for sensor %s", hook->getId(), sensor->name());

  return hook->getId();
}

template <typename T>
Watcher<T> *HooksManagerClass::getWatcherOrCreate(const Sensor<T> *sensor) {
  if (sensor == nullptr) {
    st_log_error(_HOOKS_MANAGER_TAG, _errorSensorObjectMissing);
    return nullptr;
  }

  auto it = getWatcherBySensorName<T>(sensor->name());
  if (it == getWatchersList<T>()->end()) {
    st_log_debug(_HOOKS_MANAGER_TAG, "Creating new watcher for sensor %s", sensor->name());
    Watcher<T> *watcher = new Watcher<T>(sensor);
    getWatchersList<T>()->push_back(watcher);
    st_log_debug(_HOOKS_MANAGER_TAG, "Added new watcher for sensor %s", sensor->name());
    return watcher;
  } else {
    return *it;
  }
}

bool HooksManagerClass::remove(const char * name, int id) {
  SensorType type = SensorsManager.getSensorType(name);
  if (type == UNKNOWN_SENSOR) {
    st_log_error(_HOOKS_MANAGER_TAG, _errorNoSuchSensor);
    return -1;
  }

  #if ENABLE_NUMBER_SENSORS
  if (type == NUMBER_SENSOR) {
    return remove<NUMBER_SENSOR_DATA_TYPE>(name, id);
  } 
  #endif
  #if ENABLE_TEXT_SENSORS
  if (type == TEXT_SENSOR) {
    return remove<TEXT_SENSOR_DATA_TYPE>(name, id);
  }
  #endif

  st_log_error(_HOOKS_MANAGER_TAG, "No such sensor");
  return -1;
}

template <typename T>
bool HooksManagerClass::remove(const char *name, int id) {
  st_log_warning(_HOOKS_MANAGER_TAG, "Trying to delete sensor [%s]'s hook id=%d", name, id);
  auto it = getWatcherBySensorName<T>(name);
  if (it == getWatchersList<T>()->end()) {
    return false;
  }
  
  Watcher<T> * watcher = *it;
  if (!watcher->removeHook(id)) {
    return false;
  }

  _hooksCount--;
  st_log_warning(_HOOKS_MANAGER_TAG,
                 "Hook № %d of sensor [%s] was deleted", id, name);
  if (watcher->haveHooks()) {
    return true;
  }
  st_log_debug(_HOOKS_MANAGER_TAG,
               "No hooks left for sensor [%s], removing watcher!",
               name);

  delete watcher;
  getWatchersList<T>()->erase(it);

  st_log_warning(_HOOKS_MANAGER_TAG, "Watcher for sensor [%s] removed!", name);
  return true;
}

bool HooksManagerClass::update(JsonDocument doc) {
  const char * sensor = doc["sensor"];
  SensorType type = SensorsManager.getSensorType(sensor);
  if (type == UNKNOWN_SENSOR) {
    st_log_error(_HOOKS_MANAGER_TAG, _errorNoSuchSensor);
    return -1;
  }

  JsonDocument hookObject = doc["hook"];
  if (hookObject.size() == 0) {
    st_log_error(_HOOKS_MANAGER_TAG, "Hook object is missing!");
    return false;
  }
  if (!hookObject[_idHookField].is<JsonVariant>()) {
    st_log_error(_HOOKS_MANAGER_TAG, "Hook id property is missing!");
    return false;
  }

  #if ENABLE_NUMBER_SENSORS
    if (type == NUMBER_SENSOR) {
      return update<NUMBER_SENSOR_DATA_TYPE>(sensor, hookObject);
    }
  #endif
  #if ENABLE_TEXT_SENSORS
    if (type == TEXT_SENSOR) {
      return update<TEXT_SENSOR_DATA_TYPE>(sensor, hookObject);
    }
  #endif

  st_log_error(_HOOKS_MANAGER_TAG, "No such sensor");
  return false;
}

template <typename T>
bool HooksManagerClass::update(const char *name, JsonDocument &hookObject) {
  if (!hookObject[_idHookField].is<JsonVariant>()) {
    st_log_error(_HOOKS_MANAGER_TAG,
                 "Id value in hook object is missing!");
    return false;
  }

  int id = hookObject[_idHookField];
  Hook<T> *hook = getHookFromWatcher<T>(name, id);
  if (hook == nullptr) {
    return false;
  }
  if (hook->isReadonly()) {
    st_log_error(_HOOKS_MANAGER_TAG,
                 "Hook id=%d for sensor [%s] is readonly!", id, name);
    return false;
  }

  st_log_info(_HOOKS_MANAGER_TAG, "Trying to update hook id=%d for sensor [%s]", id, name);

  if (hookObject[_triggerEnabledHookField].is<bool>()) {
    bool enabled = hookObject[_triggerEnabledHookField].as<bool>();
    hook->setTriggerEnabled(enabled);
    st_log_debug(_HOOKS_MANAGER_TAG, "trigger %s", enabled ? "enabled" : "disabled");
  }

  hook->setCompareType(hookObject[_compareTypeHookField].as<const char*>());
  st_log_debug(
    _HOOKS_MANAGER_TAG,
    "compareType=%s",
    compareTypeToString(hook->getCompareType()).c_str()
  );

  HooksBuilder::parseTrigger(hook, hookObject);

  hook->updateCustom(hookObject);

  st_log_info(_HOOKS_MANAGER_TAG, "Hook id=%d for sensor [%s] was updated!", id, name);
  return true;
}

template <typename T>
Hook<T> *HooksManagerClass::getHookFromWatcher(const char *name, int id) {
  auto watcher = getWatcherBySensorName<T>(name);
  if (watcher == getWatchersList<T>()->end()) {
    return nullptr;
  }
  Hook<T> *hook = (*watcher)->getHookById(id);
  if (hook == nullptr) {
    st_log_warning(_HOOKS_MANAGER_TAG, "Can't find hook id=%d for sensor [%s]", id, name);
    return nullptr;
  }
  return hook;
}

template <typename T>
typename std::list<Watcher<T>*>::iterator HooksManagerClass::getWatcherBySensorName(const char *name) {
  std::list<Watcher<T>*> * list = getWatchersList<T>();
  return std::find_if(list->begin(), list->end(), [name](const Watcher<T> * watcher) {
    return strcmp(watcher->getSensor()->name(), name) == 0;
  });
}

void HooksManagerClass::check() {
  #if ENABLE_NUMBER_SENSORS 
  if (_sensorsWatchers.size() > 0) {
    checkWatchers<NUMBER_SENSOR_DATA_TYPE>();
  }
  #endif
  #if ENABLE_TEXT_SENSORS
  if (_statesWatchers.size() > 0) {
    checkWatchers<TEXT_SENSOR_DATA_TYPE>();
  }
  #endif
}

template <typename T>
void HooksManagerClass::checkWatchers() {
  std::list<Watcher<T>*> * list = getWatchersList<T>();
  for (auto it = list->begin(); it != list->end(); ++it) {
    (*it)->check();
  }
}

boolean HooksManagerClass::call(const char * name, int id, String value) {
  SensorType type = SensorsManager.getSensorType(name);
  if (type == UNKNOWN_SENSOR) {
    st_log_error(_HOOKS_MANAGER_TAG, _errorNoSuchSensor);
    return -1;
  }

  boolean emptyValue = value.isEmpty();
  st_log_info(
    _HOOKS_MANAGER_TAG,
    "Trying to call hook sensor_name=%s, id=%d, value=%s",
    name,
    id,
    emptyValue ? "" : value.c_str()
  );

  #if ENABLE_NUMBER_SENSORS
  if (type == NUMBER_SENSOR) {
    return callWatcherHook<NUMBER_SENSOR_DATA_TYPE>(name, id, emptyValue ? 0 : value.toInt(), emptyValue);
  }
  #endif
  #if ENABLE_TEXT_SENSORS
  if (type == TEXT_SENSOR) {
    return callWatcherHook<TEXT_SENSOR_DATA_TYPE>(name, id, value, emptyValue);
  }
  #endif

  st_log_error(_HOOKS_MANAGER_TAG, "No such sensor");
  return false;
}

template <typename T>
boolean HooksManagerClass::callWatcherHook(const char * name, int id, T value, boolean emptyValue) {
  auto it = getWatcherBySensorName<T>(name);
  if (it == getWatchersList<T>()->end()) {
    st_log_error(_HOOKS_MANAGER_TAG, "Can't find watcher for sensor with name=%s", name);
    return false;
  }
  Watcher<T> * watcher = *it;
  Hook<T> * hook = watcher->getHookById(id);
  if (hook == nullptr) {
    st_log_error(_HOOKS_MANAGER_TAG, "Can't find hook for sensor %s by id=%d", name, id);
    return false;
  }
  const Sensor<T> * sensor = watcher->getSensor();
  if (sensor == nullptr) {
    st_log_error(_HOOKS_MANAGER_TAG, "SENSOR NULLPTR! HOW???");
    return false;
  }
  if (emptyValue) {
    st_log_info(_HOOKS_MANAGER_TAG, "Extracting value and calling hook");
    T v = sensor->provideValue();
    hook->call(v);
  } else {
    st_log_info(_HOOKS_MANAGER_TAG, "Calling hook with provided value");
    hook->call(value);
  }
  return true;
}

void HooksManagerClass::loadFromSettings() {
  String fromSettings = SettingsRepository.getHooks();

  if (fromSettings.isEmpty()) {
    st_log_info(_HOOKS_MANAGER_TAG, "No hooks in settings");
    return;
  }

  bool failedBuild = false;
  int address = 0;
  int dataLength = fromSettings.length();
  const char * data = fromSettings.c_str();

  st_log_debug(_HOOKS_MANAGER_TAG, "Building hooks from settings");
  while(address < dataLength) {
    String name;

    for (; address < dataLength; address++) {
      if (data[address] == '\t') {
        break;
      }
      name += data[address];
    }

    address++;

    SensorType type = SensorsManager.getSensorType(name.c_str());
    if (type == UNKNOWN_SENSOR) {
      st_log_error(_HOOKS_MANAGER_TAG, "Can't find sensor %s", name.c_str());
      st_log_error(_HOOKS_MANAGER_TAG, "FAILED TO LOAD HOOKS FROM SETTINGS");
      return;
    }

    #if ENABLE_NUMBER_SENSORS
    if (type == NUMBER_SENSOR) {
      failedBuild = loadHooks<NUMBER_SENSOR_DATA_TYPE>(SensorsManager.getSensor<NUMBER_SENSOR_DATA_TYPE>(name.c_str()), data, &address, dataLength) || failedBuild;
    }
    #endif
    #if ENABLE_TEXT_SENSORS
    if (type == TEXT_SENSOR) {
      failedBuild = loadHooks<TEXT_SENSOR_DATA_TYPE>(SensorsManager.getSensor<TEXT_SENSOR_DATA_TYPE>(name.c_str()), data, &address, dataLength) || failedBuild;
    }
    #endif

    address++;
  }

  st_log_debug(_HOOKS_MANAGER_TAG, "Hooks loaded! Total count: %d", _hooksCount);

  if (failedBuild) {
    st_log_warning(_HOOKS_MANAGER_TAG, "Have some ghost hooks to delete (Failed build). Trying to save correct hooks list");
    if (saveInSettings()) {
      st_log_warning(_HOOKS_MANAGER_TAG, "Ghost hooks removed");
    }
  }
}

template<typename T>
bool HooksManagerClass::loadHooks(const Sensor<T> * sensor, const char * data, int * address, int length) {
  bool res = false;
  String buff; // todo remove, pass hook length

  for (; (*address) < length; (*address)++) {
    if (data[(*address)] == '\t' || data[(*address)] == '\n') {
      res = add(sensor, buff.c_str()) == -1 || res;
      buff.clear();
    } else {
      buff += data[(*address)];
    }

    if (data[(*address)] == '\n') {
      break;
    }
  }

  return res;
}

bool HooksManagerClass::saveInSettings() {
  st_log_debug(_HOOKS_MANAGER_TAG, "Saving hooks");
  String data = "";

  #if ENABLE_TEXT_SENSORS
    std::list<Watcher<TEXT_SENSOR_DATA_TYPE>*>::iterator itt;
    for (itt = _statesWatchers.begin(); itt != _statesWatchers.end(); ++itt) {
      data += (*itt)->toString();
      data += "\n";
    }
  #endif
  #if ENABLE_NUMBER_SENSORS 
    std::list<Watcher<NUMBER_SENSOR_DATA_TYPE>*>::iterator itn;
    for (itn = _sensorsWatchers.begin(); itn != _sensorsWatchers.end(); ++itn) {
      data += (*itn)->toString();
      data += "\n";
    }
  #endif

  return SettingsRepository.setHooks(data);
}

JsonDocument HooksManagerClass::getSensorHooksJson(const char *name) {
  JsonDocument doc;

  if (name == nullptr || strlen(name) == 0) {
    st_log_error(_HOOKS_MANAGER_TAG, _errorSensorNameMissing);
    doc["error"] = _errorSensorNameMissing;
    return doc;
  }
  SensorType type = SensorsManager.getSensorType(name);
  if (type == UNKNOWN_SENSOR) {
    st_log_error(_HOOKS_MANAGER_TAG, _errorSensorNameMissing);
    doc["error"] = _errorSensorNameMissing;
    return doc;
  }

  #if ENABLE_NUMBER_SENSORS 
  if (type == NUMBER_SENSOR) {
    return getSensorHooksJson<NUMBER_SENSOR_DATA_TYPE>(name);
  } 
  #endif
  #if ENABLE_TEXT_SENSORS
  if (type == TEXT_SENSOR) {
    return getSensorHooksJson<TEXT_SENSOR_DATA_TYPE>(name);
  }
  #endif

  st_log_error(_HOOKS_MANAGER_TAG, "No such sensor");
  return doc;
}

template <typename T>
JsonDocument HooksManagerClass::getSensorHooksJson(const char *name) {
  if (name == nullptr || strlen(name) == 0) {
    st_log_error(_HOOKS_MANAGER_TAG, "Name of sensor is missing!");
  } else {
    auto it = getWatcherBySensorName<T>(name);
    if (it != getWatchersList<T>()->end()) {
      return (*it)->getSensorHooksJson();
    }
  }
  JsonDocument doc;
  return doc;
}

#if ENABLE_TEXT_SENSORS
  template <>
  std::list<Watcher<TEXT_SENSOR_DATA_TYPE>*> *HooksManagerClass::getWatchersList() {
    return &_statesWatchers;
  }
#endif

#if ENABLE_NUMBER_SENSORS
  template <>
  std::list<Watcher<NUMBER_SENSOR_DATA_TYPE>*> *HooksManagerClass::getWatchersList() {
    return &_sensorsWatchers;
  }
#endif

#endif