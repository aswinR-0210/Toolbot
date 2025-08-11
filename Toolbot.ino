#define echopin A4 // Echo pin
#define trigpin A5 // Trigger pin

int motor_r2 = 9;
int motor_r1 = 10;
int motor_12 = 5;
int motor_11 = 6;

int speed = 115;
int frontdist;
long duration;
int setdist = 10;

int L_S = A0; // Sensor Left
int R_S = A1; // Sensor Right

long data() {
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  duration = pulseIn(echopin, HIGH);
  return duration / 29 / 2; // distance in cm
}

void stopMotor() {
  analogWrite(motor_11, 0);
  analogWrite(motor_12, 0);
  analogWrite(motor_r1, 0);
  analogWrite(motor_r2, 0);
}

void forward() {
  analogWrite(motor_11, speed);
  analogWrite(motor_12, 0);
  analogWrite(motor_r1, 0);
  analogWrite(motor_r2, speed);
}

void backward() {
  analogWrite(motor_11, 0);
  analogWrite(motor_12, speed);
  analogWrite(motor_r1, speed);
  analogWrite(motor_r2, 0);
}

void turnRight() {
  analogWrite(motor_11, 0);
  analogWrite(motor_12, speed);
  analogWrite(motor_r1, 0);
  analogWrite(motor_r2, speed);
}

void turnLeft() {
  analogWrite(motor_11, speed);
  analogWrite(motor_12, 0);
  analogWrite(motor_r1, speed);
  analogWrite(motor_r2, 0);
}

void setup() {
  pinMode(motor_11, OUTPUT);
  pinMode(motor_12, OUTPUT);
  pinMode(motor_r1, OUTPUT);
  pinMode(motor_r2, OUTPUT);
  
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  
  pinMode(L_S, INPUT);
  pinMode(R_S, INPUT);

  Serial.begin(9600);
  delay(1000);
}

void loop() {
  frontdist = data();
  Serial.println(frontdist);

  if (frontdist > setdist) {
    if ((digitalRead(L_S) == 0) && (digitalRead(R_S) == 0)) {
      forward();
    }
    else if ((digitalRead(L_S) == 0) && (digitalRead(R_S) == 1)) {
      turnRight();
    }
    else if ((digitalRead(L_S) == 1) && (digitalRead(R_S) == 0)) {
      turnLeft();
    }
  } 
  else {
    turnLeft();
    delay(350);
    forward();
    delay(1000);
    turnRight();
    delay(200);
    forward();
    delay(500);
  }
}
