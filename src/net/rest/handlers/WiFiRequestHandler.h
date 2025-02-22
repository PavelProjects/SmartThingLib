#ifndef WIFI_RQ_H
#define WIFI_RQ_H

#include "SmartThing.h"
#include "logs/BetterLogger.h"
#include "net/rest/RestController.h"
#include "net/rest/handlers/HandlerUtils.h"
#include "settings/SettingsRepository.h"
#include "net/rest/handlers/RequestHandler.h"

#define WIFI_RQ_PATH "/wifi"

class WiFiRequesthandler : public RequestHandler {
 public:
  WiFiRequesthandler() {};
  virtual ~WiFiRequesthandler() {};

  bool canHandle(AsyncWebServerRequest *request) {
    return request->url().startsWith(WIFI_RQ_PATH) &&
           (request->method() == HTTP_GET || request->method() == HTTP_POST ||
            request->method() == HTTP_OPTIONS);
  }

  AsyncWebServerResponse * processRequest(AsyncWebServerRequest * request) {
    if (request->method() == HTTP_GET) {
      WiFiConfig config = SettingsRepository.getWiFi();

      JsonDocument jsonDoc;
      JsonObject settings = jsonDoc["settings"].to<JsonObject>();
      settings["ssid"] = config.ssid;
      settings["password"] = config.password;
      settings["mode"] = config.mode;

      JsonObject modes = jsonDoc["modes"].to<JsonObject>();
      modes[String(ST_WIFI_STA)] = "Connect to existing point";
      modes[String(ST_WIFI_AP)] = "Create access point";
      modes[String(ST_WIFI_STA_TO_AP)] = "Create AP if can't connect to STA";

      String response;
      serializeJson(jsonDoc, response);

      return request->beginResponse(200, CONTENT_TYPE_JSON, response);
    } else if (request->method() == HTTP_POST) {
      if (_body.length() == 0) {
        return request->beginResponse(400, CONTENT_TYPE_JSON, ERROR_BODY_MISSING);
      }

      JsonDocument jsonDoc;
      deserializeJson(jsonDoc, _body);

      String ssid = jsonDoc["ssid"].as<String>();
      if (ssid.isEmpty()) {
        return request->beginResponse(400, CONTENT_TYPE_JSON, buildErrorJson("Ssid is missing"));
      }
      if (ssid.length() > 32) {
        return request->beginResponse(400, CONTENT_TYPE_JSON,  buildErrorJson("Ssid is too big (32 symbols max)"));
      }
      String password = jsonDoc["password"].as<String>();
      if (password.length() > 0 && password.length() < 8) {
        return request->beginResponse(
            400, CONTENT_TYPE_JSON,
            buildErrorJson("Bad password (it should be blank or contains at least 8 symbols)"));
      }
      int mode = jsonDoc["mode"].as<int>();
      if (mode < ST_WIFI_STA || mode > ST_WIFI_STA_TO_AP) {
        return request->beginResponse(400, CONTENT_TYPE_JSON, buildErrorJson("Unkown wifi mode"));
      }
      WiFiConfig config;
      config.ssid = ssid;
      config.password = password;
      config.mode = static_cast<StWiFiMode>(mode);
      
      if (SettingsRepository.setWiFi(config)) {
        return request->beginResponse(200);
      }
      return request->beginResponse(500, CONTENT_TYPE_JSON, buildErrorJson("Failed to save settings"));
    }
    return nullptr;
  }
};

#endif