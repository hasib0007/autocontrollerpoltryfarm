#include <Servo.h>
#include <dht.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);


//  temperature variable declare
#define temppin 13  //declare temperature pin
dht DHT;
int tempdata;
float tempval;
float high = 32.50; 
float Max = 32.20;
float Min = 32.00;
float Low = 31.50;
float Vlow = 31.00;


//heting lights variable declare
int led[] = {12, 11, 10};
//cooling fan variable declare
int fan = 9;
int fan2 = 8;



//rain sensor and servo variable declare
int rainpin = A0;
int rainval;
int servopin = 7;
Servo servo;

//auto water pump on off variable
int trg = 6;
int echo = 5;
int duration,cm;
float inc;
int pumpon = 3;
int pump = 4;


// food 
int ldr = 3;
int ldrval = 0;
int food = A1;

void setup() {
// heting lights pin mode define
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
  pinMode(led[2], OUTPUT);
//cooling fan pin mode define
  pinMode(fan, OUTPUT);
  pinMode(fan2, OUTPUT);

// rain pin mode define
  pinMode(A0, INPUT);
// servo pin attach
  servo.attach(servopin);
  servo.write(0);

//display section
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);


// ultrasonic pin mode deside
  pinMode(trg, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(pump, OUTPUT);
}


void loop() {
//  temperature collect and display show function declare
  Temp();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp : ");
  lcd.setCursor(7, 0);
  lcd.print(tempval);
  
// rain value collect and auto window on off function
  Rain();

// water pump auto on off custom function
  Pump();

  ldrval = analogRead(ldr);
  Serial.println(ldrval);
}



//custom funtion section

//temperature custom function start
void Temp()
{
  tempdata = DHT.read22(temppin);
  tempval = DHT.temperature;
//  Serial.println(tempval);
  delay(1000);

if(tempval <= Vlow){
  digitalWrite(led[0], HIGH);
  digitalWrite(led[1], HIGH);
  digitalWrite(led[2], HIGH);
  digitalWrite(fan, LOW);
  
}
else if(tempval <= Low){
  digitalWrite(led[0], HIGH);
  digitalWrite(led[1], HIGH);
  digitalWrite(led[2], LOW);
  digitalWrite(fan, LOW);
  digitalWrite(fan2, LOW);
}
else if(tempval <= Min){
  digitalWrite(led[0], HIGH);
  digitalWrite(led[1], LOW);
  digitalWrite(led[2], LOW);
  digitalWrite(fan, LOW);
  digitalWrite(fan2, LOW);
}
else if(tempval < Max && tempval){
  digitalWrite(led[0], LOW);
  digitalWrite(led[0], LOW);
  digitalWrite(led[0], LOW);
  digitalWrite(fan, LOW);
  digitalWrite(fan2, LOW);
}
else if(tempval >= Max) {
  digitalWrite(led[0], LOW);
  digitalWrite(led[1], LOW);
  digitalWrite(led[2], LOW);
  digitalWrite(fan, HIGH);
}
else if(tempval >= high){
  digitalWrite(led[0], LOW);
  digitalWrite(led[1], LOW);
  digitalWrite(led[2], LOW);
  digitalWrite(led[0], LOW);
  digitalWrite(led[1], LOW);
  digitalWrite(led[2], LOW);
  digitalWrite(fan, HIGH);
  digitalWrite(fan2, HIGH);
}
  
}
// temperature custom funtion end


// rain detactive custom function start
void Rain()
{
  rainval = analogRead(A0);
  Serial.println(rainval);
  if(rainval <= 400){
    servo.write(180);
  }
  else {
    servo.write(0);
  }
}
// rain detactive custom function end


// water pump on off custom function start
void Pump()
{
  digitalWrite(trg, LOW);
  delayMicroseconds(2);
  digitalWrite(trg, HIGH);
  delayMicroseconds(10);
  digitalWrite(trg, LOW);
  duration = pulseIn(echo, HIGH);
  
  inc = duration * 0.0133 /2;
  cm = duration * 0.034 /2;
//  Serial.print(inc);
//  Serial.print(" Inc");
//  Serial.print(" ");
//  Serial.print(cm);
//  Serial.println(" Cm");
  
  if(inc <= 3){
    digitalWrite(pump, LOW);
  }
  else {
    digitalWrite(pump, HIGH);
  }
}
// water pump on off custom function end
