#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#define MULTICAST_ADDR "224.0.0.1"
#define PORT 8888
#define MAX_MSG_LEN 1024
#include "client.h"
int main() {
    Client client;
    client.init();
    client.receivelist();
    for(auto &i : client._channrl_desc)
        cout << "chnid : " << i.first << " desc :" << i.second << endl;
    client.receiveChannel(0);
    return 0;
}