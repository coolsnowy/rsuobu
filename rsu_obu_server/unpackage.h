#ifndef UNPAKCAGE_H
#define UNPACKAGE_H
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>
#include <list>
#define MAXSIZE 100
using namespace std;

struct BsmBlob1
{
		int carId;
		double latitude;
		double longitude;
		double speed;
		double heading;
		double wheelAngle;
		bool carBrake;
		double acceleration;
		time_t t;
};
struct Point
{
		long latitude;
		long longitude;
};

struct Lane
{
		Point laneCenter;
		long laneId;
};

struct Map
{
		int mapId;      // Intersection id
		Point mapCenter;  // Center point of intersection
        list<Lane> lanes;  // List of lanes
};
enum SpatLightState
{
	green = 3, yellow = 2, red = 1, error = 4
};

struct SpatMovementState
{
		int laneId;
		int rightTimeToChange;
		int straightTimeToChange;
		int leftTimeToChange;
		SpatLightState rightState = error;
		SpatLightState straightState = error;
		SpatLightState leftState = error;
		int rightTime[3];  //green yellow red
		int straightTime[3];
		int leftTime[3];
};

struct TrafficLight
{
		int mapId;
        list<SpatMovementState> states;
};

BsmBlob1 bsmunpack(uint8_t buf[]);
TrafficLight spatunpack(uint8_t recvbuf[]);
Map mapunpack(uint8_t recvbuf[]);
void type_distinguish(uint8_t *data_head,uint8_t *recvbuf);

#endif
