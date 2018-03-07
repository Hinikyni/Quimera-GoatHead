#ifndef _ROS_cartesian_msgs_CartesianCommand_h
#define _ROS_cartesian_msgs_CartesianCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/PoseStamped.h"

namespace cartesian_msgs
{

  class CartesianCommand : public ros::Msg
  {
    public:
      typedef geometry_msgs::PoseStamped _desired_pose_type;
      _desired_pose_type desired_pose;
      typedef float _duration_type;
      _duration_type duration;

    CartesianCommand():
      desired_pose(),
      duration(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->desired_pose.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_duration;
      u_duration.real = this->duration;
      *(outbuffer + offset + 0) = (u_duration.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_duration.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_duration.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_duration.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->duration);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->desired_pose.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_duration;
      u_duration.base = 0;
      u_duration.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_duration.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_duration.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_duration.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->duration = u_duration.real;
      offset += sizeof(this->duration);
     return offset;
    }

    const char * getType(){ return "cartesian_msgs/CartesianCommand"; };
    const char * getMD5(){ return "a31a4a0425243aea0432892b39849f76"; };

  };

}
#endif