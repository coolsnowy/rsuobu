/*
 * headfile.h
 *
 *  Created on: 2 Nov 2016
 *      Author: slc
 */
#include "tcp.h"
#include <fstream>
#include <assert.h>
#define FILENAME server.txt
const char * filename = "bsm.txt";
bool tcp_serv::Listen(char *serv_port)
{
	bzero(&server_addr, sizeof(server_addr)); //把一段内存区的内容全部设置为0
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	int port = atoi(serv_port);
	server_addr.sin_port = htons(port);
	//创建用于internet的流协议(TCP)socket,用server_socket代表服务器socket
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		cout << "Create Socket Failed!";
		exit(1);
	}
	int opt = 1;
	setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (bind(sock_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)))
	{
		cout << "bind error" << endl;
		exit(1);
	}
	if (listen(sock_fd, 20))
	{
		cout << "Server Listen Failed!" << endl;
		exit(1);
	}
	return 1;
}
uint8_t * tcp_serv::tcp_recv()
{
    ofstream in;
    in.open("bsm.txt",ios::out|ios::app);
//    FILE *date_fp;
//    if((date_fp=fopen(filename,"a+"))==NULL)
//    {
//            printf("Can't open \"words\" file!\n");
//            exit(1);
//    }
	socklen_t peerlen = sizeof(server_addr);
	//char recv_buf[MAX] = "0";
	int i;
	int client[FD_SETSIZE];
	int maxi = 0;
	for (i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;
	int nready;
	int maxfd = sock_fd;
	struct timeval timeout;
	fd_set rset;
	fd_set allset;
	FD_ZERO(&rset);
	FD_ZERO(&allset);
	FD_SET(sock_fd, &allset);
    //cout << "waiting\n";
	while (1)
	{
        cout<<"waiting message"<<endl;
        in<<"waiting message"<<endl;
        memset(recvbuf,0,sizeof(recvbuf));
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		rset = allset;
		nready = select(maxfd + 1, &rset, NULL, NULL, &timeout);
        if (nready == -1) {
                   if (errno == EINTR)
                       continue;

               }

               if (nready == 0)
                   continue;
        // detect if any new client
		if (FD_ISSET(sock_fd, &rset))
		{
            cout<<"enter"<<endl;
			if (nready <= 0)
			{
				cout << "nready <=0\n";
                in << "nready <=0\n";
				continue;
			}
            //nready--;
			connfd = accept(sock_fd, (struct sockaddr*) &client_addr, &peerlen); //accept不再阻塞
			if (connfd == -1)
			{
				cout << "accept error" << endl;
                in << "accept error" << endl;
				continue;
			}
			for (i = 0; i < FD_SETSIZE; i++)
			{
				if (client[i] < 0)
				{
					client[i] = connfd;
					cout << "add client success!\n";
                    in << "add client success!\n";
					break;
				}
			}
			if (i == FD_SETSIZE)
			{
				cout << "too many clients\n";
                in<< "too many clients\n";
				exit(1);
			}

            FD_SET(connfd, &allset);
			if (connfd > maxfd)
				maxfd = connfd;

			if (i > maxi)
			{
				maxi = i;
			}
            if(--nready <=0)
                continue;
        }
			for (i = 0; i <= maxi; i++)
			{
				if ((connfd = client[i]) < 0) /*无效的客户记录*/
				{
					cout << "client invalid" << endl;
                    in << "client invalid" << endl;
					continue;
				}
				if (FD_ISSET(connfd, &rset)) /*判断是否有套接字可读*/
				{
                    memset(data_head,0,sizeof(data_head));
                    int head_len = recv(connfd,data_head,6,0);
                    if(head_len ==-1)
                        {
                        cout<<"head error"<<endl;
                        break;
                    }
                    else if (head_len  == 0) { //客户端关闭
                                       printf("client close \n");
                                       FD_CLR(connfd, &allset);
                                       client[i] = -1;
                                       close(connfd);
                                   }
                    else if(head_len <7)
                        {
                        cout<<"len error,len<7"<<endl;
                    }

                    int data_len =0;
                    data_len = data_len | ((int) data_head[4]) << 8;
                    data_len = data_len | (int) data_head[5];
                    int len = recv(connfd, recvbuf, data_len, 0);
					if (len == -1)
					{
						cout << "readline error" << endl;
                        in << "readline error" << endl;
						break;
					}
                   // while(len>0)
                    //{
                        cout<<"receive success"<<endl<<endl<<endl;
                        in <<"receive success"<<endl<<endl<<endl;
                        cout <<endl<< "recv " << len << " bytes\n";
                        in <<endl<< "recv " << len << " bytes\n";
                        assert(recvbuf);
                        type_distinguish(data_head,recvbuf);
                        int num=0;
                        while(recvbuf[num]!=',' && num<1000)
                            num++;
                        num+=1;
                        cout<<"buflen="<<len<<endl;
                        in <<"buflen="<<len<<endl;

                    if (--nready <= 0)
					break;
				}
			}

	}

    //FD_CLR(connfd, &allset);
    //client[i] = -1;
    return recvbuf;
}
void tcp_serv::Close()
{
	close(sock_fd);
}
