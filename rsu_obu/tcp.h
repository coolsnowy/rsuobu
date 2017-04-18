#ifndef _TCP_H_
#define _TCP_H_

/*
 * headfile.h
 *
 *  Created on: 2 Nov 2016
 *      Author: slc
 */
#include<iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include<sys/time.h>
#include <netinet/in.h>
#include<ctype.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "map.h"
#include "trafficlight.h"
#include "bsm.h"
using namespace std;
#define SENDTIMES 100
#define MAXLINE 500
#define MAXSELECT 30
#define MAX 500


class tcp_client
{
private:
		struct sockaddr_in server_addr;
		struct sockaddr_in client_addr;
		int sock_fd;

public:
        bool Connect(const char *ipaddress, int destport);
        bool send_data(char *send_buf,size_t len);
        char* recv_data(int recv_num);
        void Close();

};
class tcp_serv
{
private:
		struct sockaddr_in server_addr, client_addr;
		int sock_fd;
		int connfd;
        char buf[MAX];
public:
        bool Listen(char *serv_port);
        char *tcp_recv();
		void Close();
};

#endif
