#include <AFMotor.h>
#include <SoftwareSerial.h>

AF_DCMotor top_left(1);
AF_DCMotor top_right(4);
AF_DCMotor bottom_left(2);
AF_DCMotor bottom_right(3);

SoftwareSerial bluetooth(A0, A1);

#define FORWARD_COMMAND 'F'
#define BACKWARD_COMMAND 'B'
#define LEFT_COMMAND 'L'
#define RIGHT_COMMAND 'R'
#define STOP_COMMAND 'S'

unsigned long last_bluetooth_receive = 0;
unsigned long time_since_last_bluetooth_receive;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bluetooth.begin(9600);
  top_left.setSpeed(255);
  bottom_left.setSpeed(255);
  top_right.setSpeed(255);
  bottom_right.setSpeed(255);
}
char command_char;
byte speed;
void loop() {
  // put your main code here, to run repeatedly:
  if (bluetooth.available() >= 2) {
    last_bluetooth_receive = millis();
    command_char = bluetooth.read();
    speed = bluetooth.read();
    top_left.setSpeed(speed);
    bottom_left.setSpeed(speed);
    top_right.setSpeed(speed);
    bottom_right.setSpeed(speed);
    if (command_char == FORWARD_COMMAND) {
      top_left.run(FORWARD);
      top_right.run(FORWARD);
      bottom_left.run(FORWARD);
      bottom_right.run(FORWARD);
    }
    if (command_char == BACKWARD_COMMAND) {
      top_left.run(BACKWARD);
      top_right.run(BACKWARD);
      bottom_left.run(BACKWARD);
      bottom_right.run(BACKWARD);
    }
    if (command_char == LEFT_COMMAND) {
      top_left.run(FORWARD);
      top_right.run(RELEASE);
      bottom_left.run(FORWARD);
      bottom_right.run(RELEASE);
    }
    if (command_char == RIGHT_COMMAND) {
      top_left.run(RELEASE);
      top_right.run(FORWARD);
      bottom_left.run(RELEASE);
      bottom_right.run(FORWARD);
    }
    if (command_char == STOP_COMMAND) {
      top_left.run(RELEASE);
      top_right.run(RELEASE);
      bottom_left.run(RELEASE);
      bottom_right.run(RELEASE);
    }
    Serial.write(command_char);
    Serial.print(speed);
    Serial.println();
  }
  if (Serial.available()) {
    bluetooth.write(Serial.read());
  }
  time_since_last_bluetooth_receive = millis() - last_bluetooth_receive;
  if (time_since_last_bluetooth_receive > 200) {
    // if it has been more than 200 milliseconds with no bluetooth data receive
    // stop all motors
    top_left.run(RELEASE);
    top_right.run(RELEASE);
    bottom_left.run(RELEASE);
    bottom_right.run(RELEASE);
  }
}
