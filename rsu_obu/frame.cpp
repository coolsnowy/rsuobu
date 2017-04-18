#include "frame.h"
using namespace std;
void framestruct(char framebuf[],char *FrameType,int32_t Length,char buf[])
{
	char Head[2] = { 0x59, 0x5A };
	//1 frame begin with 0x595A
    *framebuf = Head[0];
    framebuf++;
    *framebuf = Head[1];
    framebuf++;
	//2 protocol version
	*framebuf++ = '1';
	//3.1 frameType
    *framebuf++ = *FrameType;
	//3.2 data_length short int
	*framebuf++ = (Length & 0xFF00) >> 8;
	*framebuf = (Length & 0xFF);
	//3.3 data
	int bufi = 0;
    for (bufi = 0; bufi < Length && bufi<1000; bufi++)
	{
		framebuf++;
		*framebuf = buf[bufi];
	}
    cout<<"frame struct success\n";
}
unsigned int GetCrc32(char* buf, unsigned int len)
{
	//生成Crc32的查询表
	unsigned int Crc32Table[256];
	int i, j;
	unsigned int Crc;
	for (i = 0; i < 256; i++)
	{
		Crc = i;
		for (j = 0; j < 8; j++)
		{
			if (Crc & 1)
				Crc = (Crc >> 1) ^ 0xEDB88320;
			else
				Crc >>= 1;
		}
		Crc32Table[i] = Crc;
	}
	//开始计算CRC32校验值
	Crc = 0xffffffff;
	for (int i = 0; i < len; i++)
	{
		Crc = (Crc >> 8) ^ Crc32Table[(Crc & 0xFF) ^ buf[i]];
	}
	Crc ^= 0xFFFFFFFF;
	return Crc;
}
char *framecrc(char framebuf[])
{
	unsigned int crc;
	int len = strlen(framebuf);
	crc = GetCrc32(framebuf, len);
	*++framebuf = (crc & 0xFF000000) >> 24;
	*++framebuf = (crc & 0xFF0000) >> 16;
	*++framebuf = (crc & 0xFF00) >> 8;
	*++framebuf = (crc & 0xFF);
	*++framebuf = '\0';
	return framebuf;
}
