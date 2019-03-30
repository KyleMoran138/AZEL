#include "SensorArray.h";

// The default sensor layout is in a circle and will go counter
// clockwise. The top of the circle will be both 0 and 1.
 #define SERIAL_OUTPUT_SENSORARRAY
SensorArray::SensorArray(Sensor **Sensors, int sensorCount){
  this->_allSensors = Sensors;
  this->_sensorCount = sensorCount;
  this->allSensorValues = new float[sensorCount]();
}

SensorArray::SensorArray(Sensor **Sensors, int sensorCount, float perSensorTol,
  float sensorDiffTol, bool invertResults){
  this->_allSensors = Sensors;
  this->_sensorCount = sensorCount;
  this->allSensorValues = new float[sensorCount]();
  this->_PER_SENSOR_TOLERANCE = perSensorTol;
  this->_SENSOR_DIFFERENCE_TOLERANCE = sensorDiffTol;
  this->_INVERT_RESULTS = invertResults;
}

void SensorArray::readAllSensorValues(){
  for(int i = 0; i < this->_sensorCount; i++){
    if(i > this->_sensorCount) continue;
    Serial.print("Sensor:");
    Serial.println(i);
    this->allSensorValues[i] = _allSensors[i]->readFloat();
  }
}

void SensorArray::calculateAngle(float targetValue){
  for(int i = 0; i < this->_sensorCount; i++){
    delay(300);
    Sensor* senUp;
    Sensor* sen = this->_allSensors[i];
    Sensor* senDown;
    if(i >= this->_sensorCount-1){
      senUp = this->_allSensors[0];
    }else{
      senUp = this->_allSensors[i+1];
    }
    if(i == 0){
      senDown = this->_allSensors[this->_sensorCount-1];
    }else{
      senDown = this->_allSensors[i-1];
    }
    sen->d_u = sen->value - senUp->value;
    sen->d_d = sen->value - senDown->value;
    sen->d_u_gt = sen->d_u > this->_PER_SENSOR_TOLERANCE;
    sen->d_u_lt = sen->d_u < -this->_PER_SENSOR_TOLERANCE;
    sen->d_d_gt = sen->d_d > this->_PER_SENSOR_TOLERANCE;
    sen->d_d_lt = sen->d_d < -this->_PER_SENSOR_TOLERANCE;
    sen->d_f_g = targetValue - sen->value;

    

    #ifdef SERIAL_OUTPUT_SENSORARRAY
      Serial.print("Sensor [");
      Serial.print(i);
      Serial.print("]: ");
      Serial.println(sen->value);
      Serial.print("Diff up: ");
      Serial.println(sen->d_u);
      Serial.print("Diff down: ");
      Serial.println(sen->d_d);
      Serial.print("Diff up grater than: ");
      Serial.println(sen->d_u_gt);
      Serial.print("Diff up less than: ");
      Serial.println(sen->d_u_lt);
      Serial.print("Diff down grater than: ");
      Serial.println(sen->d_d_gt);
      Serial.print("Diff down less than: ");
      Serial.println(sen->d_d_lt);
      Serial.print("Distance from goal: ");
      Serial.println(sen->d_f_g);
      Serial.print('\n');
    #endif
  }
}

float SensorArray::getSensorValue(int sensor){
  return this->allSensorValues[sensor];
};