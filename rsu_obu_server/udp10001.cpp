/*
 * headfile.h
 *
 *  Created on: 2 Nov 2016
 *      Author: slc
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <vector>
#include <list>
#include <package.h>
#include <bsm.h>
#include <frame.h>
#include <map.h>
#include <tcp.h>
#include <trafficlight.h>
#include <unpackage.h>
using namespace std;
#define MAXLINE 1000
#define FILEMAX 1000
#define MAXSELECT 100000
#define MAX 500

int main(int argc, char *argv[])
{
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
	vector<uint8_t> recv_vector;
	static int n = 1;
	struct sockaddr_in addr_serv, addr_cli;
	if (argc != 2)
	{
		printf("Arguments error !Usage: %s Portnumber\n", argv[0]);
		exit(1);
	}
	if ((SERV_PORT = atoi(argv[1])) < 0)
	{
		printf("SErV_PORt error! Usage: %s Portnumber\n", argv[0]);
		exit(1);
	}
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
		perror("bind error:");
		exit(1);
	}
	maxfd = sock_fd;
	FD_ZERO(&allset); /*初始化描述符集*/
	FD_SET(sock_fd, &allset); /*将监听Socket加入描述符集*/
	for (i = 0; i < MAXSELECT; i++) /*初始化客户数组，-1表示该项没有被登记*/
		client[i] = -1;
	while (1)
	{
		printf("\n\n");
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		printf("\nserver wait:\n");
		d1: readfds = allset; //得到当前可以读的文件描述符数目
		nready = select(maxfd + 1, &readfds, NULL, NULL, &timeout);
		if (FD_ISSET(sock_fd, &readfds))
		{
			/*再次检查是否有可读的套接字，若没有，则继续等待下一个就绪套接字*/
			if (nready <= 0)
				continue;
			nready--;
			printf("Accepted a new connect. Client socket id: %d\n", connfd);
			inet_ntop(AF_INET, &addr_cli.sin_addr, addr_p, sizeof(addr_p));
			printf("client IP is %s,port is %d\n", addr_p,
					ntohs(addr_cli.sin_port));
			//打印客户端地址和端口号
			for (i = 0; i < MAXSELECT; i++) /*将新的客户加入客户数组*/
			{
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
			FD_SET(connfd, &readfds); /*将这个新连接的套接字添加至描述符集*/
			if (connfd > maxfd) /*更新描述符集中的最大值*/
				maxfd = connfd;
			if (i > maxi)
				maxi = i; /*记录当前最大客户数*/
			for (i = 0; i <= maxi; i++)
			{
				if ((sockfd = client[i]) < 0) /*无效的客户记录*/
				{
					printf("client invalid");
					continue;
				}
				if (FD_ISSET(sockfd, &readfds)) /*判断是否有套接字可读*/
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
					printf("receive success!\n");
					vector<uint8_t>::iterator first = recv_vector.begin();
					for (i = 0; i < strlen(recv_buf); i++)
					{
						first = recv_vector.insert(first, recv_buf[i]);
						first++;
					}







					//recv_buf[recv_num] = '\0';
					printf("%d :server receive %d bytes: %s\n\n", n++,
							strlen(recv_buf), recv_buf);

					if (nready <= 0)
						break;
				}
			}
		}
	}
	close(sock_fd);
	return 0;
}



