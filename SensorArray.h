#ifndef SENSORARRAY_H
#define SENSORARRAY_H
#include "Arduino.h"
#include "Sensor.h"

class SensorArray{
  
  public:
    float** allSensorValues;

    SensorArray(Sensor **Sensors, int sensorCount);
    SensorArray(Sensor **Sensors, int sensorCount, float perSensorTol, bool invertResults); 
    void readRollingAverage();
    void readAllSensorValues();
    void calculateAngle();
    int getSensorDownIndex(int currentSensor, bool respectPosition);
    int getSensorUpIndex(int currentSensor, bool respectPosition);
    int getSensorTurnDirection(int forwardSensorIndex, float target);
    float getDistanceToRotateBy(int forwardSensorIndex, float target, int directionToRotate);
    float getSensorValue(int sensor, int periodIndex);

    
  private:
    float  _PER_SENSOR_TOLERANCE = 50;
    int _sensorCount;
    int _id;
    bool _INVERT_RESULTS = false;
    const int _ROLLING_AVERAGE_PERIOD_COUNT = 10;
    const int _ROLLING_AVERAGE_PERIOD_TIME = 100; // In milliseconds
    int _CURRENT_ROLLING_PERIOD = 0;
    Sensor  **_allSensors;
    void _initSensorArrays(int sensorCount);
    void _stepRollingAveragePeriod();
  
};
#endif
