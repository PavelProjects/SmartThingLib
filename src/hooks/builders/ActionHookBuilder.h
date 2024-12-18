#ifndef ACTION_HOOK_BUILDER_H
#define ACTION_HOOK_BUILDER_H

#include "Features.h"

#if ENABLE_ACTIONS 

#include "hooks/impls/ActionHook.h"
#include "logs/BetterLogger.h"
#include "actions/ActionsManager.h"

const char * const _ACTION_HOOK_BUILDER_TAG = "action_cb_builder";

class ActionHookBuilder {
 public:
  template <typename T>
  static Hook<T>* build(JsonDocument doc) {
    const char* action = doc[_actionHookField];
    if (action == nullptr || strlen(action) == 0) {
      st_log_error(_ACTION_HOOK_BUILDER_TAG, "Action can't be blank!");
      return nullptr;
    }
    return build<T>(action);
  }

  template <typename T>
  static Hook<T>* build(const char * action) {
    st_log_debug(_ACTION_HOOK_BUILDER_TAG, "Action hook data:action=%s", action);
    return new ActionHook<T>(action);
  }
};
#endif

#endif