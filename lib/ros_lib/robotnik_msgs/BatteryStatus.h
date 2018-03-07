#ifndef _ROS_robotnik_msgs_BatteryStatus_h
#define _ROS_robotnik_msgs_BatteryStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace robotnik_msgs
{

  class BatteryStatus : public ros::Msg
  {
    public:
      typedef float _level_type;
      _level_type level;
      typedef uint32_t _time_remaining_type;
      _time_remaining_type time_remaining;

    BatteryStatus():
      level(0),
      time_remaining(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_level;
      u_level.real = this->level;
      *(outbuffer + offset + 0) = (u_level.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_level.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_level.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_level.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->level);
      *(outbuffer + offset + 0) = (this->time_remaining >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->time_remaining >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->time_remaining >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->time_remaining >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time_remaining);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_level;
      u_level.base = 0;
      u_level.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_level.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_level.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_level.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->level = u_level.real;
      offset += sizeof(this->level);
      this->time_remaining =  ((uint32_t) (*(inbuffer + offset)));
      this->time_remaining |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->time_remaining |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->time_remaining |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->time_remaining);
     return offset;
    }

    const char * getType(){ return "robotnik_msgs/BatteryStatus"; };
    const char * getMD5(){ return "97f2ff224c7220de9e3b44df5993c0f6"; };

  };

}
#endif