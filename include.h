//
// Created by 18746 on 2024/3/9.
//

#ifndef IPV4_INCLUDE_H
#define IPV4_INCLUDE_H
#include <string>
#include <iostream>
#include <vector>

using namespace  std;

typedef uint8_t chnid_t;
typedef uint8_t fd_t;

#define DEFAULT_MGROUP "224.0.0.1"
#define DEFAULT_RECVPORT 8888
#define DEFAULT_CLIENTPORT 8888
#define MAXCHID 100
#define MYTBF_MAX 500
#define MP3_BITRATE 64 * 1024
#define THREAD_NUM 10
#define DIR "/root/IPV4/music"


class server_Conf{
public:
    int recvport = DEFAULT_RECVPORT;
    string mgroup = DEFAULT_MGROUP;
    string media_dir =DIR;
    int if_daemon= 0;

};
typedef struct msg_head{
    char type[10];
    int totalchnid;
    int chnid;
    int len;
    char data[1024];
} msg_head;


static server_Conf server_conf;

#endif //IPV4_INCLUDE_H
