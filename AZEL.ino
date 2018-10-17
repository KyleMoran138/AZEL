int MTR_PN = 13;
int FWD_PN = 12;
boolean FWD_EN = false;
boolean MTR_EN = false;

void setup() {
  pinMode(MTR_PN, OUTPUT);
  pinMode(FWD_PN, OUTPUT);
  digitalWrite(FWD_PN, FWD_EN);
  digitalWrite(MTR_PN, MTR_EN);
}

void loop() {
  delay(3000);
  setMotor(false);
  setFwd(false);
  delay(3000);
  setMotor(true);
  setFwd(false);
  delay(3000);
  setMotor(true);
  setFwd(true);
}

void setMotor(bool EN){
  MTR_EN = EN;
  digitalWrite(MTR_PN, EN);
}

void setFwd(bool EN){
  FWD_EN = EN;
  digitalWrite(FWD_PN, EN);
}



