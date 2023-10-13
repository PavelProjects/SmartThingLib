#!/bin/python3.10

import socket
import struct
from datetime import datetime

LOGGER_FILE = "logger.log"
START_COLOR = "\033["
END_COLOR = "\033[0m"

ipColor = {}
group = ("224.1.1.1", 7779)
lastColorIndex = 2

mainSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
mainSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
mainSocket.bind(group)
mreq = struct.pack("4sl", socket.inet_aton(group[0]), socket.INADDR_ANY)
mainSocket.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

logFile = open(LOGGER_FILE, "a")

def colorByLevel(logLevel):
    if logLevel == "ERROR":
        return "31m"
    if logLevel == "WARNING":
        return "35m"
    if logLevel == "INFO":
        return "34m"
    if logLevel == "DEBUG":
        return "32m"
    return "30"

try:
    print(f"{START_COLOR + '1;36m'}{'':->115}")
    print(f"{'TIMESTAMP': ^26} [{'IP': ^15} :: {'NAME': ^15}] - [{'LEVEL': ^7}] [{'TAG': ^20}] :: LOG MESSAGE")
    print(f"{'':-<115}{END_COLOR}")
    while True:
        try:
            message = mainSocket.recv(4096).decode()
            splitted = message.split("$")
            if (len(splitted) == 1):
                print(message)
                continue

            ip = splitted[0]
            name = splitted[1]
            logLevel = splitted[2]
            tag = splitted[3]
            messageCuted = splitted[4].strip()

            if (ip not in ipColor.keys()):
                ipColor.update({ip: f"3{lastColorIndex}m"})
                lastColorIndex += 1

            formatedMessage = f"{START_COLOR + ipColor[ip]}{datetime.now()} [{ip: ^15} :: {name: ^15}]{END_COLOR} - "
            formatedMessage += f"{START_COLOR + colorByLevel(logLevel)}[{logLevel: ^7}] [{tag: ^20}] :: {messageCuted}{END_COLOR}"
            print(formatedMessage)
            logFile.write(formatedMessage + '\n')
            logFile.flush()
        except Exception as e:
            print("Failed to process message")
except KeyboardInterrupt:
    print("leaving...")
finally:
    mainSocket.close()
    logFile.close()