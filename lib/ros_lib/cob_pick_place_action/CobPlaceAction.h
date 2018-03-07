#ifndef _ROS_cob_pick_place_action_CobPlaceAction_h
#define _ROS_cob_pick_place_action_CobPlaceAction_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "cob_pick_place_action/CobPlaceActionGoal.h"
#include "cob_pick_place_action/CobPlaceActionResult.h"
#include "cob_pick_place_action/CobPlaceActionFeedback.h"

namespace cob_pick_place_action
{

  class CobPlaceAction : public ros::Msg
  {
    public:
      typedef cob_pick_place_action::CobPlaceActionGoal _action_goal_type;
      _action_goal_type action_goal;
      typedef cob_pick_place_action::CobPlaceActionResult _action_result_type;
      _action_result_type action_result;
      typedef cob_pick_place_action::CobPlaceActionFeedback _action_feedback_type;
      _action_feedback_type action_feedback;

    CobPlaceAction():
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

    const char * getType(){ return "cob_pick_place_action/CobPlaceAction"; };
    const char * getMD5(){ return "3111cd554bb468b33adbd6c714aa6b1a"; };

  };

}
#endif