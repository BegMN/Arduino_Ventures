#include <SoftwareSerial.h>   
SoftwareSerial SIM900(9, 8); // RX,TX 
char GSMData[100]="";
char extracted[100]="";
int Rel_One =2;
int Rel_Two =3;
int Rel_Three = 4;
int GSM_Pow = 7;
int Stat1 = 11;
int Stat2 = 12;
int Stat3 = 13;
void setup() {  
SIM900.begin(9600);
SIM900.println("AT+CNMI=2,2,0,0,0");
delay(500);
SIM900.println("AT+CMGF=1");  
Serial.begin(9600);
pinMode(Rel_One,OUTPUT);
pinMode(Rel_Two,OUTPUT);
pinMode(Rel_Three,OUTPUT);
pinMode(GSM_Pow,OUTPUT);
pinMode(Stat1,INPUT);
pinMode(Stat2,INPUT);
pinMode(Stat3,INPUT);

digitalWrite(GSM_Pow,HIGH);
delay(2000);
digitalWrite(GSM_Pow,LOW);
delay(800);

}
void loop() {
if(SIM900.available()>0){
    size_t byteCount = SIM900.readBytesUntil('\n',GSMData,sizeof(GSMData)-1);
    GSMData[byteCount] = NULL;
    Serial.println(GSMData);
char passcode[]="X257X";
char *passPointer = strstr(GSMData,passcode);
int Possy = passPointer - GSMData;
char extracted[20];
memset(extracted,0,sizeof(extracted));
strncpy(extracted,&GSMData[Possy+strlen(passcode)],sizeof(extracted));

char FilterDat[20];
memset(FilterDat,0,sizeof(FilterDat));
char *Qualifier = strchr(extracted,'<');
if (Qualifier != NULL) {
int hetjou = Qualifier - extracted;
strncpy(FilterDat,extracted,hetjou);
FilterDat[sizeof(FilterDat)]=NULL;
Serial.println(FilterDat);
 if(!(strncmp(FilterDat,"on_ONE",6))){
      digitalWrite(Rel_One,HIGH);
      //Serial.println("Switch 1 ON");
    }
       if(!(strncmp(FilterDat,"on_TWO",6))){
     // Serial.println("Switch 2 ON");
      digitalWrite(Rel_Two,HIGH);
       }
       if(!(strncmp(FilterDat,"on_THREE",8))){
        digitalWrite(Rel_Three,HIGH);
     // Serial.println("Switch 3 ON");
     }
       if(!strncmp(FilterDat,"off_ONE",7)){
        digitalWrite(Rel_One,LOW);
     // Serial.println("Switch 1 OFF");
     }
       if(!(strncmp(FilterDat,"off_TWO",7))){
      digitalWrite(Rel_Two,LOW);
    //  Serial.println("Switch 2 OFF");
    }
       if(!(strncmp(FilterDat,"off_THREE",8))){
      digitalWrite(Rel_Three,LOW);
     // Serial.println("Switch 3 OFF");
     }
  if(!(strncmp(FilterDat,"STATUS",6))){
    char regteNomm[20];
    memset(regteNomm,0,sizeof(regteNomm));
    strncpy(regteNomm,&FilterDat[6],sizeof(FilterDat));
   Serial.println(regteNomm);
boolean EEN = digitalRead(Stat1);
boolean TWEE = digitalRead(Stat2);
boolean DRIE = digitalRead(Stat3);
SIM900.println("AT+CMGF=1\r");
delay(200);
SIM900.print("AT+CMGS=\"");
SIM900.print(regteNomm);
SIM900.print("\"");
SIM900.println();
delay(200);
SIM900.println("SWICH1  "+String(EEN)+" SWICH2  "+String(TWEE)+"  SWICH3 "+String(DRIE));
SIM900.print("\r");
//SIM900.write(26);
SIM900.println((char)26); 
//SIM900.println();
delay(300);
    }}}}




