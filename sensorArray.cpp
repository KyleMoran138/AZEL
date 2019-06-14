#include "SensorArray.h"

// The default sensor layout is in a circle and will go counter
// clockwise. The top of the circle will be both 0 and 1.
 #define SERIAL_OUTPUT_SENSORARRAY
SensorArray::SensorArray(Sensor **Sensors, int sensorCount){
  this->_allSensors = Sensors;
  this->_sensorCount = sensorCount;
  this->allSensorValues = new float[sensorCount]();
}

SensorArray::SensorArray(Sensor **Sensors, int sensorCount, float perSensorTol, bool invertResults){
  this->_allSensors = Sensors;
  this->_sensorCount = sensorCount;
  this->allSensorValues = new float[sensorCount]();
  this->_PER_SENSOR_TOLERANCE = perSensorTol;
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

void SensorArray::calculateAngle(){
  for(int i = 0; i < this->_sensorCount; i++){
    delay(20);
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
      Serial.print('\n');
    #endif
  }
}

int SensorArray::GetSensorDownIndex(int currentSensorIndex, bool respectPosition = false){
  Sensor* currentSensor = this->_allSensors[currentSensorIndex];
  int indexToReturn = currentSensorIndex+1;
  if(currentSensorIndex - 1 <= -1){
    indexToReturn = this->_sensorCount-1;
  }

  if(respectPosition && indexToReturn == this->_sensorCount-1){
    indexToReturn = -1;
  }
  return indexToReturn;
}

int SensorArray::GetSensorUpIndex(int currentSensorIndex, bool respectPosition = false){
  Sensor* currentSensor = this->_allSensors[currentSensorIndex];
  int indexToReturn = currentSensorIndex + 1;
  if(currentSensorIndex + 1 >= this->_sensorCount-1){
    indexToReturn = 0;
  }

  if(respectPosition && indexToReturn == 0){
    indexToReturn = -1;
  }

  return indexToReturn;
}

int SensorArray::getSensorTurnDirection(int forwardSensorIndex, float target){
    int valueAboveTargetOrBelow = 0;

    Sensor* senUp = this->_allSensors[this->GetSensorUpIndex(forwardSensorIndex)];
    Sensor* forwardSensor = this->_allSensors[forwardSensorIndex];
    Sensor* senDown = this->_allSensors[this->GetSensorDownIndex(forwardSensorIndex)];

    if(forwardSensor->value > target && forwardSensor->value > target + this->_PER_SENSOR_TOLERANCE) valueAboveTargetOrBelow = 1;
    if(forwardSensor->value < target && forwardSensor->value < target - this->_PER_SENSOR_TOLERANCE) valueAboveTargetOrBelow = -1;

    if(valueAboveTargetOrBelow == 0) return 0;
    if(senUp->SensorDifferenceSumZero() && senDown->SensorDifferenceSumZero() && true) return 0;

    if(valueAboveTargetOrBelow == -1){
      if(forwardSensor->d_d_lt && forwardSensor->d_u_lt){
        if(abs(senUp->value - target) > abs(senDown->value - target)){
          return -1;
        }else if(abs(senUp->value - target) < abs(senDown->value - target)){
          return 1;
        }else{
          //If these arent the last sensors on the side then Get the next one away else use this one
          // Then figure out which one is close to the target and then steer twoards it
          return 0;
        }
      }else if(forwardSensor->d_d_lt){
        return -1;
      }else if(forwardSensor->d_u_lt){
        return 1;
      }
    }else if(valueAboveTargetOrBelow == 1){
      if(forwardSensor->d_d_gt && forwardSensor->d_u_gt){
        if(abs(senUp->value - target) > abs(senDown->value - target)){
          return -1;
        }else if(abs(senUp->value - target) < abs(senDown->value - target)){
          return 1;
        }else{
          return 0;
        }
      }else if(forwardSensor->d_d_gt){
        return -1;
      }else if(forwardSensor->d_u_gt){
        return 1;
      }
    }

    return 0;
}

float SensorArray::getDistanceToRotateBy(int forwardSensorIndex, float target, int directionToRotate){
  if(forwardSensorIndex + directionToRotate == forwardSensorIndex) return 0;
  Sensor* closestSensor = this->_allSensors[forwardSensorIndex];
  int sensorIndexUp = forwardSensorIndex += directionToRotate;
  
  if(forwardSensorIndex >= this->_sensorCount-1){
    sensorIndexUp = 0;
  }else if(forwardSensorIndex < 0){
    sensorIndexUp = this->_sensorCount-1;
  }

  float valuesPerOneDegree = closestSensor->getValueChangePerDistanceUnit(this->_allSensors[sensorIndexUp]);
  return (valuesPerOneDegree / this->_allSensors[sensorIndexUp]->value);

}

float SensorArray::getSensorValue(int sensor){
  return this->allSensorValues[sensor];
};
