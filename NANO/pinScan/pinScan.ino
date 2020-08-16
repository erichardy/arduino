

int pin11 = 11; //D11

int pin7 = 7; //D7 : pin N° 10 on the board
int pin6 = 6; //D6 : pin N° 9 on the board
int pin5 = 5; //D5 : pin N° 8 on the board
int pin4 = 4; //D4 : pin N° 7 on the board
int pin3 = 3; // D3 : pin N° 6 on the board
int pin2 = 2; // D2 : pin N° 5 on the board
int Apin0 = A0; // == 14
int Apin1 = A1; // == 15
int Apin2 = A2; // == 16
int Apin3 = A3; // == 17
int Apin4 = A4; // == 18
int Apin5 = A5; // == 19
int Apin6 = A6; // == 20 ; NB: analogWrite() on this pin doesn't work, must test f analogRead() is ok ?
int Apin7 = A7; // == 21 ; NB: analogWrite() on this pin doesn't work, must test f analogRead() is ok ?
int pinTest = pin11;
int i;

void setup() {
  Serial.begin(9600);
  Serial.println("--------");
  Serial.println(A0);
  Serial.println(A1);
  Serial.println(A2);
  Serial.println(A3);
  Serial.println(A4);
  Serial.println(A5);
  Serial.println(A6);
  Serial.println(A7);
  Serial.println("--------");
  Serial.println("--------");  
  pinMode(pinTest, OUTPUT);
  
}

void loop() {
  digitalWrite(pinTest, LOW);
  delay(100);
  digitalWrite(pinTest, HIGH);
  delay(500);
  /*  
  Serial.println(A0);
  Serial.println(A1);
  Serial.println(A2);
  Serial.println(A3);
  Serial.println(A4);
  Serial.println(A5);
  Serial.println(A6);
  Serial.println(A7);
  */
}
