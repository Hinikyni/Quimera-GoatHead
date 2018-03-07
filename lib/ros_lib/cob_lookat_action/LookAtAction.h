#ifndef _ROS_cob_lookat_action_LookAtAction_h
#define _ROS_cob_lookat_action_LookAtAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "cob_lookat_action/LookAtActionGoal.h"
#include "cob_lookat_action/LookAtActionResult.h"
#include "cob_lookat_action/LookAtActionFeedback.h"

namespace cob_lookat_action
{

  class LookAtAction : public ros::Msg
  {
    public:
      typedef cob_lookat_action::LookAtActionGoal _action_goal_type;
      _action_goal_type action_goal;
      typedef cob_lookat_action::LookAtActionResult _action_result_type;
      _action_result_type action_result;
      typedef cob_lookat_action::LookAtActionFeedback _action_feedback_type;
      _action_feedback_type action_feedback;

    LookAtAction():
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

    const char * getType(){ return "cob_lookat_action/LookAtAction"; };
    const char * getMD5(){ return "60cd635b33b5dca1b9d438e816920aa1"; };

  };

}
#endif