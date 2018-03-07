#ifndef _ROS_cob_pick_place_action_CobPickAction_h
#define _ROS_cob_pick_place_action_CobPickAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "cob_pick_place_action/CobPickActionGoal.h"
#include "cob_pick_place_action/CobPickActionResult.h"
#include "cob_pick_place_action/CobPickActionFeedback.h"

namespace cob_pick_place_action
{

  class CobPickAction : public ros::Msg
  {
    public:
      typedef cob_pick_place_action::CobPickActionGoal _action_goal_type;
      _action_goal_type action_goal;
      typedef cob_pick_place_action::CobPickActionResult _action_result_type;
      _action_result_type action_result;
      typedef cob_pick_place_action::CobPickActionFeedback _action_feedback_type;
      _action_feedback_type action_feedback;

    CobPickAction():
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

    const char * getType(){ return "cob_pick_place_action/CobPickAction"; };
    const char * getMD5(){ return "d69a9888fbb24a37fc236861fab099ce"; };

  };

}
#endif