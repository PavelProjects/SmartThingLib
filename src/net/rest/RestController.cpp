#include "net/rest/RestController.h"

#include "Features.h"
#include "net/rest/handlers/ActionRequestHandler.h"
#include "net/rest/handlers/HooksRequestHandler.h"
#include "net/rest/handlers/ConfigRequestHandler.h"
#include "net/rest/handlers/InfoRequestHandler.h"
#include "net/rest/handlers/SensorsRequestHandler.h"
#include "net/rest/handlers/StateRequestHandler.h"
#include "net/rest/handlers/WiFiRequestHandler.h"
#include "net/rest/handlers/SettingsRequestHandler.h"
#include "net/rest/handlers/DangerRequestHandler.h"
#include "net/rest/WebPageAssets.h"

static const char * WEB_SERVER_TAG = "web_server";

String resetReasonAsString() {
  #ifdef ARDUINO_ARCH_ESP8266
  return ESP.getResetReason();
  #endif
  #ifdef ARDUINO_ARCH_ESP32
  switch (esp_reset_reason()) {
    case ESP_RST_POWERON:
      return "ESP_RST_POWERON";
    case ESP_RST_EXT:
      return "ESP_RST_EXT";
    case ESP_RST_SW:
      return "ESP_RST_SW";
    case ESP_RST_PANIC:
      return "ESP_RST_PANIC";
    case ESP_RST_INT_WDT:
      return "ESP_RST_INT_WDT";
    case ESP_RST_TASK_WDT:
      return "ESP_RST_TASK_WDT";
    case ESP_RST_WDT:
      return "ESP_RST_WDT";
    case ESP_RST_DEEPSLEEP:
      return "ESP_RST_DEEPSLEEP";
    case ESP_RST_BROWNOUT:
      return "ESP_RST_BROWNOUT";
    case ESP_RST_SDIO:
      return "ESP_RST_SDIO";
    default:
      return "ESP_RST_UNKNOWN";
  }
  #endif
}

RestControllerClass RestController;

RestControllerClass::RestControllerClass(): _server(AsyncWebServer(80)) {};
RestControllerClass::~RestControllerClass(){};

void RestControllerClass::begin() {
  setupHandler();
  _server.begin();
  _setupFinished = true;
  SMT_LOG_INFO(WEB_SERVER_TAG, "Web service started");
}

void RestControllerClass::reload() {
  if (_setupFinished) {
    _setupFinished = false;
    _server.end();
  }
  begin();
}

void RestControllerClass::setupHandler() {
  _server.addHandler(new ConfigRequestHandler(&_configUpdatedHandler));
  _server.addHandler(new WiFiRequesthandler());
  _server.addHandler(new InfoRequestHandler());
  _server.addHandler(new SettingsRequestHandler());
  _server.addHandler(new DangerRequestHandler());
  #if ENABLE_SENSORS
  _server.addHandler(new SensorsRequestHandler());
  #endif
  #if ENABLE_STATES
  _server.addHandler(new StateRequestHandler());
  #endif
  #if ENABLE_ACTIONS
  _server.addHandler(new ActionRequestHandler());
  #endif
  #if ENABLE_HOOKS
  _server.addHandler(new HooksRequestHandler());
  #endif

  _server.on("/health", HTTP_GET, [this](AsyncWebServerRequest * request) {
    LOGGER.logRequest(WEB_SERVER_TAG, request->methodToString(), "/health", "");
    request->send(200, "text/plain", "I am alive!!! :)");
  });

#if ENABLE_WEB_PAGE
  _server.on("/", HTTP_GET, [this](AsyncWebServerRequest * request) {
    LOGGER.logRequest(WEB_SERVER_TAG, request->methodToString(), "/", "");
    request->send_P(200, "text/html", WEB_PAGE_MAIN);
  });
  _server.on("/assets/script.js", HTTP_GET, [this](AsyncWebServerRequest * request) {
    request->send_P(200, "text/javascript", SCRIPT_PAGE_MAIN);
  });
  _server.on("/assets/styles.css", HTTP_GET, [this](AsyncWebServerRequest * request) {
    request->send_P(200, "text/css", STYLE_PAGE_MAIN);
  });
#else
  _server.on("/", HTTP_GET, [this](AsyncWebServerRequest * request) {
    LOGGER.logRequest(WEB_SERVER_TAG, request->methodToString(), "/", "");
    request->send(200, "text/plain", "Web control panel is not included in this build!");
  });
#endif

  _server.on("/features", HTTP_GET, [this](AsyncWebServerRequest * request) {
    LOGGER.logRequest(WEB_SERVER_TAG, request->methodToString(), "/features", "");
    JsonDocument doc;
    doc["web"] = ENABLE_WEB_PAGE == 1;
    doc["actions"] = ENABLE_ACTIONS == 1;
    doc["sensors"] = ENABLE_SENSORS == 1;
    doc["states"] = ENABLE_STATES == 1;
    doc["hooks"] = ENABLE_HOOKS == 1;
    doc["logger"] = ENABLE_LOGGER == 1;
    
    String response;
    serializeJson(doc, response);
    AsyncWebServerResponse * resp = request->beginResponse(200, CONTENT_TYPE_JSON, response);
    resp->addHeader("Access-Control-Allow-Origin", "*");
    request->send(resp);
  });

  _server.on("/metrics", HTTP_GET, [this](AsyncWebServerRequest * request) {
    LOGGER.logRequest(WEB_SERVER_TAG, request->methodToString(), request->url().c_str(), "");
    JsonDocument doc;
    doc["uptime"] = millis();

    JsonObject obj = doc["heap"].to<JsonObject>();
    obj["free"] = ESP.getFreeHeap();
    doc["resetReason"] = resetReasonAsString();

    #ifdef ARDUINO_ARCH_ESP32
    obj["size"] = ESP.getHeapSize();
    obj["minFree"] = ESP.getMinFreeHeap();
    obj["maxAlloc"] = ESP.getMaxAllocHeap();
    #endif

    #if ENABLE_SENSORS || ENABLE_STATES || ENABLE_HOOKS
    JsonObject counts = doc["counts"].to<JsonObject>();
    #if ENABLE_SENSORS
    counts["sensors"] = SmartThing.getSensorsCount();
    #endif
    #if ENABLE_STATES
    counts["states"] = SmartThing.getDeviceStatesCount();
    #endif
    #if ENABLE_HOOKS
    counts["hooks"] = HooksManager.getTotalHooksCount();
    #endif
    #endif

    String response;
    serializeJson(doc, response);
    AsyncWebServerResponse * resp = request->beginResponse(200, CONTENT_TYPE_JSON, response);
    resp->addHeader("Access-Control-Allow-Origin", "*");
    request->send(resp);
  });

  _server.on("/restart", HTTP_GET, [&](AsyncWebServerRequest * request) {
    LOGGER.logRequest(WEB_SERVER_TAG, request->methodToString(), request->url().c_str(), "");

    request->send(200);
    SMT_LOG_INFO(WEB_SERVER_TAG, "---------RESTART---------");
    _restartHandler();

    delay(2000);
    ESP.restart();
  });

  _server.onNotFound(
      [&](AsyncWebServerRequest * request) { request->send(404, "text/plain", "Page not found"); });
}