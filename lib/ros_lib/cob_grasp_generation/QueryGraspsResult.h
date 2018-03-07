#ifndef _ROS_cob_grasp_generation_QueryGraspsResult_h
#define _ROS_cob_grasp_generation_QueryGraspsResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/Grasp.h"

namespace cob_grasp_generation
{

  class QueryGraspsResult : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;
      uint32_t grasp_list_length;
      typedef moveit_msgs::Grasp _grasp_list_type;
      _grasp_list_type st_grasp_list;
      _grasp_list_type * grasp_list;

    QueryGraspsResult():
      success(0),
      grasp_list_length(0), grasp_list(NULL)
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
      *(outbuffer + offset + 0) = (this->grasp_list_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->grasp_list_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->grasp_list_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->grasp_list_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->grasp_list_length);
      for( uint32_t i = 0; i < grasp_list_length; i++){
      offset += this->grasp_list[i].serialize(outbuffer + offset);
      }
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
      uint32_t grasp_list_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      grasp_list_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      grasp_list_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      grasp_list_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->grasp_list_length);
      if(grasp_list_lengthT > grasp_list_length)
        this->grasp_list = (moveit_msgs::Grasp*)realloc(this->grasp_list, grasp_list_lengthT * sizeof(moveit_msgs::Grasp));
      grasp_list_length = grasp_list_lengthT;
      for( uint32_t i = 0; i < grasp_list_length; i++){
      offset += this->st_grasp_list.deserialize(inbuffer + offset);
        memcpy( &(this->grasp_list[i]), &(this->st_grasp_list), sizeof(moveit_msgs::Grasp));
      }
     return offset;
    }

    const char * getType(){ return "cob_grasp_generation/QueryGraspsResult"; };
    const char * getMD5(){ return "fda0067ecf92d75eb0f0b5f6c25d3d37"; };

  };

}
#endif