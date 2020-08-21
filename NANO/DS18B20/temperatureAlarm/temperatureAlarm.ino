
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define TONE 8
#define POT_PIN A2
#define DS18B20_PIN 9
#define TEMPERATURE_PRECISION 12
#define BASE_FREQ 440
int freq = 440;
bool sirenUp = 0;

#define nbFreqs 10
int freqs[nbFreqs] = {440, 550, 660, 770, 880, 990, 1000, 1220, 1440, 1550};


LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
// Arduino        D12 D11 D7 D6 D5 D4
// LCD            RS  E   D4 D5 D6 D7
// Other LCD pins below
// VSS : GND
// VDD : 5V
// V0 : milieu pot (contrast) ; autres pot : GND et GND
// RW : GND

OneWire oneWire(DS18B20_PIN);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
// arrays to hold device address
DeviceAddress insideThermometer;
float tempC; // Current temperature
float tempT = 25.0; // Target temperature
int setTarget, target;
bool alarm = 0; // alarm set or not set

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// dispTemps : display temperatures, current and target
int lcdTemps(float current, float target) {
  lcd.setCursor(0 ,0);
  lcd.print("Actuelle :       ");
           // 01234567890123456
  lcd.setCursor(11, 0);
  lcd.print(current);
  lcd.setCursor(0, 1);
  lcd.print("Alarme a :       ");
          // 01234567890123456
  lcd.setCursor(11, 1);
  lcd.print(target);
}

void siren(int offset) {
  int f;
  if (sirenUp) {
    for (f = 0; f < nbFreqs; f++) {
      tone(TONE, freqs[f]);
      delay(50);
    }
    noTone(TONE);
  } else {
    for (f = nbFreqs - 1; f >= 0; f--) {
      tone(TONE, freqs[f]);
      delay(50);
    }
    noTone(TONE);
  }
}

void setup() {
  pinMode(POT_PIN, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  sensors.begin();
  
  lcd.clear();
  lcd.setCursor(0, 0);

  // report parasite power requirements
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
  if (!sensors.getAddress(insideThermometer, 0)){
    Serial.println("Unable to find address for Device 0");
  }
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();
  sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);

  noTone(TONE);
}

void loop() {
  sensors.requestTemperatures(); // Send the command to get temperatures
  tempC = sensors.getTempC(insideThermometer);
  Serial.print("Temp C: ");
  Serial.println(tempC);
  setTarget = analogRead(POT_PIN);
  target = map(setTarget, 0, 1024, 0, 1400);
  tempT = target / 10.0;
  Serial.println(tempT);
  lcdTemps(tempC, tempT); // pour tests + 76.0
  if (tempC >= tempT) {
    if (tempT > 1) {
      siren(0);
    } else {
      noTone(TONE);
    }
  } else {
    noTone(TONE);
  }
  sirenUp = not(sirenUp);
  /*
  lcdVolume(volume);
  volume += 5;
  if (volume > 99) {
    volume = 1;
  }
  alarm = not(alarm);
  */
  // delay(200);
}
