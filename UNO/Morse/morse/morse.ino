
#include "MorseAlphabet.h"
/*
#include <Wire.h>
#include <SparkFunT5403.h>
T5403 barometer(MODE_I2C);
*/
float tc;                        // T°C du capteur
double pa;                        // Pression atmosphérique absolue 


int MorseVitesse = 15;                                            // Vitesse Mot Minute 
int MorseToneFreq = 900;                                        // Frequence Tonalité

int pinPTT = 4;                             // Pin 4 passe au niveau haut en Tx
int MorseLEDPin = 13;                       // Pin 13 passe au niveau haut pour les traits et points
int MorseTonePin = 5;                       // Pin 5 fournit un signal audio 700Hz CW
int cw;
int CWpoint = 1200 / MorseVitesse;
int CWtrait = CWpoint * 3;
int CWword = CWpoint * 7;
int letter;
char code;
String MorseLetter;
int istr;
int i;

String message;

void on() {
  digitalWrite(MorseLEDPin, HIGH);
  tone(MorseTonePin, MorseToneFreq);
}

void off() {
  digitalWrite(MorseLEDPin, LOW);
  noTone(MorseTonePin);
}

void TransmitLetter(String MorseLetter) {
  for (i = 0; i < MorseLetter.length(); i++){
    if (MorseLetter[i] == '.'){
      // duree d'un point
      cw = CWpoint;
      Serial.print('.');
    } else {
      // duree d'un trait
      cw = CWtrait;
      Serial.print('-');
    }
    on();
    delay(cw);
    off();
    // entre chaque lettre, duree d'un point
    delay(CWpoint);
  }
  delay(CWtrait);
}

void TransmitMorse(String msg){
  // Serial.println("in transmitMorse");
  CWpoint = 1200 / MorseVitesse;
  CWtrait = CWpoint * 3;
  for (istr = 0; istr < msg.length(); istr++) {
    // Serial.println((int) msg[istr]);
    letter = (int) msg[istr] - 33;
    if (letter < 0) {
      // espace qui separe deux mots
      delay(CWword);
    } else {
      // Serial.println(letter);
      MorseLetter = MorseAlphabet[letter];
      Serial.print(MorseLetter);
      Serial.print(" : ");
      TransmitLetter(MorseLetter);
      Serial.println();
    }
  }
  delay(CWpoint * 7);
  Serial.println("End of Message");
}


void setup() {
    Serial.begin(9600);
    pinMode(pinPTT, OUTPUT);
    pinMode(MorseLEDPin, OUTPUT);
    pinMode(MorseTonePin, OUTPUT);
    Serial.println("Balise FX3UHX - Cours F8KCF ");
    Serial.println();
}

void loop() {
    /*
    tc = barometer.getTemperature(CELSIUS);
    pa  = barometer.getPressure(MODE_ULTRA);
    */
    tc = 12.54;
    pa = 1032;
    /*
    message = "FX3UHX  FX3UHX  FX3UHX  IN78RK  IN78RK  IN78RK BT PAR  1 W 1 W 1W QNH pa QNH pa QNH pa TEMP tc TEMP tc TEMP tc ";
    */
    // !!! Ne pas mettre de lettres en minuscules dans le message !!!!
    message = String("AB CD");
    message = String(message + " TEMP ");
    message += String(tc, 2);
    digitalWrite(pinPTT, HIGH);
    Serial.println(message);
    TransmitMorse(message);
    digitalWrite(pinPTT, LOW);
    delay(8000);
}
