#ifndef _ROS_cob_msgs_SiteSurvey_h
#define _ROS_cob_msgs_SiteSurvey_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "cob_msgs/Network.h"

namespace cob_msgs
{

  class SiteSurvey : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t networks_length;
      typedef cob_msgs::Network _networks_type;
      _networks_type st_networks;
      _networks_type * networks;

    SiteSurvey():
      header(),
      networks_length(0), networks(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->networks_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->networks_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->networks_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->networks_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->networks_length);
      for( uint32_t i = 0; i < networks_length; i++){
      offset += this->networks[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t networks_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      networks_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      networks_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      networks_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->networks_length);
      if(networks_lengthT > networks_length)
        this->networks = (cob_msgs::Network*)realloc(this->networks, networks_lengthT * sizeof(cob_msgs::Network));
      networks_length = networks_lengthT;
      for( uint32_t i = 0; i < networks_length; i++){
      offset += this->st_networks.deserialize(inbuffer + offset);
        memcpy( &(this->networks[i]), &(this->st_networks), sizeof(cob_msgs::Network));
      }
     return offset;
    }

    const char * getType(){ return "cob_msgs/SiteSurvey"; };
    const char * getMD5(){ return "f1063b16bb121ef190ae5edfe09d94ec"; };

  };

}
#endif