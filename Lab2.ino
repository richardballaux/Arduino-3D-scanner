/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo horServo;  // create servo object to control a servo
Servo verServo;
const int IRPin = A0;

int pos = 0;    // variable to store the servo position
int posV = 0;
int distance = 0;
int looper = 0;


void setup() {
  Serial.begin(9600);
  horServo.attach(10);  // attaches the servo on pin 10 to the servo object
  verServo.attach(11);// verServo on pin 11
  horServo.write(90);   // Putting the servo's in starting position
  verServo.write(90);

  delay(5000);
  for (posV = 60; posV <=120 ; posV += 1) {    
    if (posV%2 == 0) {
      for (pos = 60; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        //here we need to send the data to the computer
        distance = calculateDistance(analogRead(IRPin));
        sendDataToComputer(distance,pos,posV);
        horServo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(150);                        // waits 15ms for the servo to reach the position
      }
    }
    else {
      for (pos = 120; pos >= 60; pos -= 1) { // goes from 180 degrees to 0 degrees
        //here we need to send the data to the computer
        distance = calculateDistance(analogRead(IRPin));
        sendDataToComputer(distance,pos,posV);
        horServo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(150);                       // waits 15ms for the servo to reach the position
      }
    }
    verServo.write(posV);

  }
}

void loop() {
  
  }



int calculateDistance(int analogValue){
  //This function returns the distance from the sensor the the nearest object
  float voltage = (analogValue-0.0)*(5.0-0.0)/(1023.0-0.0) + 0.0;
  int distance = 2093*exp(-8.498*voltage) + 153*exp(-0.8548*voltage);
  //printAllData(analogValue,voltage,distance);
  return distance;
}
void sendDataToComputer(int dis, int angleH, int angleV){
  Serial.print(dis);    Serial.print(",");
  Serial.print(angleH); Serial.print(",");
  Serial.println(angleV);
}
void printAllData(int analogValue, float voltage, int distance){
  Serial.print("Analog value: ");
  Serial.print(analogValue);
  Serial.print(" Voltage= ");
  Serial.print(voltage);
  Serial.print(" Distance= ");
  Serial.println(distance);
}
