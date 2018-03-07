#ifndef _ROS_cob_grasp_generation_QueryGraspsAction_h
#define _ROS_cob_grasp_generation_QueryGraspsAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "cob_grasp_generation/QueryGraspsActionGoal.h"
#include "cob_grasp_generation/QueryGraspsActionResult.h"
#include "cob_grasp_generation/QueryGraspsActionFeedback.h"

namespace cob_grasp_generation
{

  class QueryGraspsAction : public ros::Msg
  {
    public:
      typedef cob_grasp_generation::QueryGraspsActionGoal _action_goal_type;
      _action_goal_type action_goal;
      typedef cob_grasp_generation::QueryGraspsActionResult _action_result_type;
      _action_result_type action_result;
      typedef cob_grasp_generation::QueryGraspsActionFeedback _action_feedback_type;
      _action_feedback_type action_feedback;

    QueryGraspsAction():
      action_goal(),
      action_result(),
      action_feedback()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->action_goal.serialize(outbuffer + offset);
      offset += this->action_result.serialize(outbuffer + offset);
      offset += this->action_feedback.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->action_goal.deserialize(inbuffer + offset);
      offset += this->action_result.deserialize(inbuffer + offset);
      offset += this->action_feedback.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "cob_grasp_generation/QueryGraspsAction"; };
    const char * getMD5(){ return "d9b14a67440c8782646d37eb58ad1ad6"; };

  };

}
#endif