#include "SevenSeg.h"
#include <DS3231.h>
SevenSeg disp (13,12,11,10,9,8,7);
const int numOfDigits =4;			
int digitPins [numOfDigits]={3,4,5,6};	
DS3231  rtc(A4, A5);				
Time t;									
const int VeranderK = A0;	
const int HuurK = A1;	
const int MinuK   = A2;
const int WysMy   = A3;
int hour;
int min;
String clock;
int number;
int count=0;
unsigned long cc=0;
void setup() {
	pinMode(VeranderK, INPUT_PULLUP);
	pinMode(HuurK, INPUT_PULLUP);
	pinMode(MinuK, INPUT_PULLUP);
  pinMode(WysMy,OUTPUT);
  rtc.begin();
  disp.setDigitPins ( numOfDigits , digitPins );
  disp.setCommonAnode();
  disp.setDutyCycle(70);
}
void loop()
{	
disp.write(clock);
digitalWrite(WysMy,LOW);
if ((hour<=9) && (min>9)){
clock = '0' + String(hour) + String(min);
}
else if ((min<=9) && (hour>9)){
clock = String(hour) + '0' + String(min);
}
else if ((hour<=9) && (min<=9)){
clock = '0' + String(hour) + '0' + String(min);
}
else{
clock = String(hour) + String(min);
}
number = clock.toInt();	
   if (digitalRead(VeranderK) == LOW){
		delay(300);
		count++;
		if (count>7){
			count=0;
		} }
  if (count==3){  
	if (digitalRead(HuurK) == LOW){
		delay(300);
			if (hour>22){
				hour=0;
			}
			else{
				hour++;
			}
   rtc.setTime(hour, min, 0);
	}
      if (digitalRead(MinuK) == LOW){ 
        delay(300);
			if (min>58){
				min=0;
			}
			else{
				min++;
			}   }
      rtc.setTime(hour, min, 0);  
		}
 else{
	t = rtc.getTime();
	hour = t.hour;
	min = t.min;
 }}
