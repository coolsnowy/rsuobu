#include "trafficlight.h"
#include <iostream>
using namespace std;
SpatLightState ColorIntToEnum(int color)
{
    switch (color) {
        case 1:
            return green;
        case 2:
            return yellow;
        case 4:
            return red;
        default:
            return error;
    }
}

TrafficLight SpatDecode(const std::vector<char> &data)
{
    std::cout<<"spat Decode"<<std::endl;
    TrafficLight result;
    result.mapId = -1;

    SPAT_t *spat = nullptr;

    int lanes = 0;
    int ttime = 0;

    asn_dec_rval_t rval;
    rval = ::asn_DEF_SPAT.ber_decoder(0, &::asn_DEF_SPAT, reinterpret_cast<void **>(&spat), data.data(), data.size(),0);

    if(rval.code != RC_OK) {
        cout<<"RC_ is not OK"<<endl;
        return result;
    }
    SpatMovementState tmpLightState;
    result.mapId = ntohs(*reinterpret_cast<short *>(spat->intersections.list.array[0]->id.buf));
     lanes = *spat->intersections.list.array[0]->lanesCnt;

//    if (lanes % 3) {

//        return result;
//    }else {

//        lanes = lanes/3;
//    }
    cout<<"lanes="<<lanes<<endl;
    int i;
    cout<<"lanes="<<lanes<<endl;
    for(i=0; i<lanes; i++) {

        //assert(list);
       // std::cout<<"1"<<std::endl;
        if(spat->intersections.list.array[0]->states.list.array[i]->laneSet.size == 1) {
           // cout<<"==1"<<endl;
            tmpLightState.laneId = spat->intersections.list.array[0]->states.list.array[i]->laneSet.buf[0];
        }else {
            //cout<<"!=1"<<endl;
            return result;
        }

        if((tmpLightState.leftState = ColorIntToEnum(*spat->intersections.list.array[0]->states.list.array[i]->currState)) == error) {
            return result;
        }

        // Left
        tmpLightState.leftTimeToChange = spat->intersections.list.array[0]->states.list.array[i]->timeToChange;
        ttime = *(spat->intersections.list.array[0]->states.list.array[i]->pedCount);
        tmpLightState.leftTime[0]  = ttime/65536;
        ttime = ttime%65536;
        tmpLightState.leftTime[1] = ttime/256;
        tmpLightState.leftTime[2] = ttime = ttime%256;

        // Straight
        if(spat->intersections.list.array[0]->states.list.array[i]->laneSet.buf[0] != tmpLightState.laneId) {
            return result;
        }

        if((tmpLightState.straightState=ColorIntToEnum(*spat->intersections.list.array[0]->states.list.array[i]->currState)) == error) {
            return result;
        }
        tmpLightState.straightTimeToChange = spat->intersections.list.array[0]->states.list.array[i]->timeToChange;
        ttime = *(spat->intersections.list.array[0]->states.list.array[i]->pedCount);
        tmpLightState.straightTime[0] = ttime/65536;
        ttime = ttime%65536;
        tmpLightState.straightTime[1] = ttime/256;
        tmpLightState.straightTime[2] = ttime = ttime%256;

        // Right
        if(spat->intersections.list.array[0]->states.list.array[i]->laneSet.buf[0] != tmpLightState.laneId) {
            return result;
        }

        if((tmpLightState.rightState=ColorIntToEnum(*spat->intersections.list.array[0]->states.list.array[i]->currState)) == error) {
            return result;
        }
        tmpLightState.rightTimeToChange = spat->intersections.list.array[0]->states.list.array[i]->timeToChange;
        ttime = *(spat->intersections.list.array[0]->states.list.array[i]->pedCount);
        tmpLightState.rightTime[0] = ttime/65536;
        ttime = ttime%65536;
        tmpLightState.rightTime[1] = ttime/256;
        tmpLightState.rightTime[2] = ttime = ttime%256;

        result.states.push_back(tmpLightState);
cout<<"success"<<endl;
    }

    ::asn_DEF_SPAT.free_struct(&::asn_DEF_SPAT, spat, 0);
    std::cout<<"spat decode success"<<std::endl;
    return result;
}
