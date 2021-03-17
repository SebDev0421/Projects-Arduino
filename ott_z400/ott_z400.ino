
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <ArduinoJson.h>

#define clockUp 100
#define START_STOP A1
#define UP A2 
#define DOWN A3
#define ENTER A4
#define ON_OFF 7
#define BUZZER A0



const int rs = 13, en = 12, d4 = 11, d5 = 10 , d6 = 9 , d7 = 8;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

long timeOnMemory = 0;
float timePulsesMemory = 0;
int pulsesMemory = 0;
float n = 0;

long currentTime = 0;
long currentOnTime  =  0;
bool start = false;
long countPulses = 0;
long countPulsesAux = 0;
bool flagStart = true;
bool flagOn = false;
bool startCount = false;


float timeLcd = 0.0;
float timeLcdAux = 0.0;

void readSensor(){
  if(flagStart){
   countPulses ++;
  }
  
}


void countTime(){
  if(millis()-currentTime >= clockUp){
    currentTime = millis();
    timeLcd += 0.1;
    String printLcd = String(timeLcd) + " s"; 
    
    lcd.setCursor(0,1);
    lcd.print(printLcd);
    printLcd = "  "+String(countPulses) + ".0 p   "; 
    lcd.setCursor(7,1);
    lcd.print(printLcd);
    currentOnTime = millis();
   }

   
   
}

void buzzer(){
  digitalWrite(BUZZER,1);
  delay(100);
  digitalWrite(BUZZER,0);
}


void lcd_on(){
  digitalWrite(ON_OFF,1);
  delay(1000);
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("OTT Z400");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("0.0 s  00.0 p");
  
  
}

void lcd_off(){
  digitalWrite(ON_OFF,0);
}

void setup() {

  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2),readSensor,RISING);
  pinMode(START_STOP, 0);
  pinMode(UP, 0);
  pinMode(DOWN, 0);
  pinMode(ENTER, 0);
  pinMode(BUZZER , 1);
  pinMode(ON_OFF, 1);
  Serial.println("Begin system .. ");
  
  timeOnMemory = EEPROM[0x01];
  timePulsesMemory = EEPROM[0x02];
  pulsesMemory = EEPROM[0x03];
  
  
  
  Serial.println(timeOnMemory);
  Serial.println(timePulsesMemory);
  Serial.println(pulsesMemory);
  
  
  //lcd_on();
  
}

void calculatedVel(){

  float vel = (((float)countPulsesAux/timeLcdAux)/(16.3915));
  String velStr = String(vel,3)+" m/s  # 1";
  Serial.println(countPulsesAux);
  Serial.println(timeLcdAux);
  Serial.println(vel);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(velStr);
  
 }

String pollSerial = "";

DynamicJsonDocument doc(1024);

void loop() {

  if(Serial.available()){
    pollSerial = Serial.readString();
    //Serial.println(pollSerial.substring(0,1));
    
    if(pollSerial == "reset\n"){

    EEPROM[0x01] = 0;
    EEPROM[0x02] = 0;
    EEPROM[0x03] = 0;

    timeOnMemory = EEPROM[0x01];
    timePulsesMemory = EEPROM[0x02];
    pulsesMemory = EEPROM[0x03];
    
    Serial.println("System was reset");
   }

   if(pollSerial.substring(0,1) == "{"){
    deserializeJson(doc,pollSerial);
    const char* timeOnGet = doc["on"];
    String timePulsesGet = doc["tPulses"];
    const char* pulsesMemoryGet = doc["pulsesSize"];

    EEPROM[0x01] = atol(timeOnGet);
    EEPROM[0x02] = timePulsesGet.toFloat();
    EEPROM[0x03] = atol(pulsesMemoryGet);

    timeOnMemory = EEPROM[0x01];
    timePulsesMemory = EEPROM[0x02];
    pulsesMemory = EEPROM[0x03];

    buzzer();
    buzzer();
    Serial.println("12");
    pollSerial = "";
   }

   

   
   }

  
  if(timeOnMemory > 0){
  
  if(millis() - currentOnTime >= timeOnMemory){
    currentOnTime = millis();
    lcd_off();
    flagOn = false;
  }
  }
  

  if(digitalRead(START_STOP)){
    buzzer();
    delay(200);
    currentOnTime = millis();
    if(!flagOn){
      digitalWrite(ON_OFF, 1);
      flagOn = true;
      lcd_on();
      buzzer();
    }else{
      timeLcdAux = timeLcd;
      if(timeLcdAux > 0){

         flagStart = false;
         countPulsesAux = countPulses;
         countPulses = 0;
         timeLcd = 0;
         delay(200);
         calculatedVel();
         
       }
       else{
        flagStart = true;
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("0.0 s  00.0 p");
       }
    }
    
  }

  /*if(digitalRead(ENTER)){
    delay(200);
    buzzer();
  }*/

  if(pulsesMemory > 0){
    if(pulsesMemory == countPulses){
       flagStart = false;
       countPulsesAux = countPulses;
       countPulses = 0;
       timeLcd = 0;
       delay(200);
       calculatedVel();
      }
  }

  if(timePulsesMemory > 0){
    
    if(timeLcd >= timePulsesMemory){
       timeLcdAux = timeLcd;
       flagStart = false;
       countPulsesAux = countPulses;
       countPulses = 0;
       timeLcd = 0;
       delay(200);
       calculatedVel();
      }
  }

  if(flagStart && flagOn){
    if(countPulses > 0){
      countTime();
     }
  }
  
}
