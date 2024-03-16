#ifndef IPV4_SERVER_H
#define IPV4_SERVER_H
#include <iostream>

#include <vector>

#include<thread>

//#include "server.h"
using namespace std;
#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <cstring>
#include "melialib.h"
#include "threadpool.h"
#include <mutex>
using namespace std;

class Server {
private:
    int _fd;
    sockaddr_in _serverAddr;
    string _ipaddr;
    int _port;
    string _muladdr;
    sockaddr_in _broadcastAddr;
    mutex _mutex;


public:


    Server() : _fd(-1){
        _port = DEFAULT_RECVPORT;
        _muladdr = DEFAULT_MGROUP;
    }
    Server(int port, string muladdr, medialib med) :
        _fd(-1) , _port(port),  _muladdr(muladdr){}

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

        std::memset(&_serverAddr, 0, sizeof(_serverAddr));
        _serverAddr.sin_family = AF_INET;
        _serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        _serverAddr.sin_port = htons(_port);

        if (bind(_fd, reinterpret_cast<sockaddr*>(&_serverAddr), sizeof(_serverAddr)) < 0) {
            std::cerr << "Bind error" << std::endl;
            close(_fd);
            return false;
        }
        int ttl = 1;
        if (setsockopt(_fd, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl)) < 0) {
            std::cerr << "Error setting multicast TTL" << std::endl;
            close(_fd);
            return -1;
        }


        std::memset(&_broadcastAddr, 0, sizeof(_broadcastAddr));
        _broadcastAddr.sin_family = AF_INET;
        _broadcastAddr.sin_addr.s_addr = inet_addr(_muladdr.c_str());
        _broadcastAddr.sin_port = htons(_port);
        return true;
    }


    void sendchannel(medialib * med){
        for(int i=0; i<med->_channel_list.size(); i++){
            pool.enqueue([&](medialib * med, int chnid, int shut) {
                msg_head* msg = new msg_head;
                memset(msg, 0, sizeof(msg_head));
                msg->chnid = chnid;
                char buf[1024];

                while (!shut) {
                    int len = med->mlib_readchn(chnid, buf, 10);
                    memcpy(msg->type, "ch", sizeof("ch"));
                    memcpy(msg->data, buf, len);
                    msg->len =  len;
                    sendto(_fd, reinterpret_cast<char*>(msg), msg->len + sizeof(msg_head), 0, reinterpret_cast<sockaddr *>(&_broadcastAddr),
                           sizeof(_broadcastAddr));
                    this_thread::sleep_for(chrono::seconds(1));
                }
                delete msg;
                }, med, med->_channel_list[i]->_chnid, 0);
        }

    }


    void sendlist(medialib *med) {
            pool.enqueue([&](medialib * med, int shut) {
                msg_head * msg = new msg_head ;
                memset(msg, 0, sizeof(msg_head));
                while (!shut) {
                    for(int i=0; i<med->_channel_list.size(); i++){
                        msg->chnid = med->_channel_list[i]->_chnid;
                        msg->totalchnid = med->_channel_list.size();
                        memcpy(msg->type, "list", sizeof("list"));
                        memcpy(msg->data, med->_channel_list[i]->_desc.c_str(), med->_channel_list[i]->_desc.size());
                        msg->len =  sizeof(msg) + med->_channel_list[i]->_desc.size();
                        sendto(_fd, reinterpret_cast<char *>(msg), msg->len, 0, reinterpret_cast<sockaddr *>(&_broadcastAddr),
                               sizeof(_broadcastAddr));
                        this_thread::sleep_for(chrono::seconds(1));
                    }
                }
                delete msg;
            }, med,  0);

    }


};




#endif // IPV4_SERVER_H
