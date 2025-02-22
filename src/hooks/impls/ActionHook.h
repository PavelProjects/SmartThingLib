#ifndef ACTION_HOOK_H
#define ACTION_HOOK_H

#include "Features.h"

#if ENABLE_ACTIONS 

#include <type_traits>
#include "SmartThing.h"
#include "hooks/impls/Hook.h"
#include "logs/BetterLogger.h"

const char * const _ACTION_HOOK_TAG = "action_hook";
const char * const _actionHookField = "action";

template<typename T, CHECK_HOOK_DATA_TYPE>
class ActionHook : public SELECT_HOOK_BASE_CLASS {
  public:
    ActionHook(const char *action): SELECT_HOOK_BASE_CLASS(ACTION_HOOK), _action(nullptr) {
      updateAction(action);
    };
    virtual ~ActionHook() {};

    void call(T &value) {
      if (_action == nullptr) {
        return;
      }
      // todo replace {v} in _action?
      st_log_debug(_ACTION_HOOK_TAG, "Calling action  %s", _action);
      ActionsManager.call(_action);
    }

  protected:
    String customValuesString() {
      return _action;
    }
    
    void populateJsonWithCustomValues(JsonDocument &doc) const {
      doc[_actionHookField] = _action;
    };

    void updateCustom(JsonDocument &obj) {
      if (obj[_actionHookField].is<const char*>()) {
        String newAction = obj[_actionHookField].as<String>();
        if (newAction.isEmpty()) {
          st_log_error(_ACTION_HOOK_TAG, "Action is missing!");
          return;
        }
        if (updateAction(newAction.c_str())) {
          st_log_debug(_ACTION_HOOK_TAG, "New hook action: %s",  _action);
        }
      }
    }

  private:
    char * _action;

    bool updateAction(const char * name) {
      if (name == nullptr || strlen(name) == 0) {
        st_log_error(_ACTION_HOOK_TAG, "Action name missing!");
        return false;
      }
      
      if (_action != nullptr) {
        free(_action);
      }
      _action = (char *) malloc(strlen(name) + 1);
      strcpy(_action, name);

      return true;
    }
};

#endif

#endif
