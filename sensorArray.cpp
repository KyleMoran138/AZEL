#include "SensorArray.h";

// The default sensor layout is in a circle and will go counter
// clockwise. The top of the circle will be both 0 and 1.

SensorArray::SensorArray(Sensor Sensor[], int* sensorCount){
  this->_allSensors = Sensor;
  this->_sensorCount = sensorCount;
  this->allSensorValues = {};
}

SensorArray::SensorArray(Sensor Sensor[], int* sensorCount, float perSensorTol,
  float sensorDiffTol, bool invertResults){
  this->_allSensors = Sensor;
  this->_sensorCount = sensorCount;
  this->allSensorValues = {};
  this->_PER_SENSOR_TOLERANCE = perSensorTol;
  this->_SENSOR_DIFFERENCE_TOLERANCE = sensorDiffTol;
  this->_INVERT_RESULTS = invertResults;
}

void SensorArray::readAllSensorValues(){
  for(int i = 0; i < this->_sensorCount; i++){
    this->allSensorValues[i] = _allSensors[i].readFloat();
  }
}

void SensorArray::calculateAngle(float targetValue){
  for(int i = 0; i < this->_sensorCount; i++){
    Sensor* senUp;
    Sensor* sen = &this->_allSensors[i];
    Sensor* senDown;
    if(i >= this->_sensorCount){
      senUp = &this->_allSensors[0];
    }else{
      senUp = &this->_allSensors[this->_sensorCount+1];
    }
    if(i == 0){
      senDown = &this->_allSensors[this->_sensorCount];
    }else{
      senDown = &this->_allSensors[this->_sensorCount-1];
    }
    sen->d_u = sen->value - senUp->value;
    sen->d_d = sen->value - senDown->value;
    sen->d_u_gt = sen->d_u < this->_PER_SENSOR_TOLERANCE;
    sen->d_u_lt = sen->d_u > -this->_PER_SENSOR_TOLERANCE;
    sen->d_d_gt = sen->d_d < this->_PER_SENSOR_TOLERANCE;
    sen->d_d_lt = sen->d_d > -this->_PER_SENSOR_TOLERANCE;
    sen->d_f_g = targetValue - sen->value;
  }
}

// void