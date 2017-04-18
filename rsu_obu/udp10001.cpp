/*
 * headfile.h
 *
 *  Created on: 2 Nov 2016
 *      Author: slc
 */
#include <iostream>
#include <stdio.h>
#include <string>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <ctype.h>
#include <fstream>
#include <arpa/inet.h>
#include <netdb.h>
#include <vector>
#include <list>
#include "package.h"
#include "bsm.h"
#include "frame.h"
#include "map.h"
#include "tcp.h"
#include "trafficlight.h"
#include "json/json.h"
using namespace std;
#define MAXLINE 1000
#define FILEMAX 1000
#define MAXSELECT 100000
#define MAX 500

TrafficLight spat;
BsmBlob bsm={32,0.0021,0.32,24,23,3,3,28};
Map light;
int main(int argc, char **argv)
{
    const char *RecvPort=0;
    const char *ServIP=0;
    const char *ServPort=0;
    Json::Reader reader;
    Json::Value root;
    ifstream in;
    in.open("/home/skymooon/workspace/Qt/rsu_obu/ini.json", ios::binary);
    if( !in.is_open() )
    {
        cout << "Error opening file\n";
        return 0;
    }
    if(reader.parse(in,root))
    {
        string s1 = root["RecvPort"].asString();
        RecvPort= s1.c_str();
        cout<<"Recv Port is "<<RecvPort<<endl;
        string s2 = root["ServIP"].asString();
        ServIP = s2.c_str();
       // cout<<s2<<endl;
        cout<<"Serv Ip is "<<ServIP<<endl;
        string s3 =root["ServPort"].asString();
        ServPort = s3.c_str();

        cout<<"Serv Port is "<<ServPort<<endl;
        cout << "Reading Complete!" << endl;
    }
    else
    {
        cout << "parse error\n" << endl;
    }

    in.close();
    int port = atoi(ServPort);
	struct timeval timeout;
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	int sock_fd, connfd = 0, sockfd;
	int maxfd, maxi = -1, nready = 0, i = 0;
	int client[MAXSELECT];

    /* socket文件描述符 */
	char addr_p[INET_ADDRSTRLEN];
	fd_set allset, readfds;
	int addr_len;
	int SERV_PORT;
	int recv_num;
	int send_num;
	char recv_buf[MAXLINE];
    vector<char> recv_vector;
	static int n = 1;
	struct sockaddr_in addr_serv, addr_cli;

    if ((SERV_PORT = atoi(RecvPort) )< 0)
	{

        printf("SErV_PORt error! Usage: %s Portnumber\n", RecvPort);
		exit(1);
	}
    // cout<<"Serv Port"<<SERV_PORT<<endl;
	if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket error");
		exit(1);
	}
	memset(&addr_serv, 0, sizeof(struct sockaddr_in));
	addr_serv.sin_family = AF_INET;
    addr_serv.sin_port = htons(SERV_PORT);
	addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
	bzero(&addr_serv.sin_zero, 8);
	addr_len = sizeof(addr_serv);
	bzero(&addr_cli, sizeof(addr_cli));
	addr_cli.sin_family = AF_INET;
	addr_cli.sin_port = htons(10001);
	addr_cli.sin_addr.s_addr = INADDR_ANY;
	bzero(&addr_cli.sin_zero, 8);
	if (bind(sock_fd, (struct sockaddr *) &addr_serv, sizeof(addr_serv)) < 0)
	{

        perror("bind error:here");
		exit(1);
	}
	maxfd = sock_fd;
	FD_ZERO(&allset); /*初始化描述符集*/
	FD_SET(sock_fd, &allset); /*将监听Socket加入描述符集*/
	for (i = 0; i < MAXSELECT; i++) /*初始化客户数组，-1表示该项没有被登记*/
		client[i] = -1;

    tcp_client tcpclient;
    tcpclient.Connect(ServIP,port);

    char frametype;
    frametype = 0x00;

	while (1)
	{
        // it is so important
        recv_vector.clear();
        memset(recv_buf,0,MAXLINE);
		printf("\n\n");
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		printf("\nserver wait:\n");
        d1: readfds = allset;
        //get the number of fd we can obtain present
		nready = select(maxfd + 1, &readfds, NULL, NULL, &timeout);
		if (FD_ISSET(sock_fd, &readfds))
		{
            // check if any socket to read again, if not any, continue waiting the next socket
			if (nready <= 0)
				continue;
			nready--;
			printf("Accepted a new connect. Client socket id: %d\n", connfd);
			inet_ntop(AF_INET, &addr_cli.sin_addr, addr_p, sizeof(addr_p));
			printf("client IP is %s,port is %d\n", addr_p,
					ntohs(addr_cli.sin_port));
            //print the address and port of client
            for (i = 0; i < MAXSELECT; i++)
			{
                 // add new client to the client array
				if (client[i] < 0)
				{
					client[i] = connfd;
					printf("add client success!\n");
					break;
				}
			}
			if (i == MAXSELECT)
			{
				printf("Too many clients, server stopped!\n");
				exit(1);
			}
            FD_SET(connfd, &readfds);
            // add the new socket to the set of fd
            if (connfd > maxfd)
            //update tha max num of the set of fd
				maxfd = connfd;
			if (i > maxi)
                maxi = i; //max num of client
			for (i = 0; i <= maxi; i++)
			{
                if ((sockfd = client[i]) < 0) // invalid client
				{
					printf("client invalid");
					continue;
				}
                if (FD_ISSET(sockfd, &readfds)) //judge if any socketfd to read
				{

					printf("have socket to read!\n");
					recv_num = recvfrom(sock_fd, recv_buf, sizeof(recv_buf), 0,
							(struct sockaddr *) &addr_cli,
							(socklen_t *) &addr_len);
					if (recv_num < 0)
					{
                        perror("recvfrom error:");
						exit(1);
					}
                    cout<<"receive success\n"<<recv_num<<"bytes"<<endl;

                    int num=0;
                    for(num=0;num<recv_num;num++)
                    {
                        recv_vector.push_back(recv_buf[num]);
                    }
                    cout<<"recv vector size="<<recv_vector.size()<<endl;
                    // send
                    cout<<"type distinguish\n";
                    char *buf = new char[1000];
                    memset(buf,0,1000);
                    type_distinguish(recv_buf,recv_vector,buf,&frametype);
                    // frame
                    size_t bufi=0;
                    int32_t buf_i =0;
                    while(buf[buf_i]!= ',' && buf_i < 999)
                    {
                        buf_i++;
                    }
                    cout<<buf[buf_i]<<'\t';
                    buf_i++;
                    cout<<"buf len="<<buf_i;

                    char *framebuf = new char[1000];
                    memset(framebuf,0,1000);
                    framestruct(framebuf,&frametype,buf_i,buf); //donot have crc32
                    int32_t framelen=0 ;
                    while(framebuf[framelen] != ',' && framelen <1000)
                        framelen++;
                    framelen++;
                    cout<<"frame length="<<framelen<<endl;
                    tcpclient.send_data(framebuf,framelen);
                    memset(buf,0,sizeof(buf));
                    memset(framebuf,0,sizeof(framebuf));
                    delete []buf;
                    delete []framebuf;
                    if (nready <= 0)
						break;
				}
			}
		}
	}

	close(sock_fd);
    tcpclient.Close();
	return 0;
}






