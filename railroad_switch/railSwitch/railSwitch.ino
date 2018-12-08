
#include <Servo.h>

int angle = 50;
int buttonPin = 10;
int button_delay = 300;

class railSwitch: public Servo {
  public:
    // state : 0 ou 1, initial == 0
    byte state = 0;

    int init_state() {
      this->write(0);
      this->state = 0;
    }
    int other_state() {
      this->write(angle);
      this->state = 1;
    }
    
};

railSwitch aiguil1 ; 

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  aiguil1.attach(9);
  aiguil1.init_state();

}

void loop() {
  if ((digitalRead(buttonPin) == LOW) && (aiguil1.state == 0)) {
      aiguil1.other_state();
      delay(button_delay);
    }
    if ((digitalRead(buttonPin) == LOW) && (aiguil1.state == 1)) {
      aiguil1.init_state();
      delay(button_delay);
    }
}
