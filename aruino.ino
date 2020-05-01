#include <Wire.h>
int Index;

//Значения поворота мотора
boolean m1 = true; // motor 1
boolean m2 = true; // motor 2
boolean m3 = false; // motor 3

void setup() {
  // Настройка соединения raspi - arduino
  Serial.begin(9600);
  // Настройка шаговых двигателей
  // motor 1
  pinMode(6, OUTPUT); //Enable
  pinMode(5, OUTPUT); //Step
  pinMode(4, OUTPUT); //Direction

  digitalWrite(6,LOW);

  //motor 2
  pinMode(9, OUTPUT); //Enable
  pinMode(8, OUTPUT); //Step
  pinMode(7, OUTPUT); //Direction

  digitalWrite(9,LOW);

  //motor 3
  pinMode(12, OUTPUT); //Enable
  pinMode(11, OUTPUT); //Step
  pinMode(10, OUTPUT); //Direction

  digitalWrite(12,LOW); // motor 1
  pinMode(6, OUTPUT); //Enable
  pinMode(5, OUTPUT); //Step
  pinMode(4, OUTPUT); //Direction

  digitalWrite(6,LOW);

  //motor 2
  pinMode(9, OUTPUT); //Enable
  pinMode(8, OUTPUT); //Step
  pinMode(7, OUTPUT); //Direction

  digitalWrite(9,LOW);

  //motor 3
  pinMode(12, OUTPUT); //Enable
  pinMode(11, OUTPUT); //Step
  pinMode(10, OUTPUT); //Direction

  digitalWrite(12,LOW);
}

void Rotate(byte motor, boolean state ){
  if (state){
    m1 = true;
    digitalWrite(4, HIGH);
    m2 = true;
    digitalWrite(7, HIGH);
    m3 = false;
    digitalWrite(10, LOW);
  }
  else{
    m1 = false;
    digitalWrite(4,LOW);
    m2 = false;
    digitalWrite(7, LOW);
    m3 = true;
    digitalWrite(10, HIGH);
  }
  byte pin = 0;
  if (motor == 1){
    pin = 5;
  }
  else if (motor == 2){
    pin = 8;
  }
  else{
    pin = 11;
  }
  for(Index = 0; Index < 100; Index++)
  {
    digitalWrite(pin,HIGH);
    delayMicroseconds(2500);
    digitalWrite(pin,LOW);
    delayMicroseconds(2500);
  }
}

void loop() {
  processMessage();
}

void processMessage() {
// c - close m1 f - open m1
// v - close m2 g - open m2
// b - close m3 h - open m3
String data;
  if (Serial.available() > 0){
    data = Serial.readStringUntil('\n');
    Serial.print("You sent me: ");
    Serial.println(data);
  }
  if (data == "c"){
    Rotate(1, true);
    Serial.write("m1 close");
    data = "";
  }

  if (data == "f"){
    Rotate(1, false);
    Serial.write("m1 open");
    data = "";
  }
  if (data == "v"){
    Rotate(2, true);
    Serial.write("m2 close");
    data = "";
  }
  if (data == "g"){
    Rotate(2, false);
    Serial.write("m2 open");
    data = "";
  }
  if (data == "b"){
    Rotate(3, true);
    Serial.write("m3 close");
    data = "";
  }
  if (data == "h"){
    Rotate(3, false);
    Serial.write("m1 open");
    data = "";
  }
}