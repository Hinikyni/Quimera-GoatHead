#ifndef _ROS_SERVICE_GetFootprint_h
#define _ROS_SERVICE_GetFootprint_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/PolygonStamped.h"
#include "std_msgs/Bool.h"

namespace cob_footprint_observer
{

static const char GETFOOTPRINT[] = "cob_footprint_observer/GetFootprint";

  class GetFootprintRequest : public ros::Msg
  {
    public:

    GetFootprintRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return GETFOOTPRINT; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetFootprintResponse : public ros::Msg
  {
    public:
      typedef geometry_msgs::PolygonStamped _footprint_type;
      _footprint_type footprint;
      typedef std_msgs::Bool _success_type;
      _success_type success;

    GetFootprintResponse():
      footprint(),
      success()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->footprint.serialize(outbuffer + offset);
      offset += this->success.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->footprint.deserialize(inbuffer + offset);
      offset += this->success.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return GETFOOTPRINT; };
    const char * getMD5(){ return "f40d48f5ad16c4c6dbedafd967306675"; };

  };

  class GetFootprint {
    public:
    typedef GetFootprintRequest Request;
    typedef GetFootprintResponse Response;
  };

}
#endif
