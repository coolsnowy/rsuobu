#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include <list>

#include <stdint.h>

struct Point
{
    long latitude;
    long longitude;
};

struct Lane
{
    Point laneCenter;
    long  laneId;
};

struct Map
{
    int         mapId;      // Intersection id
    Point       mapCenter;  // Center point of intersection
    std::list<Lane> lanes;  // List of lanes
};

Map MapDecode(const std::vector<uint8_t> &data);

#endif
