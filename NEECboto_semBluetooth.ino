#include <Servo.h>        //add Servo Motor library            
#include <NewPing.h>      //add Ultrasonic sensor library

#define TRIG_PIN 3 
#define ECHO_PIN 4
#define MAX_DISTANCE 300 // sets maximum useable sensor measuring distance to 300cm
#define COLL_DIST 25 // sets distance at which robot stops and reverses to 30cm
#define TURN_DIST COLL_DIST+20 // sets distance at which robot veers away from object

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // sets up sensor library to use the correct pins to measure distance.

Servo left_servo;  // create servo object to control servos
Servo right_servo;
Servo reader;

//Global variables
int leftDistance, rightDistance; //distances on either side
int curDist = 0;
int angle;
int up;

//-------------------------------------------- SETUP LOOP ----------------------------------------------------------------------------
void setup() {
  left_servo.attach(11); 
  right_servo.attach(10);
  reader.attach(6);
  reader.write(90);
  Serial.begin(9600);
  delay(1000); // delay for one seconds
  angle=90;
  up=1;
 }
//------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------MAIN LOOP ------------------------------------------------------------------------------
void loop() {
  
 /* if(angle<130 and up==1){
    angle=angle+10;
  } else if (angle>50 and up==0){
    angle=angle-10;
  } else if (angle>=125){
    up=0;
  } else  if (angle<=55) {
    up=1;
  }*/
  
  reader.write(angle);  // move eyes forward
  
  if (readPing() < COLL_DIST) {
    reader.write(90);
    changePath();
  }  // if forward is blocked change direction
  else {
    moveForward();  // move forward
  }
  //delay(50);
 }
//-----------------------------------------------------------//Deciding which side to go//------------------------------------------------------------------------

void changePath() {
  moveStop();   // stop forward movement
    reader.write(36);  // check distance to the right
    delay(400);
    rightDistance = readPing(); //set right distance
    delay(700);
    reader.write(144);  // check distace to the left
    delay(600);
    leftDistance = readPing(); //set left distance
    delay(700);
    reader.write(90); //return to center
    delay(400);
    compareDistance();
  }

  
void compareDistance()   // find the longest distance
{
  if (leftDistance>rightDistance  and leftDistance>25) //if left is less obstructed 
  {
    turnLeft();
  }
  else if (rightDistance>leftDistance and rightDistance>25) //if right is less obstructed
  {
    turnRight();
  }
   else  if (leftDistance<15 and rightDistance<15) //if they are equally obstructed
  {
    turnAround();
  } else {

    moveBackward();
    delay(1000);
    changePath();
    
  }
}


//--------------------------------------------//Reading the distance//-------------------------------------------------------------------------------------

int readPing() { // read the ultrasonic sensor distance
  delay(50); 
  int distance = sonar.ping_cm();
  if (distance == 0) {
    distance = MAX_DISTANCE;
  }
  Serial.println(distance);
  return distance;
}
//------------------------------------------------//movement---------------------------------------------------------------------------------
void moveStop() { right_servo.write(90); left_servo.write(90);}  // stop the motors.
//-------------------------------------------------------------------------------------------------------------------------------------
void moveForward() {
  right_servo.write(60);
  left_servo.write(122);
}
//-------------------------------------------------------------------------------------------------------------------------------------
void moveBackward() {
    right_servo.write(120);
    left_servo.write(58);
    delay(1000);
}  
//-------------------------------------------------------------------------------------------------------------------------------------
void turnRight() {
  left_servo.write(122);
  right_servo.write(120);
  delay(500); 
}  
//-------------------------------------------------------------------------------------------------------------------------------------
void turnLeft() {
  left_servo.write(58);
  right_servo.write(60);
  delay(500);   
}  
//-------------------------------------------------------------------------------------------------------------------------------------
void turnAround() {
  left_servo.write(122);
  right_servo.write(120);
  delay(1000);         
}  
//--------------------------------------------------------------------------------------------------------------------------------------
//void 
