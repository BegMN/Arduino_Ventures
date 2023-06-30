#include <SPI.h>             
#include <RF24.h>
#include <Wire.h> 
#include <nRF24L01.h>
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
int Spot1 = 2;
int Spot2 = 3;
int OutSpot = 4;
int Lite1;
int Lite2;
int LitesOUT;
void setup(){
Wire.begin();
lcd.begin();
lcd.backlight();
lcd.print("nRF24 Slave");
delay(3000);
lcd.clear();
radio.begin();
radio.openWritingPipe(addresses[0]);
radio.openReadingPipe(0, addresses[1]);
radio.setDataRate(RF24_250KBPS);
radio.setPALevel(RF24_PA_MAX);
pinMode(Spot1,INPUT);
pinMode(Spot2,INPUT);
pinMode(OutSpot,INPUT);
lcd.setCursor(5, 0);
 lcd.print("Ready");

}
void loop(){ 
lcd.backlight();
 lcd.setCursor(0, 0);
 delay(5);

 Checkoff();
 Switchies();
}
void Checkoff(){
radio.startListening();
  char zext[32] = "";
  if (radio.available()) {
    radio.read(&zext,sizeof(zext));
   lcd.clear();
    lcd.print(zext);}}

 void Switchies(){   
  Lite1 = digitalRead(Spot1);
  Lite2  = digitalRead(Spot2);
  LitesOUT = digitalRead(OutSpot);
  if(Lite1==HIGH){
    lcd.setCursor(0,1);
    lcd.print("Spotlight 1 ON");
    radio.stopListening();
 const char text[] = "SpotA";
 radio.write(&text,sizeof(text));
 delay(2000); }

if(Lite2==HIGH){
    lcd.setCursor(0,1);
    lcd.print("Spotlight 2 ON");
    radio.stopListening();
 const char text[] = "SpotB";
 radio.write(&text,sizeof(text));
 delay(2000); }
 if(LitesOUT==HIGH){
    lcd.clear();
    lcd.setCursor(0,1);
     
    lcd.print("Lites OFF");
    radio.stopListening();
 const char lext[] = "OFF";
 radio.write(&lext,sizeof(lext));
 delay(2000); 

 lcd.clear();
 lcd.print("   Ready  ");
  }}
