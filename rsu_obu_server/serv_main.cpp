#include "tcp.h"
int main(int argc, char* argv[])
{
	extern struct BsmBlob1 bsmmessage;
	extern struct Map mapmessage;
	extern struct TrafficLight spatmessage;
	//char recv_buf[1000];
	tcp_serv serv;
	serv.Listen(argv[1]);
	cout << "listen success!\n";
	serv.tcp_recv();
	return 0;
}
