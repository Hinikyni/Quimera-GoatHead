#ifndef _ROS_cob_grasp_generation_GenerateGraspsGoal_h
#define _ROS_cob_grasp_generation_GenerateGraspsGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace cob_grasp_generation
{

  class GenerateGraspsGoal : public ros::Msg
  {
    public:
      typedef const char* _object_name_type;
      _object_name_type object_name;
      typedef const char* _gripper_type_type;
      _gripper_type_type gripper_type;
      typedef bool _replan_type;
      _replan_type replan;
      typedef bool _viewer_type;
      _viewer_type viewer;

    GenerateGraspsGoal():
      object_name(""),
      gripper_type(""),
      replan(0),
      viewer(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_object_name = strlen(this->object_name);
      varToArr(outbuffer + offset, length_object_name);
      offset += 4;
      memcpy(outbuffer + offset, this->object_name, length_object_name);
      offset += length_object_name;
      uint32_t length_gripper_type = strlen(this->gripper_type);
      varToArr(outbuffer + offset, length_gripper_type);
      offset += 4;
      memcpy(outbuffer + offset, this->gripper_type, length_gripper_type);
      offset += length_gripper_type;
      union {
        bool real;
        uint8_t base;
      } u_replan;
      u_replan.real = this->replan;
      *(outbuffer + offset + 0) = (u_replan.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->replan);
      union {
        bool real;
        uint8_t base;
      } u_viewer;
      u_viewer.real = this->viewer;
      *(outbuffer + offset + 0) = (u_viewer.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->viewer);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_object_name;
      arrToVar(length_object_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_object_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_object_name-1]=0;
      this->object_name = (char *)(inbuffer + offset-1);
      offset += length_object_name;
      uint32_t length_gripper_type;
      arrToVar(length_gripper_type, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_gripper_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_gripper_type-1]=0;
      this->gripper_type = (char *)(inbuffer + offset-1);
      offset += length_gripper_type;
      union {
        bool real;
        uint8_t base;
      } u_replan;
      u_replan.base = 0;
      u_replan.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->replan = u_replan.real;
      offset += sizeof(this->replan);
      union {
        bool real;
        uint8_t base;
      } u_viewer;
      u_viewer.base = 0;
      u_viewer.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->viewer = u_viewer.real;
      offset += sizeof(this->viewer);
     return offset;
    }

    const char * getType(){ return "cob_grasp_generation/GenerateGraspsGoal"; };
    const char * getMD5(){ return "94b854875e7b7faa473bfe91df259b3c"; };

  };

}
#endif