#ifndef ACTION_HOOK_H
#define ACTION_HOOK_H

#include "Features.h"

#if ENABLE_ACTIONS 

#include <type_traits>
#include "SmartThing.h"
#include "hooks/impls/Hook.h"
#include "logs/BetterLogger.h"

static const char * _ACTION_HOOK_TAG = "action_hook";
static const char * _actionHookField = "action";

template<class T, typename V, typename std::enable_if<std::is_base_of<Hook<V>, T>::value>::type* = nullptr>
class ActionHook : public T {
  public:
    ActionHook(const char *action, bool readOnly): T(ACTION_HOOK, readOnly) {
      updateAction(action);
    };
    virtual ~ActionHook() {};

    void call(V &value) {
      if (_action == nullptr) {
        return;
      }
      // replace ${value} in _action?
      st_log_debug(_ACTION_HOOK_TAG, "Calling action  %s", _action);
      ActionsManager.call(_action);
    }

    void populateJsonWithCustomValues(JsonDocument &doc, boolean shortJson) const {
      doc[_actionHookField] = _action;
    };

    void updateCustom(JsonObject obj) {
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
    const char * _action;

    bool updateAction(const char * name) {
      if (name == nullptr) {
        st_log_error(_ACTION_HOOK_TAG, "Action name missing!");
        return false;
      }
      const Action * action = ActionsManager.get(name);
      if (action == nullptr) {
        st_log_error(_ACTION_HOOK_TAG, "Can't find action %s", name);
        return false;
      }
      _action = action->name;
      return true;
    }
};

#endif

#endif
