#include <Arduino.h>
#include "net/socket/Multicaster.h"

#include <lwip/sockets.h>

Multicaster::Multicaster() {
}

Multicaster::~Multicaster() {
    stop();
}

void Multicaster::init(const char * group, int port) {
    _sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (_sock < 0){
        close(_sock);
        return;
    }

    _saddr.sin_family = AF_INET;
    _saddr.sin_port = htons(port);
    _saddr.sin_addr.s_addr = inet_addr(group);
}

void Multicaster::broadcast(const char * message) {
    if (_sock < 0 || strlen(message) == 0) {
        return;
    }

    int nbytes = sendto(
        _sock,
        message,
        strlen(message),
        0,
        (struct sockaddr*) &_saddr,
        sizeof(_saddr)
    );
    if (nbytes < 0) {
        // TODO
    }
}

void Multicaster::stop() {
    close(_sock);
}
