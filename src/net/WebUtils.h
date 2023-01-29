#include "DictionaryDeclarations.h"

#define WEB_SERVER_TAG "web_server"

enum LOUVER_ACTIONS {
    DISABLE_AUTO_MODE,
    ENABLE_AUTO_MODE,
    OPEN,
    CLOSE,
    MIDDLE,
    BRIGHT
};

const char * greetingPage = "Hi there!";

String buildErrorJson(String error) {
    return "{\"error\":\"" + error + "\"}";
}

void handleLouverGet(WebServer * server, LouverController * controller) {
    Dictionary * dict = new Dictionary(3);
    dict->insert("automode", controller->isAutoModeEnabled());
    dict->insert("position", controller->getMotorPosition());
    dict->insert("light", controller->getLightValue());

    server->send(200, "application/json", dict->json());
    delete dict;
}

void handleLouverPut(WebServer * server, LouverController * controller) {
    if (!server->hasArg("plain")) {
        server->send(400);
        return;
    }
    Dictionary * dict = new Dictionary(1);
    dict->jload(server->arg("plain"));

    String actionStr = dict->search("action");
    if (actionStr.length() > 0) {
        int action = actionStr.toInt();
        // TODO мне кажется есть элегантное решение, но пока только на это
        // хватило познаний c++
        switch(action) {
            case ENABLE_AUTO_MODE:
                controller->enableAutoMode();
                break;
            case DISABLE_AUTO_MODE:
                controller->disabelAutoMode();
                break;
            case OPEN:
                controller->open();
                break;
            case CLOSE:
                controller->close();
                break;
            case MIDDLE:
                controller->middle();
                break;
            case BRIGHT:
                controller->bright();
                break;
            default:
                server->send(400, "application/json", buildErrorJson(String("Wrong action ") + action));
                return;
        }
    }
    
    server->send(200);
}