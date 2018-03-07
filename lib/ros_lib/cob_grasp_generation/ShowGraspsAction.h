#ifndef _ROS_cob_grasp_generation_ShowGraspsAction_h
#define _ROS_cob_grasp_generation_ShowGraspsAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "cob_grasp_generation/ShowGraspsActionGoal.h"
#include "cob_grasp_generation/ShowGraspsActionResult.h"
#include "cob_grasp_generation/ShowGraspsActionFeedback.h"

namespace cob_grasp_generation
{

  class ShowGraspsAction : public ros::Msg
  {
    public:
      typedef cob_grasp_generation::ShowGraspsActionGoal _action_goal_type;
      _action_goal_type action_goal;
      typedef cob_grasp_generation::ShowGraspsActionResult _action_result_type;
      _action_result_type action_result;
      typedef cob_grasp_generation::ShowGraspsActionFeedback _action_feedback_type;
      _action_feedback_type action_feedback;

    ShowGraspsAction():
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

    const char * getType(){ return "cob_grasp_generation/ShowGraspsAction"; };
    const char * getMD5(){ return "156494c0414432ecd331d6133324b528"; };

  };

}
#endif