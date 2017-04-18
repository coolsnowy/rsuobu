#ifndef _FRAME_H_
#define _FRAME_H_

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void framestruct(char framebuf[], char *FrameType, int32_t Length, char buf[]);

char* framecrc(char framebuf[]);

unsigned int GetCrc32(char* buf, unsigned int len);

#endif
