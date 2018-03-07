#ifndef _ROS_cob_pick_place_action_CobPickGoal_h
#define _ROS_cob_pick_place_action_CobPickGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/PoseStamped.h"

namespace cob_pick_place_action
{

  class CobPickGoal : public ros::Msg
  {
    public:
      typedef uint32_t _object_class_type;
      _object_class_type object_class;
      typedef const char* _object_name_type;
      _object_name_type object_name;
      typedef geometry_msgs::PoseStamped _object_pose_type;
      _object_pose_type object_pose;
      typedef const char* _gripper_type_type;
      _gripper_type_type gripper_type;
      typedef const char* _gripper_side_type;
      _gripper_side_type gripper_side;
      typedef const char* _grasp_database_type;
      _grasp_database_type grasp_database;
      typedef uint32_t _grasp_id_type;
      _grasp_id_type grasp_id;
      typedef const char* _support_surface_type;
      _support_surface_type support_surface;

    CobPickGoal():
      object_class(0),
      object_name(""),
      object_pose(),
      gripper_type(""),
      gripper_side(""),
      grasp_database(""),
      grasp_id(0),
      support_surface("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->object_class >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->object_class >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->object_class >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->object_class >> (8 * 3)) & 0xFF;
      offset += sizeof(this->object_class);
      uint32_t length_object_name = strlen(this->object_name);
      varToArr(outbuffer + offset, length_object_name);
      offset += 4;
      memcpy(outbuffer + offset, this->object_name, length_object_name);
      offset += length_object_name;
      offset += this->object_pose.serialize(outbuffer + offset);
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
      uint32_t length_grasp_database = strlen(this->grasp_database);
      varToArr(outbuffer + offset, length_grasp_database);
      offset += 4;
      memcpy(outbuffer + offset, this->grasp_database, length_grasp_database);
      offset += length_grasp_database;
      *(outbuffer + offset + 0) = (this->grasp_id >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->grasp_id >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->grasp_id >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->grasp_id >> (8 * 3)) & 0xFF;
      offset += sizeof(this->grasp_id);
      uint32_t length_support_surface = strlen(this->support_surface);
      varToArr(outbuffer + offset, length_support_surface);
      offset += 4;
      memcpy(outbuffer + offset, this->support_surface, length_support_surface);
      offset += length_support_surface;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->object_class =  ((uint32_t) (*(inbuffer + offset)));
      this->object_class |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->object_class |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->object_class |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->object_class);
      uint32_t length_object_name;
      arrToVar(length_object_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_object_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_object_name-1]=0;
      this->object_name = (char *)(inbuffer + offset-1);
      offset += length_object_name;
      offset += this->object_pose.deserialize(inbuffer + offset);
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
      uint32_t length_grasp_database;
      arrToVar(length_grasp_database, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_grasp_database; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_grasp_database-1]=0;
      this->grasp_database = (char *)(inbuffer + offset-1);
      offset += length_grasp_database;
      this->grasp_id =  ((uint32_t) (*(inbuffer + offset)));
      this->grasp_id |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->grasp_id |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->grasp_id |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->grasp_id);
      uint32_t length_support_surface;
      arrToVar(length_support_surface, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_support_surface; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_support_surface-1]=0;
      this->support_surface = (char *)(inbuffer + offset-1);
      offset += length_support_surface;
     return offset;
    }

    const char * getType(){ return "cob_pick_place_action/CobPickGoal"; };
    const char * getMD5(){ return "cbe0acd483d6d8f33ac28537b18c7b71"; };

  };

}
#endif