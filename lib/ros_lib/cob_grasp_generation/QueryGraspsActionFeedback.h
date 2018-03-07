#ifndef _ROS_cob_grasp_generation_QueryGraspsActionFeedback_h
#define _ROS_cob_grasp_generation_QueryGraspsActionFeedback_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "actionlib_msgs/GoalStatus.h"
#include "cob_grasp_generation/QueryGraspsFeedback.h"

namespace cob_grasp_generation
{

  class QueryGraspsActionFeedback : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef actionlib_msgs::GoalStatus _status_type;
      _status_type status;
      typedef cob_grasp_generation::QueryGraspsFeedback _feedback_type;
      _feedback_type feedback;

    QueryGraspsActionFeedback():
      header(),
      status(),
      feedback()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->status.serialize(outbuffer + offset);
      offset += this->feedback.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->status.deserialize(inbuffer + offset);
      offset += this->feedback.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "cob_grasp_generation/QueryGraspsActionFeedback"; };
    const char * getMD5(){ return "9cb5139df91af03aeb0bb0b4540c91c9"; };

  };

}
#endif