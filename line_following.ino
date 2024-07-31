#include <Servo.h>

#define ENA 5
#define IN1 6
#define IN2 7
#define IN3 9
#define IN4 10
#define ENB 11

#define IR_SENSOR_LEFT 2 //2
#define IR_SENSOR_CENTER 8 //8
#define IR_SENSOR_RIGHT 4 //4
//#define ULTRASONIC_TRIG 3
//#define ULTRASONIC_ECHO 4

int sensorValueLeft = 0;
int sensorValueCenter = 0;
int sensorValueRight = 0;
int lineThreshold = 0;
int groundThreshold = 0;

//long duration;
//int distance;

void calibrateSensors() {
  int sensorReadLeft = 0;
  int sensorReadCenter = 0;
  int sensorReadRight = 0;
  int numReadings = 10;

  Serial.println("Calibrating sensors...");
  delay(2000);

  for (int i = 0; i < numReadings; i++) {
    sensorReadLeft += analogRead(IR_SENSOR_LEFT);
    sensorReadCenter += analogRead(IR_SENSOR_CENTER);
    sensorReadRight += analogRead(IR_SENSOR_RIGHT);
    delay(100);
  }

  sensorReadLeft /= numReadings;
  sensorReadCenter /= numReadings;
  sensorReadRight /= numReadings;

  lineThreshold = (sensorReadLeft + sensorReadCenter + sensorReadRight) / 3;


}


void moveForward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void moveBackward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void turnLeft(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void turnRight(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


// int getDistance() {
//   return distance;
// }

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IR_SENSOR_LEFT, INPUT);
  pinMode(IR_SENSOR_CENTER, INPUT);
  pinMode(IR_SENSOR_RIGHT, INPUT);
  // pinMode(ULTRASONIC_TRIG, OUTPUT);
  // pinMode(ULTRASONIC_ECHO, INPUT);

  Serial.begin(9600);

  calibrateSensors();
}

void loop() {
  sensorValueLeft = analogRead(IR_SENSOR_LEFT);
  sensorValueCenter = analogRead(IR_SENSOR_CENTER);
  sensorValueRight = analogRead(IR_SENSOR_RIGHT);
  Serial.println(sensorValueCenter);
  // Serial.println(sensorValueRight);
  //Serial.println(sensorValueLeft);

  delay(1000);

  // int distance = getDistance();
  // Serial.print("Distance: ");
  // Serial.println(distance);

  // if (distance < 20) {
  //   stopMotors();
  //   delay(500);

  //   moveBackward(150);
  //   delay(500);
  //   turnRight(150);
  //   delay(500);
  //   stopMotors();
  //   delay(500);
  // } else {

    if (sensorValueCenter < lineThreshold ) {
      //Serial.println("FRENTE...");
      //Serial.println(sensorValueCenter);
      moveForward(150);
    } else if (sensorValueRight < lineThreshold) {
      //Serial.println(sensorValueRight);
      //Serial.println("ESQUERDA...");

      turnLeft(150);
    }
    else if (sensorValueLeft < lineThreshold) {
      // Serial.println(sensorValueCenter);
      // Serial.println(sensorValueRight);
      //Serial.println("DIREITA...");
      turnRight(150);
       }


  delay(100);
}

