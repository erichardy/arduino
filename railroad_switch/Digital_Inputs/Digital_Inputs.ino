
/*
 * juste pour avoir une idee de gestion d'un on/off avec un seul bouton
 */

int ledPin = 5;
int buttonApin = 9;
int buttonBpin = 8;
int delay_time = 300;

byte leds = 0;
byte led = 0;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);  
  pinMode(buttonBpin, INPUT_PULLUP);
  digitalWrite(ledPin, LOW);
  led = 0 ;
}

void loop() 
{
  // digitalWrite(ledPin, HIGH);
  if ((digitalRead(buttonApin) == LOW) && (led == 0)) {
      digitalWrite(ledPin, HIGH);
      led = 1;
      delay(delay_time);
    }
    if ((digitalRead(buttonApin) == LOW) && (led == 1)) {
      digitalWrite(ledPin, LOW);
      led = 0;
      delay(delay_time);
    }
  /*
  if (digitalRead(buttonBpin) == LOW)
  {
    digitalWrite(ledPin, LOW);
  }
  */
}
