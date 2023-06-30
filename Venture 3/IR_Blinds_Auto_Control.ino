#include <IRremote.h>
const int RECV_PIN=11;
IRrecv irrecv(RECV_PIN);
decode_results results;
#define B1_HBrA 3
#define B1_HBrB 4
#define B2_HBrA 5
#define B2_HBrB 6
#define B3_HBrA 7
#define B3_HBrB 8
#define Indicate 12
#define Selector 2
void setup()
{
Serial.begin(9600);
pinMode(Selector,INPUT);
pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(Indicate,OUTPUT);
pinMode(B1_HBrA,OUTPUT);
pinMode(B1_HBrB,OUTPUT);
pinMode(B2_HBrA,OUTPUT);
pinMode(B2_HBrB,OUTPUT);
pinMode(B3_HBrA,OUTPUT);
pinMode(B3_HBrB,OUTPUT);
irrecv.enableIRIn();
irrecv.blink13(true);
}
void loop()
{
if(digitalRead(Selector)==HIGH){  
Serial.println("Manual Mode");
IRMan();}  
if(digitalRead(Selector)==LOW){
Serial.println("Auto Mode");
LDRoto();
}}
void IRMan(){
        if (irrecv.decode(&results)){ 
       irrecv.resume();
    if(results.value==0xFF6897){
      Serial.println("Blinds 1 open");
      digitalWrite(B1_HBrA,HIGH);
      digitalWrite(B1_HBrB,LOW);}
       if(results.value==0xFF30CF){
    Serial.println("Blinds 1 Closed");
     digitalWrite(B1_HBrA,LOW);
      digitalWrite(B1_HBrB,HIGH);}
if(results.value==0xFF9867){
    Serial.println("Blinds 2 Open");
     digitalWrite(B2_HBrA,HIGH);
      digitalWrite(B2_HBrB,LOW);}
  if(results.value==0xFF18E7){
    Serial.println("Blinds 2 Closed"); 
      digitalWrite(B2_HBrA,LOW);
      digitalWrite(B2_HBrB,HIGH);}
if(results.value==0xFFB04F){
    Serial.println("Blinds 3 Open");
      digitalWrite(B3_HBrA,HIGH);
      digitalWrite(B3_HBrB,LOW);}
    if(results.value==0xFF7A85){
      Serial.println("Blinds 3 Closed");
        digitalWrite(B3_HBrA,LOW);
      digitalWrite(B3_HBrB,HIGH);}}}      
void LDRoto(){
int AnVal1 = analogRead(A0);
int AnVal2 = analogRead(A1);
int AnVal3 = analogRead(A2);
AnVal1 = map(AnVal1,0,1023,0,255);
AnVal2 = map(AnVal2,0,1023,0,255);
AnVal3 = map(AnVal3,0,1023,0,255);
 if(AnVal1>=230){
  digitalWrite(Indicate,HIGH);}
 else {
  digitalWrite(Indicate,LOW) ;
 }
 Serial.print("___________________");
  Serial.println();
 Serial.print("LDR1:");
 Serial.print(AnVal1);
 Serial.println();
 Serial.print("LDR2:");
 Serial.print(AnVal2);
 Serial.println();
 Serial.print("LDR3:");
 Serial.print(AnVal3);
 Serial.println();
delay(1000);
if(AnVal1>=230 && AnVal2>=230  && AnVal3>=230){
  Serial.println("NIGHT");
   digitalWrite(B1_HBrA,HIGH);
      digitalWrite(B1_HBrB,LOW);
  digitalWrite(B2_HBrA,HIGH);
      digitalWrite(B2_HBrB,LOW);
      digitalWrite(B3_HBrA,HIGH);
      digitalWrite(B3_HBrB,LOW);} 
  else {
       Serial.println("DAY");
       digitalWrite(B1_HBrA,LOW);
      digitalWrite(B1_HBrB,HIGH);
     digitalWrite(B2_HBrA,LOW);
      digitalWrite(B2_HBrB,HIGH);   
        digitalWrite(B3_HBrA,LOW);
      digitalWrite(B3_HBrB,HIGH);}}
