#ifndef _ROS_SERVICE_ScreenControl_h
#define _ROS_SERVICE_ScreenControl_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace cob_android_msgs
{

static const char SCREENCONTROL[] = "cob_android_msgs/ScreenControl";

  class ScreenControlRequest : public ros::Msg
  {
    public:
      typedef uint8_t _screen_mode_type;
      _screen_mode_type screen_mode;
      enum { SCREEN_STANDBY =  0 };
      enum { SCREEN_ORDER =  1 };
      enum { SCREEN_MOVE =  2 };
      enum { SCREEN_DRAGDROP =  3 };

    ScreenControlRequest():
      screen_mode(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->screen_mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->screen_mode);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->screen_mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->screen_mode);
     return offset;
    }

    const char * getType(){ return SCREENCONTROL; };
    const char * getMD5(){ return "2d82e562f2705eee8f3013d5eedfac9c"; };

  };

  class ScreenControlResponse : public ros::Msg
  {
    public:
      typedef uint8_t _active_screen_type;
      _active_screen_type active_screen;
      typedef uint8_t _last_screen_type;
      _last_screen_type last_screen;

    ScreenControlResponse():
      active_screen(0),
      last_screen(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->active_screen >> (8 * 0)) & 0xFF;
      offset += sizeof(this->active_screen);
      *(outbuffer + offset + 0) = (this->last_screen >> (8 * 0)) & 0xFF;
      offset += sizeof(this->last_screen);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->active_screen =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->active_screen);
      this->last_screen =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->last_screen);
     return offset;
    }

    const char * getType(){ return SCREENCONTROL; };
    const char * getMD5(){ return "d36239844e9a143b63069ea7ed0954e6"; };

  };

  class ScreenControl {
    public:
    typedef ScreenControlRequest Request;
    typedef ScreenControlResponse Response;
  };

}
#endif
