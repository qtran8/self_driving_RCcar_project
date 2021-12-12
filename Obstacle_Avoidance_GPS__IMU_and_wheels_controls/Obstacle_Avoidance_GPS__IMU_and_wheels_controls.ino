/*******************************************************************************************************************************************************************************************
*  Adafruit BNO055 Sensor Calibration sample
*  Refer to http://www.adafruit.com/datasheets/BST_BNO055_DS000_12.pdf
*  Section 3.10 on how to calibrate your sensor:
*   -Run this sketch
*   -To calibrate the Gyroscope, just let the sensor sit for a couple of seconds until GYR Calibration shows 1
*   -To calibrate the Magnetometer, move your sensor in random figure 8 patterns until MAG Calibration shows 1
*   -If you want to calibrate the acceleration sensor, move the sensor to 6 stable positions slowly, 3 of those should be in the XY/XZ/YZ plane
*   -Once you are happy with the readings you get, copy the c_data = .... line from serial.console to the setup() of your sketch and write it to the sensor with "bno.setCalibData(c_data);"
********************************************************************************************************************************************************************************************/

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>
#include <Wire.h>
#include <Servo.h>
#include <LIDARLite.h>
#include <SparkFun_TB6612.h>

//Connect with pin 18(RX) and 19(TX) for TinyGPS
#include <TinyGPS.h>

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

//long   lat,lon; // create variable for latitude and longitude object
float lat,lon;
float distan = 0;

TinyGPS gps; // create gps object
Adafruit_BNO055 bno = Adafruit_BNO055(55);      // define a BNO055 object

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

void setup(){
  Serial.begin(9600); // Initialize serial connection to display distance readings
  lidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  lidarLite.configure(0); // Change this number to try out alternate configurations
  myservo.attach(22);  // attaches the servo on pin 22 to the servo object
 
  Serial.begin(9600); // connect serial
  Serial.println("The GPS Received Signal:");
  Serial1.begin(9600); // connect gps sensor
  Serial.println("Orientation Sensor Calibration"); Serial.println("");

  /* Initialise the sensor */
  if (!bno.begin(Adafruit_BNO055::OPERATION_MODE_NDOF)) //if you want to calibrate using another mode, set it here. 
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");     // if the sensor is not found!
    while (1);
  }
  
  // You will need to put the next two lines into your own sketch, _immediatly_ after bno.begin() to use a predefined calibration
  // byte c_data[22] = {0, 0, 0, 0, 0, 0, 172, 250, 112, 255, 52, 253, 0, 0, 253, 255, 255, 255, 232, 3, 240, 2}; //replace this line with the serial output of this sketch
  
  byte c_data[22] = {31, 0, 237, 255, 234, 255, 49, 2, 137, 1, 36, 255, 0, 0, 0, 0, 2, 0, 232, 3, 67, 3};
  bno.setCalibData(c_data);
  
  delay(1000);
  bno.setExtCrystalUse(true);

}

void loop(){
  int dist;
  int a = 0;
  int detectedAngle = 0;
  float dV;

  
  //print the euler angles for reference
  //Serial.print("X: "); //"heading"
  //Serial.println(headingAngle, 4);
  /*Serial.print(" Y: ");
  Serial.print(event.orientation.y, 4);
  Serial.print(" Z: ");
  Serial.print(event.orientation.z, 4);
  Serial.println();*/
  float turningAngle = 0;
  float bearingAngle = 0;
  float headingAngle = 0;
  sensors_event_t event;
  bno.getEvent(&event);
  
  //while(Serial1.available());
  
    while(Serial1.available()){ // check for gps data
    
    if(gps.encode(Serial1.read()))// encode gps data
    {
    gps.f_get_position(&lat,&lon); // get latitude and longitude

    Serial.print("Position: ");
   
    //Latitude
    Serial.print("Latitude: ");
    Serial.print(lat,6);
   
    //Serial.print(",");
   
    //Longitude
    //Serial.print("Longitude: ");
    //Serial.println(lon,6);
    
    distan = gps.distance_between(lat,lon,37.976256,-121.320794);
    //Serial.print("Distance: ");
    //Serial.println(distan,6);
    
    bearingAngle = gps.course_to(lat,lon,37.976256,-121.320794);//bearing angle
    //Serial.print("Bearing angle to destination: ");
    //Serial.println(bearingAngle,2);

    headingAngle = event.orientation.x;
    //Serial.print("X: "); //"heading"
    //Serial.println(headingAngle, 4);
    delay(100);

    turningAngle = bearingAngle - headingAngle;
    //Serial.print("turningAngle: "); 
    //Serial.println(turningAngle, 4);
        if(distan > 4){
      if(turningAngle < -180){
        //turn right
        right(motor2,motor4,motor1,motor3,128,128);
        delay((turningAngle+360)*7200/360);
        Serial.println("Right: <-180");
      }
      else if(turningAngle >= -180 && turningAngle < -5){
        //turn left
        left(motor2,motor4,motor1,motor3,128,128);
        delay(fabs(turningAngle)*7200/360);
        Serial.println("left < -5");
      }
      else if(turningAngle > 5 && turningAngle <= 180){
        //turn right
        right(motor2,motor4,motor1,motor3,128,128);
        delay((turningAngle)*7200/360);
        Serial.println("right <=180");
      }
      else if(turningAngle > 180){
        //turn left
        left(motor2,motor4,motor1,motor3,128,128);
        delay((360-turningAngle)*7200/360);
        Serial.println("left > 180");
      }
      else{
          forward(motor1, motor2, 109);
          forward(motor3, motor4, 120);
          delay(100); 
          Serial.println("last going forward");
      }
    }
   }
  }
  
    if(distan > 4){
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
     }

     if(distan > 4){
      if(turningAngle < -180){
        //turn right
        right(motor2,motor4,motor1,motor3,128,128);
        delay((turningAngle+360)*7200/360);
        //Serial.println("Right: <-180");
      }
      else if(turningAngle >= -180 && turningAngle < -5){
        //turn left
        left(motor2,motor4,motor1,motor3,128,128);
        delay(fabs(turningAngle)*7200/360);
        //Serial.println("left < -5");
      }
      else if(turningAngle > 5 && turningAngle <= 180){
        //turn right
        right(motor2,motor4,motor1,motor3,128,128);
        delay((turningAngle)*7200/360);
        //Serial.println("right <=180");
      }
      else if(turningAngle > 180){
        //turn left
        left(motor2,motor4,motor1,motor3,128,128);
        delay((360-turningAngle)*7200/360);
        //Serial.println("left > 180");
      }
      else{
          forward(motor1, motor2, 109);
          forward(motor3, motor4, 120);
          delay(100); 
          //Serial.println("last going forward");
      }
    }
}
