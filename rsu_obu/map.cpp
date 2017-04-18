#include "MapData.h"
#include "ApproachObject.h"
#include <iostream>
#include "map.h"
using namespace std;
Map MapDecode(const std::vector<char> &data)
{
    Map result;

    MapData_t *map = nullptr;
    asn_dec_rval_t rval;
    rval = ::asn_DEF_MapData.ber_decoder(0, &::asn_DEF_MapData, (void **)&map, data.data(), data.size(), 0);
    if(rval.code != RC_OK) {
        cout<<"RC IS NOT OK"<<endl;
        ::asn_DEF_MapData.free_struct(&::asn_DEF_MapData, map, 0);
        return result;
    }

    // Assume one map message only contains one intersection information
    Intersection_t **inters     = map->intersections->list.array;
    Intersection_t  *inter      = nullptr;
    int              intercount = 1; //map->intersections->list.count;

    ApproachObject_t **lanes  = nullptr;
    ApproachObject_t  *lane   = nullptr;
    int                lanecount  = 0;

    Lane tmpLane;
    int id = -1;
    result.mapId = id;

    // iteration variable
    int i;
    int j;
// new version has add new message,ie.landwidth;!!
    for (i=0; i<intercount; i++) {
        inter = inters[i];
        result.mapId = ntohs(*reinterpret_cast<short *>(inter->id.buf)); //modifed !!!!!!!!!!!!!!!!!!!!!!!
        result.mapCenter.latitude= inter->refPoint->lat;
        result.mapCenter.longitude = inter ->refPoint->Long;
        lanes = inter->approaches.list.array;
        lanecount = inter->approaches.list.count;

        for (j=0; j<lanecount; j++) {
            lane = lanes[j];
            tmpLane.laneCenter.latitude  = lane->refPoint->lat;
            tmpLane.laneCenter.longitude = lane->refPoint->Long;
            tmpLane.laneId = *lane->approach->id;
            result.lanes.push_back(tmpLane);
        }
    }
    ::asn_DEF_MapData.free_struct(&::asn_DEF_MapData, map, 0);

    return result;
}

