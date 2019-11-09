/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->  http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *leftM = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor *rightM = AFMS.getMotor(4);

const int leftIRPin = A0;
const int rightIRPin = A1;

String input = "";
int rightThreshold =900;
int leftThreshold = 900;
int standardSpeed =20;
int differentialSpeed = 15;
int leftSpeed = standardSpeed;
int rightSpeed= standardSpeed;
int maxSpeed = 50;
boolean drive = false;
boolean lastRight=true;
int leftValue = 0;
int rightValue = 0;

void setup() {
  Serial.begin(19200);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
//  leftM->setSpeed(50);
//  rightM->setSpeed(50);
//  Serial.println("is in forward mode now");
//  leftM->run(FORWARD);
//  rightM->run(BACKWARD);
//  delay(5000);
//  // turn on motor
//  leftM->run(RELEASE);
//  rightM->run(RELEASE);
  delay(1000);
}

void loop() {
  checkForInput();
  leftValue = analogRead(leftIRPin);
  rightValue = analogRead(rightIRPin);
  if(drive){
    if(rightValue>rightThreshold){
        goRight();
    }
    else if(leftValue>leftThreshold){
        goLeft();
    }
    else if(leftValue<leftThreshold && rightValue<rightThreshold){
        leftM->run(BACKWARD);
        leftSpeed = standardSpeed;
        leftM->setSpeed(leftSpeed);
        rightM->run(FORWARD);
        rightSpeed = standardSpeed;
        rightM->setSpeed(rightSpeed); 
    }
//    else if(leftValue>leftThreshold && rightValue>rightThreshold){
//        leftM->run(RELEASE);
//        leftSpeed = standardSpeed;
//        leftM->setSpeed(leftSpeed);
//        rightM->run(RELEASE);
//        rightSpeed = standardSpeed;
//        rightM->setSpeed(rightSpeed);
//        drive=false;
//    }
  }
  //printAllData();
  //printAnalogs();
  printSpeedvsInput();
  delay(20);
  
}
void goLeft(){
        //leftM->run(BACKWARD);
        //leftSpeed -= differentialSpeed;
        if(leftSpeed<0){leftSpeed=0;}
        leftM->setSpeed(leftSpeed-differentialSpeed);
        //rightM->run(FORWARD);
        //rightSpeed +=differentialSpeed;
        if(rightSpeed>maxSpeed){rightSpeed=maxSpeed;}
        Serial.println(rightSpeed);
        rightM->setSpeed(rightSpeed); 
        lastRight=false;
}
void goRight(){
        //leftM->run(BACKWARD);
        //leftSpeed += differentialSpeed;
        if(leftSpeed>maxSpeed){leftSpeed=maxSpeed;}
        Serial.println(leftSpeed+differentialSpeed);
        leftM->setSpeed(leftSpeed+differentialSpeed);
        //rightM->run(FORWARD);
        //rightSpeed -= differentialSpeed;
        if(rightSpeed<0){rightSpeed=0;}
        rightM->setSpeed(rightSpeed-differentialSpeed);
        lastRight=true;
}

void checkForInput(){
  //Serial.println("Write the action you want to do");
  while (Serial.available()>0){
    input = Serial.readString();
  }
  if(input =="stop"){
    drive = false;
    leftM->run(RELEASE);
    rightM->run(RELEASE);
    Serial.println("Stop is called, robot stops driving!");
    }
  else if(input=="start"){
    drive = true;
    Serial.println("Start is called, robot starts driving!");

  }
  else if (input.substring(0,input.indexOf("="))=="right"){
    rightThreshold = input.substring(input.indexOf("=")+1).toInt();
  }
  else if (input.substring(0,input.indexOf("="))=="left"){
    leftThreshold = input.substring(input.indexOf("=")+1).toInt();
  }
  else if (input.substring(0,input.indexOf("="))=="diff"){
    differentialSpeed = input.substring(input.indexOf("=")+1).toInt();
  }
  else if (input.substring(0,input.indexOf("="))=="speed"){
    standardSpeed = input.substring(input.indexOf("=")+1).toInt();
  }
  input = "";
}
void printAllData(){
  Serial.print("standardSpeed: ");
  Serial.print(standardSpeed);
  Serial.print(" \t differentialSpeed: ");
  Serial.print(differentialSpeed);
  Serial.print(" \t leftThreshold: ");
  Serial.print(leftThreshold);
  Serial.print(" \t rightThreshold: ");
  Serial.println(rightThreshold);
}
void printAnalogs(){
  Serial.print("leftIRValue: ");
  Serial.print(analogRead(leftIRPin));
  Serial.print("\t rightIRValue: ");
  Serial.println(analogRead(rightIRPin));
}
void printSpeedvsInput(){
  Serial.print(leftSpeed);
  Serial.print(",");
  Serial.print(rightSpeed);
  Serial.print(",");
  Serial.print(leftValue);
  Serial.print(",");
  Serial.println(rightValue);
}
