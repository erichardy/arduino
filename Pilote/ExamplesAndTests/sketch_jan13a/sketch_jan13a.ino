#include <L298N.h>

// https://github.com/AndreaLombardo/L298N/blob/master/examples/L298N-Callback/L298N-Callback.ino

//pin definition
#define EN 9
#define IN1 8
#define IN2 7

//create a motor instance
L298N motor(EN, IN1, IN2);

//initial speed
unsigned short theSpeed = 250;

void setup() {

  //set the initial speed
  motor.setSpeed(theSpeed);
  motor.reset();
}

void loop() {

  //move motor for 5 seconds and then execute the callback function
  /*
  motor.forwardFor(1000, callback);
  delay(1000);
  motor.backwardFor(1000, callback);
  */
  
  motor.forwardFor(2000);
  motor.reset();

  motor.setSpeed(theSpeed);

  motor.backwardFor(2000);
  motor.reset();

  if (theSpeed >= 250) {
    theSpeed = 150;
  } else {
    theSpeed = 250;
  }
  motor.setSpeed(theSpeed);
}

void motorReset() {
  motor.reset();
}

void callback() {

  //each time the callback function is called increase the speed of the motor or reset to 0
  if (theSpeed <= 255) {
    theSpeed += 25;
  } else {
    theSpeed = 50;
  }

  //re-enable motor movements
  motor.reset();
  //set the new speed
  motor.setSpeed(theSpeed);

}
