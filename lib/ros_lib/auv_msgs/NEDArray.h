#ifndef _ROS_auv_msgs_NEDArray_h
#define _ROS_auv_msgs_NEDArray_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "auv_msgs/NED.h"

namespace auv_msgs
{

  class NEDArray : public ros::Msg
  {
    public:
      uint32_t neds_length;
      typedef auv_msgs::NED _neds_type;
      _neds_type st_neds;
      _neds_type * neds;

    NEDArray():
      neds_length(0), neds(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->neds_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->neds_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->neds_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->neds_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->neds_length);
      for( uint32_t i = 0; i < neds_length; i++){
      offset += this->neds[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t neds_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      neds_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      neds_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      neds_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->neds_length);
      if(neds_lengthT > neds_length)
        this->neds = (auv_msgs::NED*)realloc(this->neds, neds_lengthT * sizeof(auv_msgs::NED));
      neds_length = neds_lengthT;
      for( uint32_t i = 0; i < neds_length; i++){
      offset += this->st_neds.deserialize(inbuffer + offset);
        memcpy( &(this->neds[i]), &(this->st_neds), sizeof(auv_msgs::NED));
      }
     return offset;
    }

    const char * getType(){ return "auv_msgs/NEDArray"; };
    const char * getMD5(){ return "bf65cc14ab3d146f950d75ee2723b898"; };

  };

}
#endif