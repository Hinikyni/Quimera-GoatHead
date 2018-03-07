#ifndef _ROS_cob_msgs_PowerState_h
#define _ROS_cob_msgs_PowerState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace cob_msgs
{

  class PowerState : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef float _voltage_type;
      _voltage_type voltage;
      typedef float _current_type;
      _current_type current;
      typedef float _power_consumption_type;
      _power_consumption_type power_consumption;
      typedef float _remaining_capacity_type;
      _remaining_capacity_type remaining_capacity;
      typedef float _relative_remaining_capacity_type;
      _relative_remaining_capacity_type relative_remaining_capacity;
      typedef bool _charging_type;
      _charging_type charging;
      typedef float _time_remaining_type;
      _time_remaining_type time_remaining;
      typedef float _temperature_type;
      _temperature_type temperature;

    PowerState():
      header(),
      voltage(0),
      current(0),
      power_consumption(0),
      remaining_capacity(0),
      relative_remaining_capacity(0),
      charging(0),
      time_remaining(0),
      temperature(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->voltage);
      offset += serializeAvrFloat64(outbuffer + offset, this->current);
      offset += serializeAvrFloat64(outbuffer + offset, this->power_consumption);
      offset += serializeAvrFloat64(outbuffer + offset, this->remaining_capacity);
      offset += serializeAvrFloat64(outbuffer + offset, this->relative_remaining_capacity);
      union {
        bool real;
        uint8_t base;
      } u_charging;
      u_charging.real = this->charging;
      *(outbuffer + offset + 0) = (u_charging.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->charging);
      offset += serializeAvrFloat64(outbuffer + offset, this->time_remaining);
      offset += serializeAvrFloat64(outbuffer + offset, this->temperature);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->voltage));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->current));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->power_consumption));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->remaining_capacity));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->relative_remaining_capacity));
      union {
        bool real;
        uint8_t base;
      } u_charging;
      u_charging.base = 0;
      u_charging.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->charging = u_charging.real;
      offset += sizeof(this->charging);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->time_remaining));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->temperature));
     return offset;
    }

    const char * getType(){ return "cob_msgs/PowerState"; };
    const char * getMD5(){ return "70361e18e36187b93dab6d6ec8ca15e4"; };

  };

}
#endif