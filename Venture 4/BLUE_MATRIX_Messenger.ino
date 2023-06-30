#include <MD_MAX72xx.h>
#include <SPI.h>
#include <SoftwareSerial.h>
int bluetoothTx = 2;
int bluetoothRx = 3;
SoftwareSerial bluetooth(bluetoothTx,bluetoothRx);
#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define PRINT(s, x)
#define PRINTS(x)
#define PRINTD(x)
#define  MAX_DEVICES 5
#define CLK_PIN   6 
#define DATA_PIN  5 
#define CS_PIN    7  
int temp = 0;
int i = 0;
char str[32];
char inChar[32];
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
#define  DELAYTIME  100
void scrollText(char *p)
{
  uint8_t charWidth;
  uint8_t cBuf[32];  // this should be ok for all built-in fonts
  PRINTS("\nScrolling text");
  mx.clear();
  while (*p != '\n')
  {
    charWidth = mx.getChar(*p++, sizeof(cBuf) / sizeof(cBuf[0]), cBuf);
    for (uint8_t i = 0; i < charWidth + 1; i++) 
    {
      mx.transform(MD_MAX72XX::TSL);
      if (i < charWidth)
        mx.setColumn(0, cBuf[i]);
      delay(DELAYTIME);
    }}}
void(* resetFunc) (void) = 0;
void setup() {
  
  Serial.begin(9600);
  bluetooth.begin(9600);
  mx.begin();
  delay(5000);
  bluetooth.println("<System Ready>");
 }
void loop() {
  bluetoothMess();
  if (temp == 1)
  {
    check();
    temp = 0;
    i = 0;
  }
  scrollText(str);
  delay(1000);
}
void bluetoothMess()
{
  while (bluetooth.available())
  {
    if (bluetooth.find("["))
    {
      memset(str, 0, sizeof str);
      while (bluetooth.available())
      {
        char inChar = bluetooth.read();
        if (inChar == ']')
        {
          temp = 1;
          return;
        }
        else
          str[i++] = inChar;
      }}}}
void check()
{
Serial.println(str); 
bluetooth.println(str);
}
