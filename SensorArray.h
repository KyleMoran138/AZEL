#ifndef SENSORARRAY_H
#define SENSORARRAY_H
#include "Arduino.h"
#include "Sensor.h"

class SensorArray{
  
  public:
    float* allSensorValues;

    SensorArray(Sensor **Sensors, int sensorCount);
    SensorArray(Sensor **Sensors, int sensorCount, float perSensorTol, bool invertResults);
    float getSensorValue(int sensor);
    void readAllSensorValues();
    void calculateAngle();
    int getSensorTurnDirection(int forwardSensorIndex, float target);
    void getDistanceToRotateBy(int forwardSensorIndex, float target);
    
  private:
    float  _PER_SENSOR_TOLERANCE = 50;
    int _sensorCount;
    int _id;
    bool _INVERT_RESULTS = false;
    Sensor  **_allSensors;
  
};
#endif
