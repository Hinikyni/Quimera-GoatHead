#ifndef _ROS_cob_grasp_generation_QueryGraspsGoal_h
#define _ROS_cob_grasp_generation_QueryGraspsGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace cob_grasp_generation
{

  class QueryGraspsGoal : public ros::Msg
  {
    public:
      typedef const char* _object_name_type;
      _object_name_type object_name;
      typedef const char* _gripper_type_type;
      _gripper_type_type gripper_type;
      typedef const char* _gripper_side_type;
      _gripper_side_type gripper_side;
      typedef uint32_t _grasp_id_type;
      _grasp_id_type grasp_id;
      typedef uint32_t _num_grasps_type;
      _num_grasps_type num_grasps;
      typedef float _threshold_type;
      _threshold_type threshold;

    QueryGraspsGoal():
      object_name(""),
      gripper_type(""),
      gripper_side(""),
      grasp_id(0),
      num_grasps(0),
      threshold(0)
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
      uint32_t length_gripper_side = strlen(this->gripper_side);
      varToArr(outbuffer + offset, length_gripper_side);
      offset += 4;
      memcpy(outbuffer + offset, this->gripper_side, length_gripper_side);
      offset += length_gripper_side;
      *(outbuffer + offset + 0) = (this->grasp_id >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->grasp_id >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->grasp_id >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->grasp_id >> (8 * 3)) & 0xFF;
      offset += sizeof(this->grasp_id);
      *(outbuffer + offset + 0) = (this->num_grasps >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->num_grasps >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->num_grasps >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->num_grasps >> (8 * 3)) & 0xFF;
      offset += sizeof(this->num_grasps);
      offset += serializeAvrFloat64(outbuffer + offset, this->threshold);
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
      uint32_t length_gripper_side;
      arrToVar(length_gripper_side, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_gripper_side; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_gripper_side-1]=0;
      this->gripper_side = (char *)(inbuffer + offset-1);
      offset += length_gripper_side;
      this->grasp_id =  ((uint32_t) (*(inbuffer + offset)));
      this->grasp_id |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->grasp_id |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->grasp_id |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->grasp_id);
      this->num_grasps =  ((uint32_t) (*(inbuffer + offset)));
      this->num_grasps |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->num_grasps |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->num_grasps |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->num_grasps);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->threshold));
     return offset;
    }

    const char * getType(){ return "cob_grasp_generation/QueryGraspsGoal"; };
    const char * getMD5(){ return "2aaeac295326ed87cc4e63f737837d1f"; };

  };

}
#endif