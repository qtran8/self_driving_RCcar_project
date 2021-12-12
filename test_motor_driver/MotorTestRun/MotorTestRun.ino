#include <SparkFun_TB6612.h>

/******************************************************************************
TestRun.ino
TB6612FNG H-Bridge Motor Driver Example code
Michelle @ SparkFun Electronics
8/20/16
https://github.com/sparkfun/SparkFun_TB6612FNG_Arduino_Library

Uses 2 motors to show examples of the functions in the library.  This causes
a robot to do a little 'jig'.  Each movement has an equal and opposite movement
so assuming your motors are balanced the bot should end up at the same place it
started.

Resources:
TB6612 SparkFun Library

Development environment specifics:
Developed on Arduino 1.6.4
Developed with ROB-9457
******************************************************************************/

// This is the library for the TB6612 that contains the class Motor and all the
// functions
#include <SparkFun_TB6612.h>

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch

// first two motors
#define AIN1 2
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 9

//second two motors
#define AIN12 11
#define BIN12 3
#define AIN22 12
#define BIN22 14
#define PWMA2 13
#define PWMB2 10
#define STBY2 15

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

void setup()
{
 //Nothing here
}


void loop()
{
   //Use of the drive function which takes as arguements the speed
   //and optional duration.  A negative speed will cause it to go
   //backwards.  Speed can be from -255 to 255.  Also use of the 
   //brake function which takes no arguements.
   //motor1.drive(0,1000);
   //motor1.drive(-100,1000);
   //motor1.brake();
   //delay(1000);
   
   //motor2.drive(0,1000);
   //motor2.drive(-100,1000);
   //motor2.brake();
   //delay(1000);
   
   //motor3.drive(100,1000);
   //motor3.drive(-100,1000);
   //motor3.brake();
   //delay(1000);

   //motor4.drive(100,1000);
   //motor4.drive(-100,1000);
   //motor4.brake();
   //delay(1000);
   
   //Use of the forward function, which takes as arguements two motors
   //and optionally a speed.  If a negative number is used for speed
   //it will go backwards
   //forward(motor1, motor2, 109);
   //forward(motor3, motor4, 120);
   //delay(4000);
   
   //Use of the back function, which takes as arguments two motors 
   //and optionally a speed.  Either a positive number or a negative
   //number for speed will cause it to go backwards
   //back(motor3, motor4, 120);
   //back(motor1, motor2, 98);
   //delay(4000);
   
   //Use of the brake function which takes as arguments two motors.
   //Note that functions do not stop motors on their own.
   //brake(motor1, motor2);
   //delay(1000);
/*
   //360 degree-turn
   right(motor2,motor4,motor1,motor3,128,128);
   delay(7200);
   brake(motor1, motor2);
   brake(motor3, motor4);
   delay(3000);*/
/*
   //turn right 
   right(motor2,motor4,motor1,motor3,128,128);
   delay(1800);
   brake(motor1, motor2);
   brake(motor3, motor4);
   delay(3000);

   //turn left
   left(motor2,motor4,motor1,motor3,128,128);
   delay(1800);
   brake(motor1, motor2);
   brake(motor3, motor4);
   delay(900);*/
   //Use of the left and right functions which take as arguements two
   //motors and a speed.  This function turns both motors to move in 
   //the appropriate direction.  For turning a single motor use drive.
   //left(motor1, motor2, 10);
   //delay(1000);
   //right(motor1, motor2, 10);
   //delay(1000);
   
   //Use of brake again.
   //brake(motor1, motor2);
   //delay(1000);
   
}
