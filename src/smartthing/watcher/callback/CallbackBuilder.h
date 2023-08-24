#ifndef CALLBACK_BUILDER_H
#define CALLBACK_BUILDER_H

#include "smartthing/watcher/callback/LambdaCallback.h"
#include "smartthing/watcher/callback/HttpCallback.h"
#include "smartthing/watcher/callback/ActionCallback.h"
#include "smartthing/watcher/callback/WatcherCallback.h"
#include "smartthing/logs/BetterLogger.h"

#define CALLBACK_BUILDER_TAG "callback_builder"

namespace Callback {
    class CallbackBuilder {
        public:
            CallbackBuilder(): _readOnly(false){};

            template<typename T>
            WatcherCallback<T> * build(T triggerValue) {
                if (_type.isEmpty()) {
                    LOGGER.error(CALLBACK_BUILDER_TAG, "Callback type is missing! Can't build allback without it.");
                    return nullptr;
                }

                if (_type.equals(HTTP_CALLBACK_TAG)) {
                    if (_url.isEmpty()) {
                        LOGGER.error(CALLBACK_BUILDER_TAG, "Can't build callback of type %s without url!", _type.c_str());
                        return nullptr;
                    }
                    LOGGER.debug(CALLBACK_BUILDER_TAG, "Building new http callback %s", _url.c_str());
                    return new HttpCallback<T>(_url.c_str(), _method.c_str(), _payload.c_str(), triggerValue, _readOnly);
                } else if (_type.equals(LAMBDA_CALLBACK_TAG)) {
                    LOGGER.debug(CALLBACK_BUILDER_TAG, "Building new lambda callback");
                    return new LambdaCallback<T>([](T * v){}, triggerValue, _readOnly);
                } else if (_type.equals(ACTION_CALLBACK_TAG)) {
                    if (_action.isEmpty()) {
                        LOGGER.error(CALLBACK_BUILDER_TAG, "Can't build callback of type %s without action!", _action.c_str());
                        return nullptr;
                    }
                    LOGGER.debug(CALLBACK_BUILDER_TAG, "Building new action callback");
                    return new ActionCallback<T>(_action.c_str(), triggerValue, _readOnly);
                }
                LOGGER.error(CALLBACK_BUILDER_TAG, "Failed to build callback of type %s", _type.c_str());
                return nullptr;
            }

            // CallbackBuilder * callback(LambdaCallback::CustomCallback * callback) {
            //     if (callback.isEmpty()) {
            //         return this;
            //     }
            //     _callback = callback;
            //     return this;
            // }
            CallbackBuilder * readOnly(bool isReadOnly) {
                _readOnly = isReadOnly;
                return this;
            }
            CallbackBuilder * type(String type) {
                if (type.isEmpty()) {
                    return this;
                }
                _type = type;
                return this;
            }
            CallbackBuilder * url(String url) {
                if (url.isEmpty()) {
                    return this;
                }
                _url = url;
                return this;
            }
            CallbackBuilder * method(String method) {
                if (method.isEmpty()) {
                    return this;
                }
                _method = method;
                return this;
            }
            CallbackBuilder * payload(String payload) {
                if (payload.isEmpty()) {
                    return this;
                }
                _payload = payload;
                return this;
            }
            CallbackBuilder * action(String action) {
                if (action.isEmpty()) {
                    return this;
                }
                _action = action;
                return this;
            }
            
        private:
            // LambdaCallback<int16_t>::CustomCallback * _callback;
            bool _readOnly;
            String _type;
            String _url;
            String _method;
            String _payload;
            String _action;
    };
}

#endif