#ifndef SENSOR_H
#define SENSOR_H
#include "Arduino.h"

class Sensor{
  public: 
    float value;

    Sensor();
    Sensor(int pin_id, float pos);
    Sensor(int pin_id, float pos, float weight);
    float readFloat();
    
    // Difference between the sensor before this one and after
    float d_u;
    float d_d;

    // Is difference up grater than || less than individual tolerance
    bool d_u_gt;
    bool d_u_lt;

    // Is difference down grater than || less than individual tolerance
    bool d_d_gt;
    bool d_d_lt;

    float pos;

    float getValueChangePerDistanceUnit(Sensor* sensorTwo);
    bool SensorDifferenceSumZero();

  protected:
    int   _pin_id;
    float _weight;
};
#endif
