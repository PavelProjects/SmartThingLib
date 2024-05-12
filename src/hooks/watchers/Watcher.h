#ifndef WATCHER_H
#define WATCHER_H

#include <ArduinoJson.h>

#include <functional>

#include "hooks/impls/Hook.h"
#include "configurable/ConfigurableObjects.h"
#include "logs/BetterLogger.h"
#include "utils/List.h"

#define WATCHER_INFO_DOC_SIZE 128
#define WATCHER_TAG "watcher"

/*
    Класс наблюдатель за объектами
    T - тип данных, которые хранит в себе объект
*/

template <typename T>
class Watcher {
 public:
  Watcher(const Configurable::ConfigurableObject<T> *observable, T initialValue)
      : _observable(observable),
        _oldValue(initialValue),
        _hookIdSequence(0){};

  virtual bool check() = 0;
  virtual const char *getObservableInfo() = 0;

  DynamicJsonDocument getObservableHooksJson() {
    return getObservableHooksJson(false, false);
  }

  DynamicJsonDocument getObservableHooksJson(bool ignoreReadOnly, bool shortJson) {
    if (_hooks.size() == 0) {
      LOGGER.debug(WATCHER_HOOK_TAG, "No hook's, creating empty array");
      DynamicJsonDocument doc(0);
      doc.to<JsonArray>();
      return doc;
    }
    DynamicJsonDocument doc(HOOK_INFO_DOC_SIZE * _hooks.size());
    _hooks.forEach([&](Hook::Hook<T> *current) {
      if (current == nullptr || ignoreReadOnly && current->isReadonly()) {
        return;
      }
      doc.add(current->toJson(shortJson));
    });
    return doc;
  };

  DynamicJsonDocument toJson(bool ignoreReadOnly, bool shortJson) {
    if (_hooks.size() == 0) {
      DynamicJsonDocument doc(0);
      return doc;
    }
    DynamicJsonDocument hooks =
        getObservableHooksJson(ignoreReadOnly, shortJson);
    DynamicJsonDocument doc(HOOK_INFO_DOC_SIZE * _hooks.size() + 128);
    doc["observable"] =
        ((Configurable::ConfigurableObject<T> *)_observable)->toJson();
    doc["hooks"] = hooks;
    return doc;
  }

  bool addHook(Hook::Hook<T> *hook) {
    if (hook == nullptr) {
      LOGGER.error(WATCHER_TAG, "Hook is missing!");
      return false;
    }

    if (hook->isReadonly()) {
      LOGGER.debug(WATCHER_TAG, "Hook is readonly, skipping id generation");
      hook->setId(-1);
    } else if (hook->getId() < 0) {
      int id = getNextHookId();
      if (id < 0) {
        LOGGER.error(WATCHER_TAG, "Failed to generate new id for hook");
        return false;
      }
      LOGGER.debug(WATCHER_TAG, "Generated new hook id=%d", id);
      hook->setId(id);
    } else if (getHookById(hook->getId()) != nullptr) {
      LOGGER.error(WATCHER_TAG, "Hook with id=%d already exists!",
                   hook->getId());
      return false;
    }

    _hooks.append(hook);
    LOGGER.debug(WATCHER_TAG, "New hook added id=%d", hook->getId());
    return true;
  };

  bool removeHook(int id) {
    if (id < 0) {
      LOGGER.error(WATCHER_TAG, "Failed to remove hook - id negative!");
      return false;
    }
    Hook::Hook<T> *hook = getHookById(id);
    if (hook == nullptr) {
      LOGGER.error(WATCHER_TAG,
                   "Failed to remove hook - can't find hook with id %d",
                   id);
      return false;
    }
    if (hook->isReadonly()) {
      LOGGER.error(WATCHER_TAG, "This hook is readonly!");
      return false;
    }
    if (_hooks.remove(hook)) {
      delete hook;
      return true;
    }
    LOGGER.error(WATCHER_TAG, "Failed to remove hook from list");
    return false;
  }

  Hook::Hook<T> *getHookById(int id) {
    if (id < 0) {
      return nullptr;
    }
    return _hooks.findValue([&](Hook::Hook<T> *hook) {
      return hook->getId() == id;
    });
  }

  void callHooks(T &value) {
    _hooks.forEach([&](Hook::Hook<T> *current) {
      if (current != nullptr && current->accept(value)) {
        LOGGER.debug(WATCHER_TAG, "Calling hook [id=%d]", current->getId());
        current->call(value);
      }
    });
  };

  const Configurable::ConfigurableObject<T> *getObservable() {
    return _observable;
  };

  bool haveHooks() { return _hooks.size() != 0; }

  uint8_t hooksCount() { return _hooks.size(); }

 protected:
  const Configurable::ConfigurableObject<T> *_observable;
  T _oldValue;
  List<Hook::Hook<T>> _hooks;

 private:
  int _hookIdSequence;

  int getNextHookId() {
    bool res = false;
    uint8_t attempts = 20;
    while (!res && attempts != 0) {
      _hookIdSequence++;
      res = getHookById(_hookIdSequence) == nullptr;
      attempts--;
    }
    if (attempts == 0) {
      return -1;
    }
    return _hookIdSequence;
  }
};
#endif