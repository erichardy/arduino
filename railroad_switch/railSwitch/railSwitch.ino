
#include <Servo.h>
#define ALL 255
#define NO_ONE 0

int button_delay = 300;

class railSwitch: public Servo {
  public:
    // state : 0 ou 1, initial == 0
    byte state = 0;
    int current_state;
    unsigned char angle0;
    unsigned char angle;
    unsigned char command;
    unsigned char button;

    int init_state() {
      this->write(this->angle0);
      this->state = 0;
    }
    int other_state() {
      this->write(this->angle);
      this->state = 1;
    }
    int change_state() {
      current_state = this->state;
      if (current_state == 0) {
        this->write(this->angle);
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

/* Nombre d'aiguillages */
const char NBSWITCH = 5;

railSwitch aiguil1;
/* les aiguillages */
railSwitch aiguils[NBSWITCH];

/* les angles (initial et autre) de chaque servo */
unsigned char angles0[NBSWITCH] = {5, 5, 5, 5, 5};
unsigned char angles[NBSWITCH] = {130, 53, 53, 53, 180};

/* les pins des commandes des servo */
unsigned char commands[NBSWITCH] = {9, 10, 11, 12, 13};
unsigned char buttons[NBSWITCH] = {8, 7, 6, 5, 4};

unsigned char i;

void setup() {
  Serial.begin(9600);
  for (i = 0; i < NBSWITCH; i++){
    Serial.print(i);
    Serial.print("\n");
    pinMode(buttons[i], INPUT_PULLUP);
    aiguils[i].angle0 = angles0[i];
    aiguils[i].angle = angles[i];
    aiguils[i].command = commands[i];
    aiguils[i].button = buttons[i];
    aiguils[i].attach(aiguils[i].command);
    aiguils[i].init_state();
  }
  i = 0;
}

void loop() {
  /*
  if (digitalRead(aiguils[0].button) == LOW){
    aiguils[0].change_state();
    Serial.print("boutton : ");
    Serial.println(aiguils[0].button, DEC);
    delay(button_delay);
  }
  
  if (digitalRead(aiguils[1].button) == LOW){
    aiguils[1].change_state();
    Serial.print("boutton : ");
    Serial.println(aiguils[1].button, DEC);
    delay(button_delay);
  }
  
  if (digitalRead(aiguils[2].button) == LOW){
    aiguils[2].change_state();
    Serial.print("boutton : ");
    Serial.println(aiguils[2].button, DEC);
    delay(button_delay);
  }
  
  if (digitalRead(aiguils[3].button) == LOW){
    aiguils[3].change_state();
    Serial.print("boutton : ");
    Serial.println(aiguils[3].button, DEC);
    delay(button_delay);
  }
  
  if (digitalRead(aiguils[4].button) == LOW){
    aiguils[4].change_state();
    Serial.print("boutton : ");
    Serial.println(aiguils[4].button, DEC);
    delay(button_delay);
  }
  */
  if (i >= NBSWITCH) {
    i = 0;
  }
  if (digitalRead(int(aiguils[i].button)) == LOW){
    aiguils[i].change_state();
    Serial.print("boutton : ");
    Serial.println(aiguils[i].button, DEC);
    delay(button_delay);
  }
  i++;
  delay(20);
  
}
