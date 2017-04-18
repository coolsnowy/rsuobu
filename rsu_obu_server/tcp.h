/*
 *
 * headfile.h
 *
 *  Created on: 2 Nov 2016
 *      Author: slc
 */
#ifndef TCP_H
#define TCP_H
#include<iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "unpackage.h"
#include <fstream>
using namespace std;
#define SENDTIMES 100
#define MAXLINE 500
#define MAXSELECT 30
#define MAX  1000

class tcp_client
{
private:
		struct sockaddr_in server_addr;
		struct sockaddr_in client_addr;
		int sock_fd;

public:
		bool Connect(char *ipaddress, char *destport);
		bool send_data(char *send_buf);
		char* recv_data(int recv_num);
		void Close();

};
class tcp_serv
{
private:
		struct sockaddr_in server_addr, client_addr;
		int sock_fd;
		int connfd;
        uint8_t recvbuf[1000];
        uint8_t data_head[10];

public:
		bool Listen(char *serv_port);
        uint8_t *tcp_recv();
		void Close();
};

#endif

