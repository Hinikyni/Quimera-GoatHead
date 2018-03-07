#ifndef _ROS_cob_android_msgs_orderResult_h
#define _ROS_cob_android_msgs_orderResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace cob_android_msgs
{

  class orderResult : public ros::Msg
  {
    public:
      typedef int16_t _error_code_type;
      _error_code_type error_code;

    orderResult():
      error_code(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_error_code;
      u_error_code.real = this->error_code;
      *(outbuffer + offset + 0) = (u_error_code.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_error_code.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->error_code);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_error_code;
      u_error_code.base = 0;
      u_error_code.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_error_code.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->error_code = u_error_code.real;
      offset += sizeof(this->error_code);
     return offset;
    }

    const char * getType(){ return "cob_android_msgs/orderResult"; };
    const char * getMD5(){ return "d6893539232537f3fa191600390ad3e0"; };

  };

}
#endif