#ifndef _ROS_SERVICE_bin_pose_h
#define _ROS_SERVICE_bin_pose_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"

namespace bin_pose_msgs
{

static const char BIN_POSE[] = "bin_pose_msgs/bin_pose";

  class bin_poseRequest : public ros::Msg
  {
    public:

    bin_poseRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return BIN_POSE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class bin_poseResponse : public ros::Msg
  {
    public:
      typedef geometry_msgs::Pose _grasp_pose_type;
      _grasp_pose_type grasp_pose;
      typedef geometry_msgs::Pose _approach_pose_type;
      _approach_pose_type approach_pose;
      typedef geometry_msgs::Pose _deapproach_pose_type;
      _deapproach_pose_type deapproach_pose;

    bin_poseResponse():
      grasp_pose(),
      approach_pose(),
      deapproach_pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->grasp_pose.serialize(outbuffer + offset);
      offset += this->approach_pose.serialize(outbuffer + offset);
      offset += this->deapproach_pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->grasp_pose.deserialize(inbuffer + offset);
      offset += this->approach_pose.deserialize(inbuffer + offset);
      offset += this->deapproach_pose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return BIN_POSE; };
    const char * getMD5(){ return "79ec9f7617b8c7d8e86e8cc3dedc670f"; };

  };

  class bin_pose {
    public:
    typedef bin_poseRequest Request;
    typedef bin_poseResponse Response;
  };

}
#endif
