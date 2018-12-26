
#include <Servo.h>
#define ALL 255
#define NO_ONE 0

int angle0 = 5;
int angle = 53;
int buttonPin = 7;
int button_delay = 300;

/* commandes des leds par 74HC595 */
int latchPin = 11;
int clockPin = 9;
int dataPin = 12;
byte leds = 0;
/* Numeros des leds */
int led1_1 = 128;
int led1_2 = 64;
int led2_1 = 32;
int led2_2 = 16;
int led3_1 = 8;
int led3_2 = 4;
int led4_1 = 2;
int led4_2 = 1;

/* commandes des servos */
int servo1 = 8;

void turnOnLight(int light)
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, light);
   digitalWrite(latchPin, HIGH);
}

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
        turnOnLight(led1_2);
        Serial.print("state = 1\n");
      }
      if (current_state == 1) {
        this->init_state();
        this->state = 0;
        turnOnLight(led1_1);
        Serial.print("state = 0\n");
      }
    }
};

railSwitch aiguil1 ; 

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  aiguil1.attach(servo1);
  aiguil1.init_state();
  Serial.begin(9600);

  /* initialisation du 74HC595 */
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  turnOnLight(NO_ONE);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    aiguil1.change_state();
    Serial.print("buttonPin : ");
    Serial.println(digitalRead(buttonPin), 1);
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
