#ifndef HOOKS_RQ_H
#define HOOKS_RQ_H

#include "Features.h"
#if ENABLE_HOOKS 

#include <ArduinoJson.h>

#include "SmartThing.h"
#include "hooks/builders/HooksFactory.h"
#include "logs/BetterLogger.h"
#include "net/rest/handlers/HandlerUtils.h"
#include "net/rest/handlers/RequestHandler.h"

#define HOOKS_RQ_PATH "/hooks"
#define HOOKS_RQ_TAG "hooks_handler"

#define HOOK_NAME_ARG "name"
#define HOOK_OBSERVABLE_TYPE "type"
#define HOOK_ID_ARG "id"

// todo cut off first /hooks?
class HooksRequestHandler : public RequestHandler {
 public:
  HooksRequestHandler(){};
  bool canHandle(AsyncWebServerRequest *request) {
    return request->url().startsWith(HOOKS_RQ_PATH) &&
           (request->method() == HTTP_GET || request->method() == HTTP_PUT || request->method() == HTTP_POST ||
            request->method() == HTTP_DELETE || request->method() == HTTP_OPTIONS);
  };
  AsyncWebServerResponse * processRequest(AsyncWebServerRequest * request) {
    if (request->method() == HTTP_GET) {
      if (request->url().equals("/hooks/templates")) {
        String type = request->arg(HOOK_OBSERVABLE_TYPE);
        if (type.isEmpty()) {
          return request->beginResponse(400, CONTENT_TYPE_JSON,
                      buildErrorJson("Type parameter are missing!"));
        }
        JsonDocument doc = Hook::HooksFactory::getTemplates(type.c_str());
        String response;
        serializeJson(doc, response);
        return request->beginResponse(200, CONTENT_TYPE_JSON, response);
      }
      if (request->url().equals("/hooks/by/observable")) {
        String type = request->arg(HOOK_OBSERVABLE_TYPE);
        String name = request->arg(HOOK_NAME_ARG);

        if (type.isEmpty() || name.isEmpty()) {
          return request->beginResponse(
              400, CONTENT_TYPE_JSON,
              buildErrorJson("Observable type or name args are missing!"));
        }
        JsonDocument doc = HooksManager.getObservableHooksJson(
            type.c_str(), name.c_str());
        String response;
        serializeJson(doc, response);
        return request->beginResponse(200, CONTENT_TYPE_JSON, response);
      }
      if (request->url().equals("/hooks/by/id")) {
        String type = request->arg(HOOK_OBSERVABLE_TYPE);
        String name = request->arg(HOOK_NAME_ARG);
        String id = request->arg(HOOK_ID_ARG);

        if (type.isEmpty() || name.isEmpty() || id.isEmpty()) {
          return request->beginResponse(400, CONTENT_TYPE_JSON,
                      buildErrorJson("Type, name or id args are missing!"));
        }
        JsonDocument doc = HooksManager.getHookJsonById(
            type.c_str(), name.c_str(), id.toInt());
        String response;
        serializeJson(doc, response);
        return request->beginResponse(200, CONTENT_TYPE_JSON, response);
      }
      if (request->url().equals("/hooks/test")) {
        String type = request->arg(HOOK_OBSERVABLE_TYPE);
        String name = request->arg(HOOK_NAME_ARG);
        String id = request->arg(HOOK_ID_ARG);
        String value = request->arg("value");

        if (type.isEmpty() || name.isEmpty() || id.isEmpty()) {
          return request->beginResponse(400, CONTENT_TYPE_JSON,
                      buildErrorJson("Type, name or id args are missing!"));
        }
        if (HooksManager.callHook(type.c_str(), name.c_str(), id.toInt(), value)) {
          return request->beginResponse(200);
        } else {
          return request->beginResponse(500);
        }
      }
      JsonDocument doc = HooksManager.allHooksToJson(false, false);
      String response;
      serializeJson(doc, response);
      return request->beginResponse(200, CONTENT_TYPE_JSON, response);
    }
    if (request->method() == HTTP_POST) {
      if (_body.isEmpty()) {
        return request->beginResponse(400, CONTENT_TYPE_JSON, "Body is missing!");
      }
      int id = HooksManager.createHookFromJson(_body.c_str());
      if (id >= 0) {
        HooksManager.saveHooksToSettings();
        // spritf fails, why?
        JsonDocument doc;
        doc["id"] = id;
        String response;
        serializeJson(doc, response);
        return request->beginResponse(201, CONTENT_TYPE_JSON, response);
      } else {
        return request->beginResponse(500, CONTENT_TYPE_JSON,
                    buildErrorJson("Failed to create hook. Check logs for "
                                   "additional information."));
      }
    }
    if (request->method() == HTTP_PUT) {
      if (_body.isEmpty()) {
        return request->beginResponse(400, CONTENT_TYPE_JSON, buildErrorJson("Body is missing!"));
      }

      JsonDocument doc;
      deserializeJson(doc, _body);
      if (HooksManager.updateHook(doc)) {
        HooksManager.saveHooksToSettings();
        return request->beginResponse(200);
      } else {
        return request->beginResponse(500, CONTENT_TYPE_JSON,
                    buildErrorJson("Failed to update hook. Check logs for "
                                   "additional information."));
      }
    }
    if (request->method() == HTTP_DELETE) {
      String type = request->arg(HOOK_OBSERVABLE_TYPE);
      String name = request->arg(HOOK_NAME_ARG);
      String id = request->arg(HOOK_ID_ARG);

      if (type.isEmpty() || name.isEmpty() || id.isEmpty()) {
        return request->beginResponse(
            400, CONTENT_TYPE_JSON,
            buildErrorJson("Observable type, name or id args are missing!"));
      }

      if (HooksManager.deleteHook(type.c_str(), name.c_str(),
                                          id.toInt())) {
        HooksManager.saveHooksToSettings();
        return request->beginResponse(200);
      } else {
        return request->beginResponse(500, CONTENT_TYPE_JSON,
                    buildErrorJson("Failed to delete hook. Check logs for "
                                   "additional information."));
      }
    }
    
    return nullptr;
  }
};
#endif

#endif