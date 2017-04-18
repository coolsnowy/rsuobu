#ifndef _PACKAGE_H_
#define _PACKAGE_H_

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include"bsm.h"
#include "map.h"
#include "trafficlight.h"
#include <vector>
#define MAXSIZE 100
using namespace std;

void type_distinguish(char recv_buf[], const std::vector<char> recv_vector,char buf[],char *frametype);
void bsmpack(BsmBlob blob,char buf[]);
void spatpack(TrafficLight light,char buf[]);
void mappack(Map map,char buf[]);

#endif


































