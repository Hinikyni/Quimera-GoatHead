#ifndef _ROS_auv_msgs_WorldWaypointRequest_h
#define _ROS_auv_msgs_WorldWaypointRequest_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "auv_msgs/NED.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Twist.h"

namespace auv_msgs
{

  class WorldWaypointRequest : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef auv_msgs::NED _position_type;
      _position_type position;
      typedef geometry_msgs::Vector3 _orientation_type;
      _orientation_type orientation;
      bool disable_axis[6];
      typedef geometry_msgs::Vector3 _position_tolerance_type;
      _position_tolerance_type position_tolerance;
      typedef geometry_msgs::Vector3 _orientation_tolerance_type;
      _orientation_tolerance_type orientation_tolerance;
      typedef geometry_msgs::Twist _twist_limit_type;
      _twist_limit_type twist_limit;

    WorldWaypointRequest():
      header(),
      position(),
      orientation(),
      disable_axis(),
      position_tolerance(),
      orientation_tolerance(),
      twist_limit()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->position.serialize(outbuffer + offset);
      offset += this->orientation.serialize(outbuffer + offset);
      for( uint32_t i = 0; i < 6; i++){
      union {
        bool real;
        uint8_t base;
      } u_disable_axisi;
      u_disable_axisi.real = this->disable_axis[i];
      *(outbuffer + offset + 0) = (u_disable_axisi.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->disable_axis[i]);
      }
      offset += this->position_tolerance.serialize(outbuffer + offset);
      offset += this->orientation_tolerance.serialize(outbuffer + offset);
      offset += this->twist_limit.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->position.deserialize(inbuffer + offset);
      offset += this->orientation.deserialize(inbuffer + offset);
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
      offset += this->position_tolerance.deserialize(inbuffer + offset);
      offset += this->orientation_tolerance.deserialize(inbuffer + offset);
      offset += this->twist_limit.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "auv_msgs/WorldWaypointRequest"; };
    const char * getMD5(){ return "cb80c1e42bc09e9c27be72f3245795c3"; };

  };

}
#endif