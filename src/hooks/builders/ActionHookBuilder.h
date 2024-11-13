#ifndef ACTION_HOOK_BUILDER_H
#define ACTION_HOOK_BUILDER_H

#include "Features.h"

#if ENABLE_ACTIONS 

#include "hooks/impls/ActionHook.h"
#include "logs/BetterLogger.h"
#include "actions/ActionsManager.h"

static const char * _ACTION_HOOK_BUILDER_TAG = "action_cb_builder";

class ActionHookBuilder {
 public:
  template <class B, typename T>
  static Hook<T>* build(JsonObject doc, bool readOnly) {
    if (doc.size() == 0) {
      st_log_error(_ACTION_HOOK_BUILDER_TAG, "Json document is empty!");
      return nullptr;
    }
    const char* action = doc[_actionHookField];
    if (action == nullptr || strlen(action) == 0) {
      st_log_error(_ACTION_HOOK_BUILDER_TAG, "Action can't be blank!");
      return nullptr;
    }

    ActionHook<B, T>* hook = new ActionHook<B, T>(action, readOnly);
    st_log_debug(_ACTION_HOOK_BUILDER_TAG, "Action hook created: action=%s", action);

    return hook;
  }
  static JsonDocument getTemplate() {
    JsonDocument doc;
    JsonObject actionObj = doc[_actionHookField].to<JsonObject>();
    actionObj["required"] = true;
    JsonObject valuesObj = actionObj["values"].to<JsonObject>();

    JsonDocument actions = ActionsManager.toJson();
    JsonArray actionsArray = actions.as<JsonArray>();
    for (JsonObject action: actionsArray) {
      const char * name = action[ACTIONS_JSON_NAME];
      valuesObj[name] = action[ACTIONS_JSON_CAPTION];
    }
    return doc;
  }
};
#endif

#endif