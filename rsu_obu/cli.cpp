/*
 * headfile.h
 *
 *  Created on: 2 Nov 2016
 *      Author: slc
 */
#include "tcp.h"
bool tcp_client::Connect(const char *ipaddress, int destport)
{

	bzero(&client_addr, sizeof(client_addr)); //把一段内存区的内容全部设置为0
	client_addr.sin_family = AF_INET;    //internet协议族
	client_addr.sin_addr.s_addr = htons(INADDR_ANY);    //INADDR_ANY表示自动获取本机地址
	client_addr.sin_port = htons(0);    //0表示让系统自动分配一个空闲端口
	//创建用于internet的流协议(TCP)socket,用client_socket代表客户机socket
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		cout << "Create Socket Failed!\n";
		exit(1);
	}
	//把客户机的socket和客户机的socket地址结构联系起来
	if (bind(sock_fd, (struct sockaddr*) &client_addr, sizeof(client_addr)))
	{
		printf("Client Bind Port Failed!\n");
		exit(1);
	}
	//设置一个socket地址结构server_addr,代表服务器的internet地址, 端口
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	if (inet_aton(ipaddress, &server_addr.sin_addr) == 0) //服务器的IP地址来自程序的参数
	{
		cout << "Server IP Address Error!\n" << endl;
		exit(1);
	}


    cout<<"port"<<destport<<endl;
    server_addr.sin_port = htons(destport);
	socklen_t server_addr_length = sizeof(server_addr);
	//向服务器发起连接,连接成功后client_socket代表了客户机和服务器的一个socket连接
	if (connect(sock_fd, (struct sockaddr*) &server_addr,
			server_addr_length) < 0)
	{
		printf("Can Not Connect To %s!\n", ipaddress);
		exit(1);
	}
	else
		cout << "connect success" << endl;

	return true;
}
bool tcp_client::send_data(char *send_buf,size_t len)
{
    int send_num;
    send_num = send(sock_fd, send_buf,len, 0);
    if (send_num < 0)
    {
          perror("send error:");
          exit(1);
    }
    else
          cout<<"send success"<<endl;
    return true;
}
char* tcp_client::recv_data(int recv_num)
{
    char recv_buf[MAX];
	recv_num = recv(sock_fd, recv_buf, sizeof(recv_buf), 0);
	if (recv_num < 0)
	{
		perror("recv error");
		exit(1);
	}
    return recv_buf;
}
void tcp_client::Close()
{
	close(sock_fd);
}


