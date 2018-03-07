#ifndef _ROS_auv_msgs_NavigationStatus_h
#define _ROS_auv_msgs_NavigationStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geographic_msgs/GeoPoint.h"
#include "auv_msgs/NED.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Vector3.h"

namespace auv_msgs
{

  class NavigationStatus : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef geographic_msgs::GeoPoint _global_position_type;
      _global_position_type global_position;
      typedef geographic_msgs::GeoPoint _origin_type;
      _origin_type origin;
      typedef auv_msgs::NED _position_type;
      _position_type position;
      typedef float _altitude_type;
      _altitude_type altitude;
      typedef geometry_msgs::Point _body_velocity_type;
      _body_velocity_type body_velocity;
      typedef geometry_msgs::Point _seafloor_velocity_type;
      _seafloor_velocity_type seafloor_velocity;
      typedef geometry_msgs::Vector3 _orientation_type;
      _orientation_type orientation;
      typedef geometry_msgs::Vector3 _orientation_rate_type;
      _orientation_rate_type orientation_rate;
      typedef auv_msgs::NED _position_variance_type;
      _position_variance_type position_variance;
      typedef geometry_msgs::Vector3 _orientation_variance_type;
      _orientation_variance_type orientation_variance;
      typedef uint8_t _status_type;
      _status_type status;
      enum { STATUS_FAULT =  0 };
      enum { STATUS_LOCAL_FRAME_OK =  1 };
      enum { STATUS_GLOBAL_FRAME_OK =  2 };
      enum { STATUS_POSITION_OK =  3 };
      enum { STATUS_ESTIMATION_ERROR_OK =  8 };
      enum { STATUS_WATER_VELOCITY_OK =  16 };
      enum { STATUS_GROUND_VELOCITY_OK =  32 };
      enum { STATUS_VELOCITY_OK =  48 };
      enum { STATUS_ALL_OK =  59 };

    NavigationStatus():
      header(),
      global_position(),
      origin(),
      position(),
      altitude(0),
      body_velocity(),
      seafloor_velocity(),
      orientation(),
      orientation_rate(),
      position_variance(),
      orientation_variance(),
      status(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->global_position.serialize(outbuffer + offset);
      offset += this->origin.serialize(outbuffer + offset);
      offset += this->position.serialize(outbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_altitude;
      u_altitude.real = this->altitude;
      *(outbuffer + offset + 0) = (u_altitude.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_altitude.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_altitude.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_altitude.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->altitude);
      offset += this->body_velocity.serialize(outbuffer + offset);
      offset += this->seafloor_velocity.serialize(outbuffer + offset);
      offset += this->orientation.serialize(outbuffer + offset);
      offset += this->orientation_rate.serialize(outbuffer + offset);
      offset += this->position_variance.serialize(outbuffer + offset);
      offset += this->orientation_variance.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->status >> (8 * 0)) & 0xFF;
      offset += sizeof(this->status);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->global_position.deserialize(inbuffer + offset);
      offset += this->origin.deserialize(inbuffer + offset);
      offset += this->position.deserialize(inbuffer + offset);
      union {
        float real;
        uint32_t base;
      } u_altitude;
      u_altitude.base = 0;
      u_altitude.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_altitude.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_altitude.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_altitude.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->altitude = u_altitude.real;
      offset += sizeof(this->altitude);
      offset += this->body_velocity.deserialize(inbuffer + offset);
      offset += this->seafloor_velocity.deserialize(inbuffer + offset);
      offset += this->orientation.deserialize(inbuffer + offset);
      offset += this->orientation_rate.deserialize(inbuffer + offset);
      offset += this->position_variance.deserialize(inbuffer + offset);
      offset += this->orientation_variance.deserialize(inbuffer + offset);
      this->status =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->status);
     return offset;
    }

    const char * getType(){ return "auv_msgs/NavigationStatus"; };
    const char * getMD5(){ return "3b6f0debc53f1eacc07c1295f8c6666a"; };

  };

}
#endif