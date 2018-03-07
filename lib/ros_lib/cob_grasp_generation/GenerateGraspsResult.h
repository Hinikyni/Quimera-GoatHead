#ifndef _ROS_cob_grasp_generation_GenerateGraspsResult_h
#define _ROS_cob_grasp_generation_GenerateGraspsResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace cob_grasp_generation
{

  class GenerateGraspsResult : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;
      typedef uint32_t _num_grasps_type;
      _num_grasps_type num_grasps;

    GenerateGraspsResult():
      success(0),
      num_grasps(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      *(outbuffer + offset + 0) = (this->num_grasps >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->num_grasps >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->num_grasps >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->num_grasps >> (8 * 3)) & 0xFF;
      offset += sizeof(this->num_grasps);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
      this->num_grasps =  ((uint32_t) (*(inbuffer + offset)));
      this->num_grasps |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->num_grasps |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->num_grasps |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->num_grasps);
     return offset;
    }

    const char * getType(){ return "cob_grasp_generation/GenerateGraspsResult"; };
    const char * getMD5(){ return "89a93e15e1906977d5060def30025192"; };

  };

}
#endif