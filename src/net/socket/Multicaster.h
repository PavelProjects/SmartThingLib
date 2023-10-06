#include "lwip/sockets.h"

#ifndef Multicaster_H
#define Multicaster_H

#define MULTICASTER_TAG "multicaster"
#define DEFAULT_BROADCAST_DELAY 5000

class Multicaster {
    private:
        int _sock = -1;
        struct sockaddr_in _saddr = { 0 }; 

    public:
        Multicaster();
        ~Multicaster();
        void init(const char * group, int port);
        void broadcast(const char * message);
        void stop();
};

#endif