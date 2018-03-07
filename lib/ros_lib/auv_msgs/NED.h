#ifndef _ROS_auv_msgs_NED_h
#define _ROS_auv_msgs_NED_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace auv_msgs
{

  class NED : public ros::Msg
  {
    public:
      typedef float _north_type;
      _north_type north;
      typedef float _east_type;
      _east_type east;
      typedef float _depth_type;
      _depth_type depth;

    NED():
      north(0),
      east(0),
      depth(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->north);
      offset += serializeAvrFloat64(outbuffer + offset, this->east);
      offset += serializeAvrFloat64(outbuffer + offset, this->depth);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->north));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->east));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->depth));
     return offset;
    }

    const char * getType(){ return "auv_msgs/NED"; };
    const char * getMD5(){ return "4a16ce817ea5a7912b32dfb04540797b"; };

  };

}
#endif