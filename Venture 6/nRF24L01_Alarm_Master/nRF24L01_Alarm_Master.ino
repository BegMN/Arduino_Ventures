#include <SPI.h>             
#include <RF24.h>
#include <Wire.h> 
#include <nRF24L01.h>
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
int Zone1 = 2;
int Zone2 = 3;
int Zone3 = 4;
int Zone4 = 5;
int AlmReset = 6;
int Alam  = 9;
int SpotA = 14;
int SpotB = 15;
int StatZ1;
int StatZ2;
int StatZ3;
int StatZ4;
int AlRess;
void setup(){
Wire.begin();
lcd.begin();
lcd.backlight();
digitalWrite(Alam,LOW);
lcd.print("nRF24 Master");
delay(3000);
lcd.clear();
radio.begin();
radio.openWritingPipe(addresses[1]);
radio.openReadingPipe(0, addresses[0]);
radio.setDataRate(RF24_250KBPS);
radio.setPALevel(RF24_PA_MAX);
pinMode(Zone1,INPUT);
pinMode(Zone2,INPUT);
pinMode(Zone3,INPUT);
pinMode(Zone4,INPUT);
pinMode(AlmReset,INPUT);
pinMode(Alam,OUTPUT);
pinMode(SpotA,OUTPUT);
pinMode(SpotB,OUTPUT);
 lcd.setCursor(5, 0);
 lcd.print("ARMED");
}
void loop(){ 
lcd.backlight();
 lcd.setCursor(0, 0);

 delay(5);
Vluister();
 Luister();
}
void Vluister(){
  StatZ1 = digitalRead(Zone1);
  if(StatZ1==HIGH){
    lcd.clear();
    digitalWrite(Alam,HIGH);
lcd.print("Alarm on Zone 1");
  radio.stopListening();
 const char text[] = "Alarm Zone 1";
 radio.write(&text,sizeof(text));
 delay(2000); 
    }
     StatZ2 = digitalRead(Zone2);
  if(StatZ2==HIGH){
    lcd.clear();
    digitalWrite(Alam,HIGH);
    lcd.print("Alarm on Zone 2");
    radio.stopListening();
 const char text[] = "Alarm Zone 2";
 radio.write(&text,sizeof(text));
 delay(2000); 
    }
     StatZ3 = digitalRead(Zone3);
  if(StatZ3==HIGH){
    lcd.clear();
    digitalWrite(Alam,HIGH);
    lcd.print("Alarm on Zone 3");
 radio.stopListening();
 const char text[] = "Alarm Zone 3";
 radio.write(&text,sizeof(text));
 delay(2000); 
    }
    
     StatZ4 = digitalRead(Zone4);
  if(StatZ4==HIGH){
    lcd.clear();
    digitalWrite(Alam,HIGH);
    lcd.print("Alarm on Zone 4");
   radio.stopListening();
 const char text[] = "Alarm Zone 4";
 radio.write(&text,sizeof(text));
 delay(2000); 
    }
     AlRess = digitalRead(AlmReset);
  if(AlRess==HIGH){
    lcd.clear();
    digitalWrite(Alam,LOW);
    lcd.print("Resetting...");
 radio.stopListening();
 const char text[] = "Alarm ARMED ";
 radio.write(&text,sizeof(text));
 delay(2000);
 lcd.clear();
 lcd.print("Alarm ARMED"); 
    }}
    
void Luister(){
    radio.startListening();
  char zext[32] = "";
  if (radio.available()) {
    radio.read(&zext,sizeof(zext));
 String RxData = String(zext);
    if (RxData == "SpotA") {
      digitalWrite(SpotA,HIGH);}
      if(RxData=="SpotB"){
         digitalWrite(SpotB,HIGH);} 
      
      if(RxData == "OFF"){
digitalWrite(SpotA,LOW);
digitalWrite(SpotB,LOW);}

    }}
