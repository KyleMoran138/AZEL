import processing.serial.*;


PrintWriter output;
Serial myPort;
String val;
String[] values;
int maxCount = 100;
int count = 0;
boolean enforceCount = true;


void setup()
{
  // I know that the first port in the serial list on my mac
  // is Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  String portName = Serial.list()[0]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 230400);
  output = createWriter("TestSensor0.txt");
  output.println("Sensor#,SensorValue,DU,DD,DUG,DUL,DDG,DDL,DTT");
}

void draw()
{
  
  if ( myPort.available() > 0) 
  {  // If data is available,
    count = count + 1;
    val = myPort.readStringUntil('\n');         // read it and store it in val
    output.print(val);
    println("Count: " + count);
  }
  
  if(count >= maxCount && enforceCount){
    output.flush(); // Writes the remaining data to the file
    output.close(); // Finishes the file
    exit(); 
  }

}

void mousePressed() {
  output.flush(); // Writes the remaining data to the file
  output.close(); // Finishes the file
  exit(); 
}
