//
// Created by 18746 on 2024/3/11.
//

#ifndef IPV4_UTIL_H
#define IPV4_UTIL_H
#include "include.h"
#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <cstring>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
static bool daemonize(){
    pid_t pid = fork();
    if(pid < 0){
        std::cerr << "fork failed!" << endl;
        return false;
    }
    else if(pid > 0){
        exit(0);
    }
    int fd = open("/dev/null", O_RDWR);
    if(fd < 0){
        std::cerr << "daeonize fd open failed!" << endl;
        return false;
    }else{
        dup2(fd, 0);
        dup2(fd, 1);
        dup2(fd, 2);
        if(fd > 2)
            close(fd);
    }
    chdir("/");
    umask(0);
    setsid();
    return 0;

}

static void printf_help() {
    printf("-M   指定多播组\n"
           "-P   指定接收端口\n"
           "-F   前台运行\n"
           "-D   指定媒体库位置\n"
           "-I   指定网络设备\n"
           "-H   显示帮助\n");
}

#endif //IPV4_UTIL_H
