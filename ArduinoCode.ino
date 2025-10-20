#include <Servo.h>

/* ----- PINS ----- */
#define M1_IN1 2
#define M1_IN2 3
#define M2_IN1 4
#define M2_IN2 5
#define M1_EN 6
#define M2_EN 9

#define SENSOR_LEFT 7
#define SENSOR_RIGHT 8

#define US_FRONT_TRIG 10
#define US_FRONT_ECHO 11
#define US_BACK_TRIG 12
#define US_BACK_ECHO 13

#define SERVO_PIN A0

Servo drawerServo;

/* ----- GLOBALS ----- */
bool robotRunning = false;
bool destinationReached = false;
unsigned long bothSensorsSince = 0;
const int MOTOR_SPEED = 200;
const unsigned long DESTINATION_CONFIRM_MS = 600; // 600ms both sensors on line
const int OBSTACLE_DIST_CM = 20; 

/* ----- FUNCTIONS ----- */
long readUltrasonicCM(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000); 
  long distance = duration * 0.034 / 2; 
  return distance;
}

void motorStop() { analogWrite(M1_EN,0); analogWrite(M2_EN,0); digitalWrite(M1_IN1,LOW); digitalWrite(M1_IN2,LOW); digitalWrite(M2_IN1,LOW); digitalWrite(M2_IN2,LOW);}
void motorForward(int s){digitalWrite(M1_IN1,HIGH);digitalWrite(M1_IN2,LOW);digitalWrite(M2_IN1,HIGH);digitalWrite(M2_IN2,LOW);analogWrite(M1_EN,s);analogWrite(M2_EN,s);}
void motorLeft(int s){digitalWrite(M1_IN1,LOW);digitalWrite(M1_IN2,LOW);digitalWrite(M2_IN1,HIGH);digitalWrite(M2_IN2,LOW);analogWrite(M1_EN,0);analogWrite(M2_EN,s);}
void motorRight(int s){digitalWrite(M1_IN1,HIGH);digitalWrite(M1_IN2,LOW);digitalWrite(M2_IN1,LOW);digitalWrite(M2_IN2,LOW);analogWrite(M1_EN,s);analogWrite(M2_EN,0);}
void openDrawers(){drawerServo.write(0); Serial.println("DRAWER_OPEN");}
void closeDrawers(){drawerServo.write(90);}

/* ----- SETUP ----- */
void setup() {
  pinMode(M1_IN1,OUTPUT); pinMode(M1_IN2,OUTPUT);
  pinMode(M2_IN1,OUTPUT); pinMode(M2_IN2,OUTPUT);
  pinMode(M1_EN,OUTPUT); pinMode(M2_EN,OUTPUT);

  pinMode(SENSOR_LEFT,INPUT); pinMode(SENSOR_RIGHT,INPUT);

  pinMode(US_FRONT_TRIG,OUTPUT); pinMode(US_FRONT_ECHO,INPUT);
  pinMode(US_BACK_TRIG,OUTPUT); pinMode(US_BACK_ECHO,INPUT);

  drawerServo.attach(SERVO_PIN); closeDrawers();
  
  Serial.begin(9600); // Communication with ESP8266
}

/* ----- LOOP ----- */
void loop() {
  if (!robotRunning || destinationReached) { motorStop(); return; }

  // Obstacle detection
  long frontDist = readUltrasonicCM(US_FRONT_TRIG, US_FRONT_ECHO);
  long backDist = readUltrasonicCM(US_BACK_TRIG, US_BACK_ECHO);

  if (frontDist < OBSTACLE_DIST_CM) { motorStop(); Serial.println("OBSTACLE_FRONT"); return;}
  if (backDist < OBSTACLE_DIST_CM) { motorStop(); Serial.println("OBSTACLE_BACK"); return;}

  // Line following
  int left = digitalRead(SENSOR_LEFT);
  int right = digitalRead(SENSOR_RIGHT);

  if (left==LOW && right==LOW) motorForward(MOTOR_SPEED);
  else if (left==LOW && right==HIGH) motorLeft(MOTOR_SPEED-50);
  else if (left==HIGH && right==LOW) motorRight(MOTOR_SPEED-50);
  else motorStop();

  // Destination detection
  if (left==LOW && right==LOW) {
    if (bothSensorsSince==0) bothSensorsSince=millis();
    else if (millis()-bothSensorsSince>DESTINATION_CONFIRM_MS){
      destinationReached=true; motorStop(); openDrawers(); Serial.println("DESTINATION");
    }
  } else bothSensorsSince=0;

  delay(20);
}
