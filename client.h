//
// Created by 18746 on 2024/3/13.
//
#include "include.h"
#ifndef IPV4_CLIENT_H
#define IPV4_CLIENT_H
#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <cstring>
#include <map>

#include "melialib.h"
#include "threadpool.h"
class Client {
public:
    int _fd;
    int _port;
    std::string _muladdr;
    mutex _mutex;
    map<int,string> _channrl_desc;

    public:
    Client() : _fd(-1), _port(DEFAULT_CLIENTPORT), _muladdr(DEFAULT_MGROUP) {}
    Client(int port, const std::string& muladdr) : _fd(-1), _port(port), _muladdr(muladdr) {}

    bool init() {
        _fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_fd < 0) {
            std::cerr << "Socket create error" << std::endl;
            return false;
        }

        int broadcastEnable = 1;
        if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &broadcastEnable, sizeof(broadcastEnable)) < 0) {
            std::cerr << "Error setting socket option" << std::endl;
            close(_fd);
            return false;
        }

        sockaddr_in clientAddr;
        std::memset(&clientAddr, 0, sizeof(clientAddr));
        clientAddr.sin_family = AF_INET;
        clientAddr.sin_port = htons(_port);
        clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind(_fd, reinterpret_cast<sockaddr*>(&clientAddr), sizeof(clientAddr)) < 0) {
            std::cerr << "Bind error" << std::endl;
            close(_fd);
            return false;
        }

        ip_mreq multicastRequest;
        multicastRequest.imr_multiaddr.s_addr = inet_addr(_muladdr.c_str());
        multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);

        if (setsockopt(_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicastRequest, sizeof(multicastRequest)) < 0) {
            std::cerr << "Error adding to multicast group" << std::endl;
            close(_fd);
            return false;
        }

        return true;
    }


    void receiveChannel(int chnid) {
        int len;
        char buffer[2048];
        memset(buffer, 0 , sizeof(buffer));
        sockaddr_in serverAddr;
        socklen_t serverAddrLen = sizeof(serverAddr);
        msg_head  * msg = new msg_head ;
        while (true) {
            memset(buffer, 0, sizeof(buffer));
            len = recvfrom(_fd, buffer, sizeof(buffer), 0, reinterpret_cast<sockaddr *>(&serverAddr), &serverAddrLen);
            msg = (msg_head *) buffer;
            if(strcmp(msg->type,"ch") == 0 && msg->chnid == chnid) {
                cout << "msg chnid " << msg->chnid << " message :"<< msg->data << endl;
            }

        }
    }

    void receivelist() {
        int len;
        int totalchnin;
        char buffer[2048];
        memset(buffer, 0 , sizeof(buffer));
        sockaddr_in serverAddr;
        socklen_t serverAddrLen = sizeof(serverAddr);
        msg_head  * msg = new msg_head ;
        while (true) {
            memset(buffer, 0, sizeof(buffer));
            len = recvfrom(_fd, buffer, sizeof(buffer), 0, reinterpret_cast<sockaddr *>(&serverAddr), &serverAddrLen);
            msg = (msg_head *) buffer;
            totalchnin = msg->totalchnid;
            if(strcmp(msg->type, "list") == 0)
                if(_channrl_desc.size() == totalchnin)
                    break;
                else{
                    if(_channrl_desc.find(msg->chnid) == _channrl_desc.end())
                        _channrl_desc[msg->chnid] = msg->data;
                }

        }
    }

};
#endif //IPV4_CLIENT_H
