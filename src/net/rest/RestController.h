#ifndef REST_CONTROLLER_H
#define REST_CONTROLLER_H

#include <ESPAsyncWebServer.h>

#define CONTENT_TYPE_JSON "application/json"
#define CONTENT_TYPE_JS "text/javascript"

typedef std::function<void(void)> RestHandlerFunction;

class RestControllerClass {
 public:
  RestControllerClass();
  ~RestControllerClass();
  void begin();
  void reload();

  void addConfigUpdatedHandler(RestHandlerFunction hf) {
    _configUpdatedHandler = hf;
  }
  void addRestartHandler(RestHandlerFunction hf) { _restartHandler = hf; }

  AsyncWebServer* getWebServer() { return &_server; };

 private:
  bool _setupFinished = false;
  AsyncWebServer _server;

  void setupHandler();

  RestHandlerFunction _configUpdatedHandler = []() {};
  RestHandlerFunction _restartHandler = []() {};
};

extern RestControllerClass RestController;

#endif