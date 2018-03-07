#ifndef _ROS_robotnik_msgs_MotorStatus_h
#define _ROS_robotnik_msgs_MotorStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace robotnik_msgs
{

  class MotorStatus : public ros::Msg
  {
    public:
      typedef const char* _state_type;
      _state_type state;
      typedef const char* _status_type;
      _status_type status;
      typedef const char* _statusword_type;
      _statusword_type statusword;
      typedef const char* _driveflags_type;
      _driveflags_type driveflags;

    MotorStatus():
      state(""),
      status(""),
      statusword(""),
      driveflags("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_state = strlen(this->state);
      varToArr(outbuffer + offset, length_state);
      offset += 4;
      memcpy(outbuffer + offset, this->state, length_state);
      offset += length_state;
      uint32_t length_status = strlen(this->status);
      varToArr(outbuffer + offset, length_status);
      offset += 4;
      memcpy(outbuffer + offset, this->status, length_status);
      offset += length_status;
      uint32_t length_statusword = strlen(this->statusword);
      varToArr(outbuffer + offset, length_statusword);
      offset += 4;
      memcpy(outbuffer + offset, this->statusword, length_statusword);
      offset += length_statusword;
      uint32_t length_driveflags = strlen(this->driveflags);
      varToArr(outbuffer + offset, length_driveflags);
      offset += 4;
      memcpy(outbuffer + offset, this->driveflags, length_driveflags);
      offset += length_driveflags;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_state;
      arrToVar(length_state, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_state; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_state-1]=0;
      this->state = (char *)(inbuffer + offset-1);
      offset += length_state;
      uint32_t length_status;
      arrToVar(length_status, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_status; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_status-1]=0;
      this->status = (char *)(inbuffer + offset-1);
      offset += length_status;
      uint32_t length_statusword;
      arrToVar(length_statusword, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_statusword; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_statusword-1]=0;
      this->statusword = (char *)(inbuffer + offset-1);
      offset += length_statusword;
      uint32_t length_driveflags;
      arrToVar(length_driveflags, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_driveflags; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_driveflags-1]=0;
      this->driveflags = (char *)(inbuffer + offset-1);
      offset += length_driveflags;
     return offset;
    }

    const char * getType(){ return "robotnik_msgs/MotorStatus"; };
    const char * getMD5(){ return "bf902392cd07d79e1d1294bfae19e58e"; };

  };

}
#endif