#ifndef HANDLER_UTILS_H
#define HANDLER_UTILS_H

static const char ERROR_BODY_MISSING[] PROGMEM = "{\"error\": \"Body is missing\"}";

String buildErrorJson(String error) { return "{\"error\": \"" + error + "\"}"; }

#endif