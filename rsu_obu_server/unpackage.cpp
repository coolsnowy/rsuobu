#include "unpackage.h"
#include <fstream>
BsmBlob1 bsmmessage;
Map mapmessage;
TrafficLight spatmessage;
void type_distinguish(uint8_t *data_head,uint8_t *recvbuf)
{
    ofstream in;
    in.open("bsm.txt",ios::out|ios::app);
    cout<<"start type distinguish"<<endl;
    in<<"start type distinguish"<<endl;
    memset(&bsmmessage,0,sizeof(bsmmessage));
    mapmessage.mapId=0;
    memset(&mapmessage.mapCenter,0,sizeof(mapmessage.mapCenter));
    list<Lane>::iterator it=mapmessage.lanes.begin();
    while(it != mapmessage.lanes.end())
    {
        it->laneId=0;
        it->laneCenter.latitude=0;
        it->laneCenter.longitude=0;
        it++;
    }

    spatmessage.mapId=0;
    list<SpatMovementState>::iterator spat_it=spatmessage.states.begin();
    while(spat_it !=spatmessage.states.end())
    {
        spat_it->laneId=0;
        spat_it->rightTimeToChange=0;
        spat_it->straightTimeToChange=0;
        spat_it->leftTimeToChange=0;
        spat_it->rightState=error;
        spat_it->straightState=error;
        spat_it->leftState = error  ;
        int i;
        for(i=0;i<3;i++)
        {
        spat_it->rightTime[i]=0;
        spat_it->straightTime[i]=0;
        spat_it->leftTime[i] = 0;
        }
        spat_it++;
    }
    cout<<"to zero success /t unpacking"<<endl;
    in<<"unpacking"<<endl;

    if (*data_head == 0x59 && *(data_head + 1) == 0x5A)
    {

        cout<<"head right"<<endl;
        in<<"head right"<<endl;
        if (*(data_head + 3) == 0x01)
		{
            cout<<"bsmmessage"<<endl;
            in<<"bsmmessage"<<endl;
            bsmmessage = bsmunpack(recvbuf);
			cout << "bsmmessage" << endl;
			cout << "carId:" << bsmmessage.carId << endl;
			cout << "latitude:" << bsmmessage.latitude << endl;
			cout << "longitude:" << bsmmessage.longitude << endl;
			cout << "speed:" << bsmmessage.speed << endl;
			cout << "heading:" << bsmmessage.heading << endl;
			cout << "acceleration:" << bsmmessage.acceleration << endl;
			cout << "wheelangle:" << bsmmessage.wheelAngle << endl;
			cout << "carbrake:" << bsmmessage.carBrake << endl;
			cout << "sendtime:";
			char* timeptr;

            in << "bsmmessage" << endl;
            in << "carId:" << bsmmessage.carId << endl;
            in << "latitude:" << bsmmessage.latitude << endl;
            in << "longitude:" << bsmmessage.longitude << endl;
            in << "speed:" << bsmmessage.speed << endl;
            in << "heading:" << bsmmessage.heading << endl;
            in << "acceleration:" << bsmmessage.acceleration << endl;
            in << "wheelangle:" << bsmmessage.wheelAngle << endl;
            in << "carbrake:" << bsmmessage.carBrake << endl;
            in << "sendtime:";

            timeptr = ctime(&(bsmmessage.t));
            while (*timeptr != '\0')
			{
				cout << *timeptr;
                in<<*timeptr;
                timeptr++;
			}
			cout << endl;
            in<<endl;
		}
        if (*(data_head + 3) == 0x02)
		{
            cout<<"map message"<<endl;
            in<<"map message"<<endl;
            mapmessage = mapunpack(recvbuf);
			cout << " mapmessage:" << endl;
			cout << "mapId:" << mapmessage.mapId << endl;
			cout << "mapcenter gps :latitude  :"
					<< mapmessage.mapCenter.latitude << "  longitude:  "
					<< mapmessage.mapCenter.longitude << endl;

            in << " mapmessage:" << endl;
            in << "mapId:" << mapmessage.mapId << endl;
            in << "mapcenter gps :latitude  :"
                    << mapmessage.mapCenter.latitude << "  longitude:  "
                    << mapmessage.mapCenter.longitude << endl;
            list<Lane>::iterator map_iter = mapmessage.lanes.begin();
            for (int num = 0; map_iter != mapmessage.lanes.end(); num++, map_iter++)
			{
                cout << "laneId[" << num + 1 << "]:" << map_iter->laneId << endl;
				cout << "lanecenter [" << num + 1 << "]: latitude "
                        << map_iter->laneCenter.latitude;
                cout << "  longitude:  " << map_iter->laneCenter.longitude << endl;
			}
		}
        if (*(data_head + 3) == 0x03)
		{
            cout<<"spat message"<<endl;
            spatmessage = spatunpack(recvbuf);
            cout << "spatmessage unapckage success:" << endl;
			cout << "mapId :" << spatmessage.mapId << endl;
			list<SpatMovementState>::iterator iter = spatmessage.states.begin();
			for (int num = 0; iter != spatmessage.states.end(); num++, iter++)
			{
                cout<<endl;
				cout << "spat [" << num + 1 << "]:" << endl;
				cout << "laneId:" << iter->laneId << endl;
				cout << "right time to change :" << iter->rightTimeToChange
						<< endl;
				cout << "straight time to change :"
						<< iter->straightTimeToChange << endl;
				cout << "left time to change : " << iter->leftTimeToChange
						<< endl;
				cout << "right state: " << iter->rightState << endl;
				cout << "straight state: " << iter->straightState << endl;
				cout << "left state: " << iter->leftState << endl;
				cout << "right time:" << "greed: " << iter->rightTime[0]
						<< " yellow:" << iter->rightTime[1] << " red:"
						<< iter->rightTime[2] << endl;
				cout << "straight time:" << "greed: " << iter->straightTime[0]
						<< " yellow:" << iter->straightTime[1] << " red:"
						<< iter->straightTime[2] << endl;
				cout << "left time:" << "greed: " << iter->leftTime[0]
						<< " yellow:" << iter->leftTime[1] << " red:"
						<< iter->leftTime[2] << endl;
			}
		}
	}
    else
        {
        cout<<"head error"<<endl;
    }
}
BsmBlob1 bsmunpack(uint8_t buf[])
{

	BsmBlob1 blob;
	int tempcarID = 0;
	int templatitude = 0;
	int templongitude = 0;
	int tempspeed = 0;
	int tempheading = 0;
	int tempacceleration = 0;
	int tempwheelAngle = 0;
	bool tempcarbrake = 0;
    time_t tempt=0;
    int j=0;
    char bu[100] = {0};
	//id (0 - 3)
//	tempcarID = tempcarID | ((int) buf[0]) << 24;
//	tempcarID = tempcarID | ((int) buf[1]) << 16;
//	tempcarID = tempcarID | ((int) buf[2]) << 8;
//	tempcarID = tempcarID | (int) buf[3];
    sscanf(buf,"%[^,]",bu);
    j = strlen(bu);
    tempcarID = atoi(bu);



//	//lat (4 - 7)
//	templatitude = templatitude | ((int) buf[4]) << 24;
//	templatitude = templatitude | ((int) buf[5]) << 16;
//	templatitude = templatitude | ((int) buf[6]) << 8;
//	templatitude = templatitude | (int) buf[7];
    char *str = buf +j-1;
    sscanf(str,"%*[^,],%[^,]",bu);
    j=strlen(bu);
    str += (j-1);
    templatitude = atoi(bu);
	//long (8 - 11)
//	templongitude = templongitude | ((int) buf[8]) << 24;
//	templongitude = templongitude | ((int) buf[9]) << 16;
//	templongitude = templongitude | ((int) buf[10]) << 8;
//	templongitude = templongitude | (int) buf[11];
    sscanf(str,"%*[^,],%[^,]",bu);
    j=strlen(bu);
    str += (j-1);
    templongitude = atoi(bu);

	//speed (12 - 13)
//	tempspeed = tempspeed | ((int) buf[12] & 0x1F) << 8;
//	tempspeed = tempspeed | (int) buf[13];

    sscanf(str,"%*[^,],%[^,]",bu);
    j=strlen(bu);
    str += (j-1);
    tempspeed = atoi(bu);

	//Heading (14 - 15)
//	tempheading = tempheading | ((int) buf[14]) << 8;
//	tempheading = tempheading | (int) buf[15];

    sscanf(str,"%*[^,],%[^,]",bu);
    j=strlen(bu);
    str += (j-1);
    tempheading = atoi(bu);
	//angle (16)
//	tempwheelAngle = tempwheelAngle | (int) buf[16];

    sscanf(str,"%*[^,],%[^,]",bu);
    j=strlen(bu);
    str += (j-1);
    tempwheelAngle = atoi(bu);

	//acceleration (17 - 18)
//	tempacceleration = tempacceleration | ((int) buf[17]) << 8;
//	tempacceleration = tempacceleration | ((int) buf[18]);
    sscanf(str,"%*[^,],%[^,]",bu);
    j=strlen(bu);
    str += (j-1);
    tempacceleration = atoi(bu);

    //carbrake (19)
//	tempcarbrake = tempcarbrake | ((int) buf[19]);
    sscanf(str,"%*[^,],%[^,]",bu);
    j=strlen(bu);
    str += (j-1);
    tempcarBrake = atoi(bu);

	// time_t (20 -23)
//	tempt = tempt | ((int) buf[20]) << 24;
//	tempt = tempt | ((int) buf[21]) << 16;
//	tempt = tempt | ((int) buf[22]) << 8;
//	tempt = tempt | ((int) buf[23]);



	blob.carId = tempcarID;
    blob.latitude = templatitude;
	blob.longitude = templongitude;
	blob.speed = tempspeed;
	blob.heading = tempheading;
	blob.wheelAngle = tempwheelAngle;
	blob.acceleration = tempacceleration;
	blob.carBrake = tempcarbrake;
    //blob.t = tempt;
	return blob;
}
TrafficLight spatunpack(uint8_t recvbuf[])
{
    cout<<"spat message unpacking"<<endl;
	TrafficLight light;
    light.mapId=0;
    uint8_t *buf=recvbuf;
    light.mapId=0;
    light.mapId = light.mapId | ((int32_t) *buf++) << 24;
    light.mapId = light.mapId | ((int32_t) *buf++) << 16;
    light.mapId = light.mapId | ((int32_t) *buf++) << 8;
    light.mapId = light.mapId | ((int32_t) *buf);

    buf=&recvbuf[3];
    while (*++buf !=',')
	{
        SpatMovementState spat;
        memset(&spat,0,sizeof(spat));
        spat.laneId = spat.laneId | ((int32_t) *buf) << 24;
        spat.laneId = spat.laneId | ((int32_t) *++buf) << 16;
        spat.laneId = spat.laneId | ((int32_t) *++buf) << 8;
        spat.laneId = spat.laneId | ((int32_t) *++buf);


        spat.rightTimeToChange = spat.rightTimeToChange | ((int32_t) *++buf) << 24;
        spat.rightTimeToChange = spat.rightTimeToChange | ((int32_t) *++buf) << 16;
        spat.rightTimeToChange = spat.rightTimeToChange | ((int32_t) *++buf) << 8;
        spat.rightTimeToChange = spat.rightTimeToChange | ((int32_t) *++buf);

		spat.straightTimeToChange = spat.straightTimeToChange
                | ((int32_t) *++buf) << 24;
		spat.straightTimeToChange = spat.straightTimeToChange
                | ((int32_t) *++buf) << 16;
		spat.straightTimeToChange = spat.straightTimeToChange
                | ((int32_t) *++buf) << 8;
        spat.straightTimeToChange = spat.straightTimeToChange | ((int32_t) *++buf);

        spat.leftTimeToChange = spat.leftTimeToChange | ((int32_t) *++buf) << 24;
        spat.leftTimeToChange = spat.leftTimeToChange | ((int32_t) *++buf) << 16;
        spat.leftTimeToChange = spat.leftTimeToChange | ((int32_t) *++buf) << 8;
        spat.leftTimeToChange = spat.leftTimeToChange | ((int32_t) *++buf);

        spat.rightState = (enum SpatLightState) ((int32_t) spat.rightState
                | ((int32_t) *++buf) << 24);
        spat.rightState = (enum SpatLightState) ((int32_t) spat.rightState
                | ((int32_t) *++buf) << 16);
        spat.rightState = (enum SpatLightState) ((int32_t) spat.rightState
                | ((int32_t) *++buf) << 8);
        spat.rightState = (enum SpatLightState) ((int32_t) spat.rightState
                | ((int32_t) *++buf));

        spat.straightState = (enum SpatLightState) ((int32_t) spat.straightState
                | ((int32_t) *++buf) << 24);
        spat.straightState = (enum SpatLightState) ((int32_t) spat.straightState
                | ((int32_t) *++buf) << 16);
        spat.straightState = (enum SpatLightState) ((int32_t) spat.straightState
                | ((int32_t) *++buf) << 8);
        spat.straightState = (enum SpatLightState) ((int32_t) spat.straightState
                | ((int32_t) *++buf));


        spat.leftState = (enum SpatLightState) ((int32_t) spat.leftState
                | ((int32_t) *++buf) << 24);
        spat.leftState = (enum SpatLightState) ((int32_t) spat.leftState
                | ((int32_t) *++buf) << 16);
        spat.leftState = (enum SpatLightState) ((int32_t) spat.leftState
                | ((int32_t) *++buf) << 8);
        spat.leftState =(enum SpatLightState) ((int32_t) spat.leftState
                | ((int32_t) *++buf));

        spat.rightTime[0] = spat.rightTime[0] | ((int32_t) *++buf) << 24;
        spat.rightTime[0] = spat.rightTime[0] | ((int32_t) *++buf) << 16;
        spat.rightTime[0] = spat.rightTime[0] | ((int32_t) *++buf) << 8;
        spat.rightTime[0] = spat.rightTime[0] | ((int32_t) *++buf);

        spat.rightTime[1] = spat.rightTime[1] | ((int32_t) *++buf) << 24;
        spat.rightTime[1] = spat.rightTime[1] | ((int32_t) *++buf) << 16;
        spat.rightTime[1] = spat.rightTime[1] | ((int32_t) *++buf) << 8;
        spat.rightTime[1] = spat.rightTime[1] | ((int32_t) *++buf);

        spat.rightTime[2] = spat.rightTime[2] | ((int32_t) *++buf) << 24;
        spat.rightTime[2] = spat.rightTime[2] | ((int32_t) *++buf) << 16;
        spat.rightTime[2] = spat.rightTime[2] | ((int32_t) *++buf) << 8;
        spat.rightTime[2] = spat.rightTime[2] | ((int32_t) *++buf);

        spat.straightTime[0] = spat.straightTime[0] | ((int32_t) *++buf) << 24;
        spat.straightTime[0] = spat.straightTime[0] | ((int32_t) *++buf) << 16;
        spat.straightTime[0] = spat.straightTime[0] | ((int32_t) *++buf) << 8;
        spat.straightTime[0] = spat.straightTime[0] | ((int32_t) *++buf);

        spat.straightTime[1] = spat.straightTime[1] | ((int32_t) *++buf) << 24;
        spat.straightTime[1] = spat.straightTime[1] | ((int32_t) *++buf) << 16;
        spat.straightTime[1] = spat.straightTime[1] | ((int32_t) *++buf) << 8;
        spat.straightTime[1] = spat.straightTime[1] | ((int32_t) *++buf);

        spat.straightTime[2] = spat.straightTime[2] | ((int32_t) *++buf) << 24;
        spat.straightTime[2] = spat.straightTime[2] | ((int32_t) *++buf) << 16;
        spat.straightTime[2] = spat.straightTime[2] | ((int32_t) *++buf) << 8;
        spat.straightTime[2] = spat.straightTime[2] | ((int32_t) *++buf);

        spat.leftTime[0] = spat.leftTime[0] | ((int32_t) *++buf) << 24;
        spat.leftTime[0] = spat.leftTime[0] | ((int32_t) *++buf) << 16;
        spat.leftTime[0] = spat.leftTime[0] | ((int32_t) *++buf) << 8;
        spat.leftTime[0] = spat.leftTime[0] | ((int32_t) *++buf);

        spat.leftTime[1] = spat.leftTime[1] | ((int32_t) *++buf) << 24;
        spat.leftTime[1] = spat.leftTime[1] | ((int32_t) *++buf) << 16;
        spat.leftTime[1] = spat.leftTime[1] | ((int32_t) *++buf) << 8;
        spat.leftTime[1] = spat.leftTime[1] | ((int32_t) *++buf);

        spat.leftTime[2] = spat.leftTime[2] | ((int32_t) *++buf) << 24;
        spat.leftTime[2] = spat.leftTime[2] | ((int32_t) *++buf) << 16;
        spat.leftTime[2] = spat.leftTime[2] | ((int32_t) *++buf) << 8;
        spat.leftTime[2] = spat.leftTime[2] | ((int32_t) *++buf);
//        static int num=0;
//        cout<<++num<<endl;

//        cout<<"right"<<endl;
        light.states.push_back((SpatMovementState)spat);
	}
    cout<<"unpack success!"<<endl;
	return light;
}
Map mapunpack(uint8_t recvbuf[])
{
    cout<<"map message unpack"<<endl;
    Map light;
    memset(&(light.mapCenter),0,sizeof(light.mapCenter));
    light.mapId=0;
    uint8_t *buf=recvbuf;
    light.mapId = light.mapId | ((int32_t) *buf++) << 24;
    light.mapId = light.mapId | ((int32_t) *buf++) << 16;
    light.mapId = light.mapId | ((int32_t) *buf++) << 8;
    light.mapId = light.mapId | ((int32_t) *buf++);
    cout<<"mapId="<<light.mapId<<endl;
    buf=buf-4;
    light.mapCenter.latitude=0;
    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) buf[4]) << 56;
    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) buf[5]) << 48;
    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) buf[6]) << 40;
    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) buf[7]) << 32;
    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) buf[8]) << 24;
    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) buf[9]) << 16;
    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) buf[10]) << 8;
    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) buf[11]);
//    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) recvbuf[4]) << 56;
//    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) recvbuf[5]) << 48;
//    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) recvbuf[6]) << 40;
//    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) recvbuf[7]) << 32;
//    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) recvbuf[8]) << 24;
//    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) recvbuf[9]) << 16;
//    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) recvbuf[10]) << 8;
//    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) recvbuf[11]);

//    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) *buf++) << 56;
//    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) *buf++) << 48;
//    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) *buf++) << 40;
//    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) *buf++) << 32;
//    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) *buf++) << 24;
//    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) *buf++) << 16;
//    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) *buf++) << 8;
//    light.mapCenter.latitude = light.mapCenter.latitude | ((int64_t) *buf++);
    cout<<"laitude="<<light.mapCenter.latitude<<endl;
    buf+=12;

    light.mapCenter.longitude = light.mapCenter.longitude | ((int64_t) *buf++) << 56;
    light.mapCenter.longitude = light.mapCenter.longitude | ((int64_t) *buf++) << 48;
    light.mapCenter.longitude = light.mapCenter.longitude | ((int64_t) *buf++) << 40;
    light.mapCenter.longitude = light.mapCenter.longitude | ((int64_t) *buf++) << 32;
    light.mapCenter.longitude = light.mapCenter.longitude | ((int64_t) *buf++) << 24;
    light.mapCenter.longitude = light.mapCenter.longitude | ((int64_t) *buf++) << 16;
    light.mapCenter.longitude = light.mapCenter.longitude | ((int64_t) *buf++) << 8;
    light.mapCenter.longitude = light.mapCenter.longitude | ((int64_t) *buf);
    cout<<"longitude="<<light.mapCenter.longitude<<endl;

    buf=recvbuf+19;
    while (*++buf != ',' )
	{
        struct Lane lane;

        lane.laneId = lane.laneId | ((int64_t) *buf) << 56;
        lane.laneId = lane.laneId | ((int64_t) *++buf) << 48;
        lane.laneId = lane.laneId | ((int64_t) *++buf) << 40;
        lane.laneId = lane.laneId | ((int64_t) *++buf) << 32;
        lane.laneId = lane.laneId | ((int64_t) *++buf) << 24;
        lane.laneId = lane.laneId | ((int64_t) *++buf) << 16;
        lane.laneId = lane.laneId | ((int64_t) *++buf) << 8;
        lane.laneId = lane.laneId | ((int64_t) *++buf);

        lane.laneCenter.latitude = lane.laneCenter.latitude
                | ((int64_t) *++buf) << 56;
        lane.laneCenter.latitude = lane.laneCenter.latitude
                | ((int64_t) *++buf) << 48;
        lane.laneCenter.latitude = lane.laneCenter.latitude
                | ((int64_t) *++buf) << 40;
        lane.laneCenter.latitude = lane.laneCenter.latitude
                | ((int64_t) *++buf) << 32;
		lane.laneCenter.latitude = lane.laneCenter.latitude
                | ((int64_t) *++buf) << 24;
		lane.laneCenter.latitude = lane.laneCenter.latitude
                | ((int64_t) *++buf) << 16;
		lane.laneCenter.latitude = lane.laneCenter.latitude
                | ((int64_t) *++buf) << 8;
        lane.laneCenter.latitude = lane.laneCenter.latitude
                | ((int64_t) *++buf);



        lane.laneCenter.longitude = lane.laneCenter.longitude
                | ((int64_t) *++buf) << 56;
        lane.laneCenter.longitude = lane.laneCenter.longitude
                | ((int64_t) *++buf) << 48;
        lane.laneCenter.longitude = lane.laneCenter.longitude
                | ((int64_t) *++buf) << 40;
        lane.laneCenter.longitude = lane.laneCenter.longitude
                | ((int64_t) *++buf) << 32;
		lane.laneCenter.longitude = lane.laneCenter.longitude
                | ((int64_t) *++buf) << 24;
		lane.laneCenter.longitude = lane.laneCenter.longitude
                | ((int64_t) *++buf) << 16;
		lane.laneCenter.longitude = lane.laneCenter.longitude
                | ((int64_t) *++buf) << 8;
        lane.laneCenter.longitude = lane.laneCenter.longitude
                | ((int64_t) *++buf);

        light.lanes.push_back((Lane)lane);
        static int slc=0;
        ++slc;
        cout<<slc<<endl;
        cout<<"unpack success"<<endl;

	}
    return light;

}



















