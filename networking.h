#ifndef __networking_h
#define __networking_h

#include <sys/types.h>
#include <sys/socket.h>//Socket definitions
#include <netinet/in.h>//sockaddr_in structs
#include <arpa/inet.h>
#include <errno.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define LISTENQ 1024
#define MAXLINE 4096
#define BUFFSIZE 8192
#define SERV_PORT 9877

#endif
