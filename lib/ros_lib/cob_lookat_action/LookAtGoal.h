#ifndef _ROS_cob_lookat_action_LookAtGoal_h
#define _ROS_cob_lookat_action_LookAtGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace cob_lookat_action
{

  class LookAtGoal : public ros::Msg
  {
    public:
      typedef const char* _target_frame_type;
      _target_frame_type target_frame;
      typedef const char* _pointing_frame_type;
      _pointing_frame_type pointing_frame;
      typedef uint8_t _pointing_axis_type_type;
      _pointing_axis_type_type pointing_axis_type;
      enum { X_POSITIVE =  0 };
      enum { Y_POSITIVE =  1 };
      enum { Z_POSITIVE =  2 };
      enum { X_NEGATIVE =  3 };
      enum { Y_NEGATIVE =  4 };
      enum { Z_NEGATIVE =  5 };

    LookAtGoal():
      target_frame(""),
      pointing_frame(""),
      pointing_axis_type(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_target_frame = strlen(this->target_frame);
      varToArr(outbuffer + offset, length_target_frame);
      offset += 4;
      memcpy(outbuffer + offset, this->target_frame, length_target_frame);
      offset += length_target_frame;
      uint32_t length_pointing_frame = strlen(this->pointing_frame);
      varToArr(outbuffer + offset, length_pointing_frame);
      offset += 4;
      memcpy(outbuffer + offset, this->pointing_frame, length_pointing_frame);
      offset += length_pointing_frame;
      *(outbuffer + offset + 0) = (this->pointing_axis_type >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pointing_axis_type);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_target_frame;
      arrToVar(length_target_frame, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_target_frame; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_target_frame-1]=0;
      this->target_frame = (char *)(inbuffer + offset-1);
      offset += length_target_frame;
      uint32_t length_pointing_frame;
      arrToVar(length_pointing_frame, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_pointing_frame; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_pointing_frame-1]=0;
      this->pointing_frame = (char *)(inbuffer + offset-1);
      offset += length_pointing_frame;
      this->pointing_axis_type =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->pointing_axis_type);
     return offset;
    }

    const char * getType(){ return "cob_lookat_action/LookAtGoal"; };
    const char * getMD5(){ return "c7ecadab6e81f87b503d0594e7622cbb"; };

  };

}
#endif