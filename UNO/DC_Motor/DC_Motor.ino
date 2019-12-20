//www.elegoo.com
//2016.12.12

/************************
Exercise the motor using
the L293D chip
************************/

#define ENABLE 5 // vers enable 1 du L293
#define DIRA 3 // vers input2 du L293
#define DIRB 4 // vers input1 du L293

int i;
int count = 0;
 
void setup() {
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
}

int backandforth(int enable, int dira, int dirb) {
  //---back and forth example
    Serial.println("One way, then reverse");
    digitalWrite(ENABLE,HIGH); // enable on
    for (i=0;i<5;i++) {
      digitalWrite(DIRA,HIGH); //one way
      digitalWrite(DIRB,LOW);
      delay(500);
      digitalWrite(DIRA,LOW);  //reverse
      digitalWrite(DIRB,HIGH);
      delay(500);
    }
  digitalWrite(ENABLE,LOW); // disable
  delay(2000);
}

void fastSlow(int enable, int dira, int dirb) {
  Serial.println("fast Slow example");
  //---fast/slow stop example
  digitalWrite(ENABLE,HIGH); //enable on
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  delay(3000);
  digitalWrite(ENABLE,LOW); //slow stop
  delay(1000);
  digitalWrite(ENABLE,HIGH); //enable on
  digitalWrite(DIRA,LOW); //one way
  digitalWrite(DIRB,HIGH);
  delay(3000);
  digitalWrite(DIRA,LOW); //fast stop
  delay(2000);
}

void pwmFullSlow(int enable, int dira, int dirb) {
  Serial.println("PWM full then slow");
  //---PWM example, full speed then slow
  analogWrite(ENABLE,255); //enable on
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  delay(2000);
  analogWrite(ENABLE,180); //half speed
  delay(2000);
  analogWrite(ENABLE,128); //half speed
  delay(2000);
  analogWrite(ENABLE,50); //half speed
  delay(2000);
  analogWrite(ENABLE,128); //half speed
  delay(2000);
  analogWrite(ENABLE,180); //half speed
  delay(2000);
  analogWrite(ENABLE,255); //half speed
  delay(2000);
  digitalWrite(ENABLE,LOW); //all done
  delay(10000);
}

void slowDonw(int enable, int dira, int dirb) {
  // digitalWrite(DIRA,HIGH); //one way
  // digitalWrite(DIRB,LOW);
  for (i = 255; i > 0; i -= 2) {
    digitalWrite(DIRA,HIGH);
    digitalWrite(DIRB,LOW);
    analogWrite(ENABLE, i);
    delay(100);
  }
}

void fasterSlower(int enable, int dira, int dirb) {
  for (i = 0; i < 255; i++) {
    analogWrite(ENABLE, i);
    digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, LOW);
    delay(100);
  }
  for (i = 255; i > 0; i--) {
    analogWrite(ENABLE, i);
    digitalWrite(DIRA, LOW);
    digitalWrite(DIRB, HIGH);
    delay(100);
  }
}

void loop() {
  // pwmFullSlow(ENABLE, DIRA, DIRB);
  // backandforth(ENABLE, DIRA, DIRB);
  // slowDonw(ENABLE, DIRA, DIRB);
  if (count < 2) {
  fasterSlower(ENABLE, DIRA, DIRB);
  count++;
  }
}
