#include "Arduino.h";
#include "PhotoResistor.h";

class SensorArray{
  
  public:
    float* allSensorValues;

    SensorArray(Sensor Sensors[], int* sensorCount);
    SensorArray(Sensor Sensors[], int* sensorCount, float perSensorTol,
      float sensorDiffTol, bool invertResults);
    void readAllSensorValues();
    void calculateAngle(float targetValue);
    
  private:
    float  _PER_SENSOR_TOLERANCE = 10;
    float  _SENSOR_DIFFERENCE_TOLERANCE = 10;
    int _sensorCount;
    int _id;
    bool _INVERT_RESULTS = false;
    Sensor*   _allSensors;
  
};
