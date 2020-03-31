
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
    unsigned char alpha; // angle pour tests
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
unsigned char angles0[NBSWITCH] = {30, 25, 30, 30, 20};
unsigned char angles[NBSWITCH] = {120, 120, 135, 125, 120};

/* les pins des commandes des servo */
unsigned char commands[NBSWITCH] = {9, 10, 11, 12, 13};
unsigned char buttons[NBSWITCH] = {8, 7, 6, 5, 4};

unsigned char i;

/*
 * Micro Servo 9g :
 * marron : masse
 * rouge : +5V (milieu)
 * jaune : commande
 */
void setup() {
  delay(3000);

  Serial.begin(9600);
  for (i = 0; i < NBSWITCH; i++){
    Serial.print("Aiguillage : ");
    Serial.println(i + 1);
    Serial.print("button : ");
    Serial.println(i);
    pinMode(buttons[i], INPUT_PULLUP);
    aiguils[i].angle0 = angles0[i];
    aiguils[i].angle = angles[i];
    aiguils[i].alpha = 0;
    aiguils[i].command = commands[i];
    
    aiguils[i].button = buttons[i];
    Serial.print("Etat : ");
    Serial.println(aiguils[i].state);
    aiguils[i].attach(aiguils[i].command);
    Serial.print("Attached ? ");
    Serial.println(aiguils[i].attached());
    if (aiguils[i].attached()) {
        aiguils[i].init_state();
        delay(500);
        aiguils[i].change_state();
        Serial.print("Etat : ");
        Serial.println(aiguils[i].state);
        delay(500);
        aiguils[i].change_state();
        Serial.print("Etat : ");
        Serial.println(aiguils[i].state);
        delay(500);
        aiguils[i].init_state();
        Serial.print("Etat : ");
        Serial.println(aiguils[i].state);
        Serial.println("------------------------");
    }
  delay(2000);
  }
  i = 0;
}

void loop() {
  
  if (i >= NBSWITCH) {
    i = 0;
  }
  if (digitalRead(int(aiguils[i].button)) == LOW){
    Serial.print("Aiguillage : ");
    Serial.print(i + 1);
    Serial.print(" , ");
    // Serial.print(" boutton : ");
    // Serial.println(aiguils[i].button, DEC);
    aiguils[i].change_state();
    delay(button_delay);
  }
  i++;
  delay(20);
  
}
