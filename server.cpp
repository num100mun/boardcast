//
// Created by 18746 on 2024/3/14.
//
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#define MULTICAST_ADDR "224.0.0.1"
#define PORT 8888
#define MAX_MSG_LEN 1024
#include "server.h"
#include "melialib.h"
int main() {
    Server server;
    server.init();
    medialib * med = new medialib;
    server.sendlist(med);
    server.sendchannel(med);

}
