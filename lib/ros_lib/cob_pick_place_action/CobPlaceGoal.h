#ifndef _ROS_cob_pick_place_action_CobPlaceGoal_h
#define _ROS_cob_pick_place_action_CobPlaceGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/PoseStamped.h"

namespace cob_pick_place_action
{

  class CobPlaceGoal : public ros::Msg
  {
    public:
      typedef uint32_t _object_class_type;
      _object_class_type object_class;
      typedef const char* _object_name_type;
      _object_name_type object_name;
      uint32_t destinations_length;
      typedef geometry_msgs::PoseStamped _destinations_type;
      _destinations_type st_destinations;
      _destinations_type * destinations;
      typedef const char* _support_surface_type;
      _support_surface_type support_surface;

    CobPlaceGoal():
      object_class(0),
      object_name(""),
      destinations_length(0), destinations(NULL),
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
      *(outbuffer + offset + 0) = (this->destinations_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->destinations_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->destinations_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->destinations_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->destinations_length);
      for( uint32_t i = 0; i < destinations_length; i++){
      offset += this->destinations[i].serialize(outbuffer + offset);
      }
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
      uint32_t destinations_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      destinations_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      destinations_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      destinations_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->destinations_length);
      if(destinations_lengthT > destinations_length)
        this->destinations = (geometry_msgs::PoseStamped*)realloc(this->destinations, destinations_lengthT * sizeof(geometry_msgs::PoseStamped));
      destinations_length = destinations_lengthT;
      for( uint32_t i = 0; i < destinations_length; i++){
      offset += this->st_destinations.deserialize(inbuffer + offset);
        memcpy( &(this->destinations[i]), &(this->st_destinations), sizeof(geometry_msgs::PoseStamped));
      }
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

    const char * getType(){ return "cob_pick_place_action/CobPlaceGoal"; };
    const char * getMD5(){ return "eac848fa6d0bba67596f88cde36f673b"; };

  };

}
#endif