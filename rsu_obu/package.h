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

void type_distinguish(char recv_buf[], const std::vector<uint8_t> recv_vector,uint8_t buf[],uint8_t *frametype);


void bsmpack(BsmBlob blob,uint8_t buf[]);
void spatpack(TrafficLight light,uint8_t buf[]);
void mappack(Map map,uint8_t buf[]);

#endif


































