#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

#define pulse_in 2
#define pulse_out 3
#define mode 10

double pulse ;
double frequency ;
double inductance ;
double capacitance;
double induct = 0.0098 ;
double cap = 0.000000098 ;

void setup()
{
  Wire.begin();
  lcd.begin();
  lcd.backlight();
  delay(100);
  pinMode(pulse_in , INPUT);
  pinMode(pulse_out , OUTPUT);
  pinMode(mode, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("Use Toggle Swtch");
  delay(200);
  lcd.setCursor(0, 1);
  lcd.print("To Measure XL/XC");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("--Both Buttons--");
  lcd.setCursor(0, 1);
  lcd.print("Same Direction");
  delay(3000);
  lcd.clear();
}

void lcd_milli()
{
  lcd.setCursor(0, 0);
  lcd.print("INDUCTANCE VALUE");
  lcd.setCursor(5 , 1);
  lcd.print ((inductance / 1000));
  lcd.print ("mH" );
  delay(500);
  lcd.clear();
}

void lcd_micro()
{
  lcd.setCursor(0, 0);
  lcd.print("INDUCTANCE VALUE");
  lcd.setCursor(5 , 1);
  lcd.print (inductance);
  lcd.print ("uH" );
  delay(500);
  lcd.clear();
}

void lcd_niks()
{
  lcd.setCursor(0, 0);
  lcd.print("INDUCTANCE VALUE");
  lcd.setCursor(0, 1);
  lcd.print("insert Inductor");
}

void lcd_microf()
{
  lcd.setCursor(0, 0);
  lcd.print("CAPACITANCE VAL:");
  lcd.setCursor(5 , 1);
  lcd.print ((capacitance/1000));
  lcd.print ("uF" );
  delay(500);
  lcd.clear();
}

void lcd_nanof()
{
  lcd.setCursor(0, 0);
  lcd.print("CAPACITANCE VAL:");
  lcd.setCursor(5 , 1);
  lcd.print (capacitance);
  lcd.print ("nF" );
  delay(500);
  lcd.clear();
}

void lcd_niksf()
{
  lcd.setCursor(0, 0);
  lcd.print("CAPACITANCE VAL:");
  lcd.setCursor(0, 1);
  lcd.print("insert CAP");
}
void ind_meter()
{
  digitalWrite(pulse_out, HIGH);
  delay(5);
  digitalWrite(pulse_out, LOW);
  delayMicroseconds(100);

  pulse = pulseIn(pulse_in, HIGH, 5000);

  if (pulse > 0.1)
  {
    frequency = 1.E6 / (2 * pulse) ;
    inductance = 1. / (4 * cap * pow(frequency , 2 ) * pow(3.14159 , 2));
    inductance *= 1.0E6;
    if (inductance >= 1000)
    {
      lcd_milli();
    }
    else
    {
      lcd_micro();
    }
  }
  else if (pulse < 0.1)
  {
    lcd_niks();
  }
}
void cap_meter()
{
  digitalWrite(pulse_out, HIGH);
  delay(5);
  digitalWrite(pulse_out, LOW);
  delayMicroseconds(100);

  pulse = pulseIn(pulse_in, HIGH, 5000);


  if (pulse > 0.1)
  {
    frequency = 1.E6 / (2 * pulse) ;
    capacitance = 1. / (4 * induct * pow(frequency , 2 ) * pow(3.14159 , 2));
    capacitance *= 1.0E9;
    if (capacitance >= 1000)
    {
      lcd_microf();
    }
    else
    {
      lcd_nanof();
    }
  }
  else if (pulse < 0.1)
  {
    lcd_niksf();
  }
}

void loop()
{
  if (digitalRead(mode) == LOW)
  {
    ind_meter();
  }
  else {
    cap_meter();
  }
}
