#include <Servo.h>
#include <NewPing.h>

#define RIGHT_PIN 10
#define LEFT_PIN 11
#define READER_PIN 7
#define ECHO_PIN 4
#define TRIG_PIN 3

#define MAX_DISTANCE 300

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

Servo rightservo;
Servo leftservo;
Servo readerservo;

enum direction {halt, left, right, forward, backward};

void setup() {
  Serial.begin(9600);
  rightservo.attach(RIGHT_PIN);
  leftservo.attach(LEFT_PIN);
  readerservo.attach(READER_PIN);
  readerservo.write(90);
  rightservo.write(90);
  leftservo.write(90);
  delay(100); // delay for one seconds
  Serial.println("Began");
}

void loop() {
  moveAutoBot();
}

void moveBot(enum direction d){
  int r;
  int l;
  
  switch(d) {
    case(halt):
      r = 90;
      l = 90;
      Serial.println("Halting...");
      break;
    case(left):
      r = 45;
      l = 45;
      Serial.println("Moving left...");
      break;
    case(right):
      r = 135;
      l = 135;
      Serial.println("Moving right...");
      break;
    case(forward):
      r = 45;
      l = 135;
      Serial.println("Moving forward...");
      break;
    default:
      r = 135;
      l = 45;
      Serial.println("Moving backward...");
      break;
  }
  
  rightservo.write(r);
  leftservo.write(l);
}

int getDistance(){
  int distance = sonar.ping_cm();
  Serial.print("Distance (cm): ");
  Serial.println(distance);
  return distance; 
}

void moveAutoBot(){
  int distance;
  distance = getDistance();
  
  if(distance<30){
    checkSides();
  } else {
    moveBot(forward); 
  }
}

void checkSides(){
  moveBot(halt);
  delay(1000);

  Serial.println("Checking right...");
  readerservo.write(35);
  delay(1000);
  int dist_r = getDistance();

  Serial.println("Checking left...");
  readerservo.write(145);
  delay(1000);
  int dist_l = getDistance();

  readerservo.write(90);
  delay(500);

  if (dist_l < 30 && dist_r < 30) {
    moveBot(backward); 
  } else if (dist_l < dist_r) {
    moveBot(right);
  } else {
    moveBot(left);
  }
  delay(500);
}
