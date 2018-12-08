
#include <Servo.h>

int angle0 = 5;
int angle = 53;
int buttonPin = 10;
int button_delay = 300;

class railSwitch: public Servo {
  public:
    // state : 0 ou 1, initial == 0
    byte state = 0;
    int current_state;

    int init_state() {
      this->write(angle0);
      this->state = 0;
    }
    int other_state() {
      this->write(angle);
      this->state = 1;
    }
    int change_state() {
      current_state = this->state;
      if (current_state == 0) {
        this->write(angle);
        this->state = 1;
        Serial.print("state = 1\n");
      }
      if (current_state == 1) {
        this->init_state();
        this->state = 0;
        Serial.print("state = 0\n");
      }
    }
};

railSwitch aiguil1 ; 

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  aiguil1.attach(9);
  aiguil1.init_state();
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    aiguil1.change_state();
    delay(button_delay);
  }
  /*
  if ((digitalRead(buttonPin) == LOW) && (aiguil1.state == 0)) {
      aiguil1.other_state();
      Serial.print("other_state\n");
      delay(button_delay);
    }
    if ((digitalRead(buttonPin) == LOW) && (aiguil1.state == 1)) {
      aiguil1.init_state();
      Serial.print("initial_state\n");
      delay(button_delay);
    }
    */
}
