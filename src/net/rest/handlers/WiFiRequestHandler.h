#ifndef WIFI_RQ_H
#define WIFI_RQ_H

#include <WebServer.h>
#include "utils/SettingsManager.h"
#include "net/logs/BetterLogger.h"
#include "net/rest/handlers/HandlerUtils.h"
#include "net/rest/RestController.h"

#define WIFI_LOG_TAG "wifi_handler"
#define WIFI_RQ_PATH "/wifi"

class WiFiRequesthandler: public RequestHandler {
    public:
        WiFiRequesthandler(SettingsManager * settingsManager, RestController::HandlerFunction * wifiUpdatedHandler): 
            _settingsManager(settingsManager), _wifiUpdatedHandler(wifiUpdatedHandler) {};

        bool canHandle(HTTPMethod method, String uri) {
            return uri.startsWith(WIFI_RQ_PATH) && 
                (method == HTTP_GET || HTTP_POST || HTTP_OPTIONS);
        }

        bool handle(WebServer& server, HTTPMethod requestMethod, String requestUri) {
            if (requestMethod == HTTP_OPTIONS) {
                server.sendHeader("Access-Control-Allow-Origin", "*");
                server.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
                server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
                server.send(200);
                return true; 
            }

            String body = server.arg("plain");
            BetterLogger::logRequest(WIFI_LOG_TAG, http_method_str(requestMethod), requestUri.c_str(), body.c_str());
            
            server.sendHeader("Access-Control-Allow-Origin", "*");
            if (requestMethod == HTTP_GET) {
                //todo hide password smh
                JsonObject wifiSettings = _settingsManager->getSettings(GROUP_WIFI);

                DynamicJsonDocument jsonDoc(1028);
                jsonDoc["settings"] = wifiSettings;
                JsonArray modes = jsonDoc.createNestedArray("modes");
                JsonObject mode1 = modes.createNestedObject();
                mode1["caption"] = "WIFI_MODE_STA";
                mode1["value"] = WIFI_MODE_STA;
                JsonObject mode2 = modes.createNestedObject();
                mode2["caption"] = "WIFI_MODE_AP";
                mode2["value"] = WIFI_MODE_AP;

                String response;
                serializeJson(jsonDoc, response);

                server.send(200, JSON_CONTENT_TYPE, response);
                return true;
            } else if (requestMethod == HTTP_POST) {
                if (body.length() == 0) {
                    server.send(400, "content/json", buildErrorJson("Body is missing"));
                    return true;
                }

                DynamicJsonDocument jsonDoc(256);
                deserializeJson(jsonDoc, body);

                String ssid = jsonDoc["ssid"].as<String>();
                if (ssid.isEmpty()) {
                    server.send(400, "content/json", buildErrorJson("Ssid is missing"));
                    return true;
                }
                if (ssid.length() > 32) {
                    server.send(400, "content/json", buildErrorJson("Ssid is too long (32 symbols max)"));
                    return true;
                }
                String password = jsonDoc["password"].as<String>();
                if (password.length() > 0 && password.length() < 8) {
                    server.send(400, "content/json", buildErrorJson("Password is too short (8 symbols or blank)"));
                }
                int mode = jsonDoc["mode"].as<int>();
                if (mode < 0) {
                    server.send(400, "content/json", buildErrorJson("WiFi mode can't be negative"));
                }
                if (mode == WIFI_MODE_NULL) {
                    mode = WIFI_MODE_STA;
                }

                _settingsManager->putSetting(GROUP_WIFI, SSID_SETTING, ssid);
                _settingsManager->putSetting(GROUP_WIFI, PASSWORD_SETTING, password);
                _settingsManager->putSetting(GROUP_WIFI, WIFI_MODE_SETTING, mode);
                _settingsManager->saveSettings();
                server.send(200);
                if (_wifiUpdatedHandler != nullptr) {
                    (*_wifiUpdatedHandler)();
                }
                return true;
            }
            return false;
        }
    private:
        SettingsManager * _settingsManager;
        RestController::HandlerFunction * _wifiUpdatedHandler;
};

#endif