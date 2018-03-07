#ifndef _ROS_auv_msgs_VehiclePose_h
#define _ROS_auv_msgs_VehiclePose_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "auv_msgs/NED.h"
#include "geometry_msgs/Vector3.h"

namespace auv_msgs
{

  class VehiclePose : public ros::Msg
  {
    public:
      typedef const char* _id_type;
      _id_type id;
      typedef auv_msgs::NED _position_type;
      _position_type position;
      typedef geometry_msgs::Vector3 _orientation_type;
      _orientation_type orientation;

    VehiclePose():
      id(""),
      position(),
      orientation()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_id = strlen(this->id);
      varToArr(outbuffer + offset, length_id);
      offset += 4;
      memcpy(outbuffer + offset, this->id, length_id);
      offset += length_id;
      offset += this->position.serialize(outbuffer + offset);
      offset += this->orientation.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_id;
      arrToVar(length_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_id-1]=0;
      this->id = (char *)(inbuffer + offset-1);
      offset += length_id;
      offset += this->position.deserialize(inbuffer + offset);
      offset += this->orientation.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "auv_msgs/VehiclePose"; };
    const char * getMD5(){ return "7d95e36a3a6c27d76fa9dfc44de996fd"; };

  };

}
#endif