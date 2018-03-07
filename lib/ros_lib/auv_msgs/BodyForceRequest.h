#ifndef _ROS_auv_msgs_BodyForceRequest_h
#define _ROS_auv_msgs_BodyForceRequest_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Wrench.h"

namespace auv_msgs
{

  class BodyForceRequest : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef geometry_msgs::Wrench _wrench_type;
      _wrench_type wrench;
      bool disable_axis[6];

    BodyForceRequest():
      header(),
      wrench(),
      disable_axis()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->wrench.serialize(outbuffer + offset);
      for( uint32_t i = 0; i < 6; i++){
      union {
        bool real;
        uint8_t base;
      } u_disable_axisi;
      u_disable_axisi.real = this->disable_axis[i];
      *(outbuffer + offset + 0) = (u_disable_axisi.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->disable_axis[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->wrench.deserialize(inbuffer + offset);
      for( uint32_t i = 0; i < 6; i++){
      union {
        bool real;
        uint8_t base;
      } u_disable_axisi;
      u_disable_axisi.base = 0;
      u_disable_axisi.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->disable_axis[i] = u_disable_axisi.real;
      offset += sizeof(this->disable_axis[i]);
      }
     return offset;
    }

    const char * getType(){ return "auv_msgs/BodyForceRequest"; };
    const char * getMD5(){ return "0051a8676b62a65bdc9b6410715bfedc"; };

  };

}
#endif