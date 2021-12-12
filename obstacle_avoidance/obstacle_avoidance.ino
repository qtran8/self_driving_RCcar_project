//
#include <FlexiTimer2.h>
#include <Wire.h>
#include <Servo.h>
#include <LIDARLite.h>
#include <SparkFun_TB6612.h>

// Globals

// first two motors
#define AIN1 2
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 9

//second two motors
#define AIN12 13
#define BIN12 10
#define AIN22 12
#define BIN22 14
#define PWMA2 11
#define PWMB2 3
#define STBY2 15

//#define PI 3.14159265
// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY); //top right wheel
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY); //top left wheel

Motor motor3 = Motor(AIN12, AIN22, PWMA2, offsetA, STBY2); //Bottom right wheel
Motor motor4 = Motor(BIN12, BIN22, PWMB2, offsetB, STBY2); //bottom left wheel


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

//Global variables
int pos = 60;    // variable to store the servo position
int i = 0;
LIDARLite lidarLite;
int angleArray[3] = {0,0,0};
float distArray[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

float convertFromDegreeToRadian(int degree){
  return (degree*PI/180);
}
float returnVerticalDistance(float distance, float objectAngle){
  objectAngle = convertFromDegreeToRadian(objectAngle);
  return distance*sin(objectAngle);
}
  
void flash()
{
  int count = 0;
  int dist;
  float dV;
  /*while(i == 3){
    brake(motor1, motor2);
    brake(motor3, motor4);
    delay(100);
    i = 0;
    for (pos = 60; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    dist = lidarLite.distance(); // With bias correction
    dV = returnVerticalDistance(dist,pos);
    if(dV < 70){
      if(i < 3){
        angleArray[i] = pos;
        if( i > 0 && ((angleArray[i] - 1) != angleArray[i-1])){
          i = 0;
        }
        else {  i++; }
      }
      if((i == 3) && a < 20){
        distArray[a] = dV;        // even location gives distant
        distArray[a + 1] = angleArray[1];     //odd location gives angle at the previous even location
        i = 0;
        a += 2;
      }
    }

    //Serial.print(pos);
    //Serial.println(" : current angle"); 
    //Serial.print(dist);
    //Serial.print(" cm; dV = ");
    //Serial.println(dV);
    delay(1);                       // waits 15 ms for the servo to reach the position
  }
  
  float minDist = distArray[0];
  for(int j = 0; j <10; j++){
    if((distArray[2*j] != 0) && (distArray[2*j] <= minDist)){
      minDist = distArray[2*j];
      detectedAngle = distArray[2*j + 1];
    }
  }
}
    if(detectedAngle != 0){
      //Serial.print(bestAngle);
      //Serial.println(" : flash degree");
      if(detectedAngle <= 90){
        right(motor2,motor4,motor1,motor3,128,128);
        delay(detectedAngle*7200/360);
      }
      else{
        left(motor2,motor4,motor1,motor3,128,128);
        delay((detectedAngle-90)*7200/360);
      }
      
      //Serial.print(bestAngle);
      //Serial.println(" : updated 0 degree");
    }
    detectedAngle = 0;
    i = 0;
    a = 0;
    for(int j = 0; j <20; j++){
       distArray[j] = 0;
    }*/
}
void setup() {
  Serial.begin(9600); // Initialize serial connection to display distance readings
  lidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  lidarLite.configure(0); // Change this number to try out alternate configurations
  myservo.attach(22);  // attaches the servo on pin 22 to the servo object
  
  //FlexiTimer2::set(1000, 1/1000, flash); // call every 200 1ms "ticks"
  //FlexiTimer2::start();

}

void loop() {
  int dist;
  int a = 0;
  int detectedAngle = 0;
  float dV;
  forward(motor1, motor2, 109);
  forward(motor3, motor4, 120);
  delay(100);    
      
  for (pos = 60; pos <= 120; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    dist = lidarLite.distance(); // With bias correction
    dV = returnVerticalDistance(dist,pos);
    //Serial.print(pos);
    //Serial.println(" : current angle"); 
    //Serial.print(dist);
    //Serial.print(" cm; dV = ");
    //Serial.println(dV);
    if(dV < 50){
      if(i < 3){
        angleArray[i] = pos;
        if( i > 0 && ((angleArray[i] - 1) != angleArray[i-1])){
          i = 0;
        }
        else {  i++; }
      }
        if((i == 3) && a < 20){
          distArray[a] = dV;        // even location gives distant
          distArray[a + 1] = angleArray[2];     //odd location gives angle at the previous even location
          Serial.print(distArray[a]);
          Serial.print(" : current dist; previous angle: ");
          Serial.println(distArray[a + 1]);
          i = 0;
          a += 2;
        }
      }
    
    delay(1);                       // waits 15 ms for the servo to reach the position
  }
  
  float minDist = distArray[0];
  for(int j = 0; j <10; j++){
    if((distArray[2*j] != 0) && (distArray[2*j] <= minDist)){
      minDist = distArray[2*j];
      detectedAngle = distArray[2*j + 1];
      Serial.print(minDist);
      Serial.print(" : min dist; previous angle: ");
      Serial.println(detectedAngle);
    }
  }
  if(detectedAngle != 0){
    Serial.print(detectedAngle);
    Serial.println(" : detected degree");
    brake(motor1, motor2);
    brake(motor3, motor4);
    delay(500);
      if(detectedAngle <= 90){
        Serial.println("turn left");
        left(motor2,motor4,motor1,motor3,128,128);
        delay(detectedAngle*7200/360);
      }
      else{
        Serial.println("turn right");
        right(motor2,motor4,motor1,motor3,128,128);
        delay((detectedAngle-90)*7200/360);
      }
      
      //Serial.print(bestAngle);
      //Serial.println(" : updated 0 degree");
    }
    detectedAngle = 0;
    i = 0;
    a = 0;
    for(int j = 0; j <20; j++){
       distArray[j] = 0;
       Serial.println(j);
    }
  for (pos = 120; pos >= 60; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    dist = lidarLite.distance(); // With bias correction
    dV = returnVerticalDistance(dist,pos);
    delay(1);                       // waits 15 ms for the servo to reach the position
  }
}
