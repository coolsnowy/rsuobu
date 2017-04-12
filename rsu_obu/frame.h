#ifndef _FRAME_H_
#define _FRAME_H_
typedef unsigned char		uint8_t;
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void framestruct(uint8_t framebuf[], uint8_t *FrameType, int32_t Length, uint8_t buf[]);

void *framecrc(uint8_t framebuf[]);

unsigned int GetCrc32(uint8_t* buf, unsigned int len);

#endif
