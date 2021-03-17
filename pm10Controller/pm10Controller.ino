#include <LiquidCrystal.h>

#define START 2
#define RUN 4
#define ENTER 3
#define MENU 5 
#define LCD_LIGHT 6
#define RESET 7
#define UP A0
#define DOWN A1

#define time_counter 1000

//const int rs = 8, en = 9, d4 = 10, d5 = 11 , d6 = 12 , d7 = 13; 

const int rs = 13, en = 12, d4 = 11, d5 = 10 , d6 = 9 , d7 = 8;


int period_enable = 1000;
unsigned long timeElapse_enable = 0;




int indexDays = 0; //15 list mode possible
int indexMemoryOnDays = 0;
int indexMemoryOffDays = 0;
int mode_day_on = 0; // out range array
int hourOn = 0; //desbording hour for mcu can't make begin
int minuteOn = 0; //desbording
bool enable_on = false;

bool resDayOn = false;
bool resHourOn = false;

bool resDayOff = false;
bool resHourOff = false;

int mode_day_off = 0; // 15 list mode possible
int hourOff = 0; //desbording hour for mcu can't make begin
int minuteOff = 0;
bool enable_off = false;

bool flag_option_auto = false;
bool enable_day_select  = false;
bool enable_hour_select  = false;

bool enable_auto = false;


const String daysOptions[7] = {"L","M","MI","J","V","S","D"};
String OptionsMenu[8] = {"Hora","Dia","prender auto","apagar auto","Habilitar",""};

const String daySetup[15] = {"L","M","M", "J", "V", "S", "D", "L M M J V", "S D", "L M M J V S","L M M", "J V S","L Mi V","M J V","L M M J V S D"}; // days setup



LiquidCrystal lcd(rs,en,d4,d5,d6,d7);


int hour = 0;
int minutes = 0;
int seconds = 0;

int clockHour = 23;
int clockMinutes = 59;
int clockSeconds = 0;

bool setHour = false;
bool setDay = false;
int setOn = 0;
int setOff = 0;

bool reset_cnf = false;

bool flagMenu = false;

int flagOptions = 0;

long timeRunning = 0;
long timeRunningAux = 0;

int timeMonitoring = 24;

bool statusStart = false;

String hourPrint = "";
String minutesPrint = "";
String secondsPrint = "";

String clockHourPrint = "";
String clockMinutesPrint = "";
 

void setup() {
  lcd.begin(16,2);
  lcd.setCursor(5,0);
  lcd.print("Tish");
  lcd.setCursor(2,2);
  lcd.print("Enviromental");
  delay(2000);
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Tish");
  lcd.setCursor(1,2);
  lcd.print("PM 10 Control");
  delay(2000);
  lcd.clear();
  Serial.begin(9600);
  pinMode(START,INPUT);
  pinMode(RUN,OUTPUT);
  pinMode(MENU,INPUT);
  pinMode(RESET,INPUT);
  lcd.setCursor(0,0);
  lcd.print("Tiempo:0");
  lcd.setCursor(0,2);
  lcd.print("H: 00:00 D: L");
}

bool pointerSecond = false;

void menuAuto(){
  
  if(flag_option_auto){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Progr dias");
    lcd.setCursor(0,1);
    lcd.print("*Progr Hora");
  }else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("*Progr dias");
    lcd.setCursor(0,1);
    lcd.print("Progr Hora");
  }
  
  
}

void dayOnSetup(){
  //Days setup for On Pump
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("progr dias:");
  lcd.setCursor(0,1);
  if(indexMemoryOnDays > 14){
    indexMemoryOnDays = 0;
  }
  lcd.print(daySetup[indexMemoryOnDays]);
  
}

void dayOffSetup(){
  //Days setup for On Pump
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("progr dias:");
  lcd.setCursor(0,1);
  if(indexMemoryOffDays > 14){
    indexMemoryOffDays = 0;
  }
  lcd.print(daySetup[indexMemoryOffDays]); 
}

void hourOnSetup(){
  //Days setup for On Pump
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("progr hora on:");
  lcd.setCursor(0,1);

  if(hourOn > 23){
    hourOn = 0;
  }

  if(minuteOn > 59){

  minuteOn = 0;
  
  }
  
  String hourTo = String(hourOn);
  String minuteTo = String(minuteOn);
  if(hourOn < 10){
    hourTo = "0"+hourTo;
  }

  if(minuteOn < 10){
    minuteTo = "0"+minuteTo; 
  }
  
  String showClock = hourTo+":"+minuteTo;
  lcd.print(showClock);
}

void hourOffSetup(){
  //Days setup for On Pump
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("progr hora off:");
  lcd.setCursor(0,1);

  if(hourOff > 23){
    hourOff = 0;
  }

  if(minuteOff > 59){

  minuteOff = 0;
  
  }
  
  String hourTo = String(hourOff);
  String minuteTo = String(minuteOff);
  if(hourOff < 10){
    hourTo = "0"+hourTo;
  }

  if(minuteOff < 10){
    minuteTo = "0"+minuteTo; 
  }
  
  String showClock = hourTo+":"+minuteTo;
  lcd.print(showClock);
}


void mode_daysOn(){
  Serial.print("mode day on: ");
  Serial.println(mode_day_on);
  switch(mode_day_on){
    case 0:
           //const String daysOptions[7] = {"L","M","MI","J","V","S","D"};
           //const String daySetup[15] = {"L","M","M", "J", "V", "S", "D", "L M M J V", "S D", "L M M J V S","L M M", "J V S","L Mi V","M J V","L M M J V S D"}; // days setup
           if(daysOptions[indexDays] == "L"){
             resDayOn = true;
             resDayOff = false;
           }
           break;
     case 1:
           if(daysOptions[indexDays] == "M"){
             resDayOn = true;
             resDayOff = false;
           }
           break;
     case 2:
           if(daysOptions[indexDays] == "MI"){
             resDayOn = true;
             resDayOff = false;
           }
           break;
     case 3:
           if(daysOptions[indexDays] == "J"){
             resDayOn = true;
             resDayOff = false;
           }
           break; 
     case 4:
           if(daysOptions[indexDays] == "V"){
             resDayOn = true;
             resDayOff = false;
           }
           break;
     case 5:
           if(daysOptions[indexDays] == "S"){
             resDayOn = true;
             resDayOff = false;
           }
           break;
     case 6:
           if(daysOptions[indexDays] == "D"){
             resDayOn = true;
             resDayOff = false;
           }
           break;
      case 7:
           if(daysOptions[indexDays] == "L" || daysOptions[indexDays] == "M" || daysOptions[indexDays] == "MI" || daysOptions[indexDays] == "J" || daysOptions[indexDays] == "V" ){
             resDayOn = true;
             resDayOff = false;
           }
           break;
      case 8:
           if(daysOptions[indexDays] == "S" || daysOptions[indexDays] == "D"){
             resDayOn = true;
             resDayOff = false;
           }
           break;
      case 9:
           if(daysOptions[indexDays] == "L" || daysOptions[indexDays] == "M" || daysOptions[indexDays] == "MI" || daysOptions[indexDays] == "J" || daysOptions[indexDays] == "V" || daysOptions[indexDays] == "S" ){
             resDayOn = true;
             resDayOff = false;
           }
           break; 
      case 10:
           if(daysOptions[indexDays] == "L" || daysOptions[indexDays] == "M" || daysOptions[indexDays] == "MI" ){
             resDayOn = true;
             resDayOff = false;
           }
           break;
      case 11:
           if(daysOptions[indexDays] == "J" || daysOptions[indexDays] == "V" || daysOptions[indexDays] == "S" ){
             resDayOn = true;
             resDayOff = false;
           }
           break;
      case 12:
           if(daysOptions[indexDays] == "L" || daysOptions[indexDays] == "MI" || daysOptions[indexDays] == "V"){ // falta viernes
             resDayOn = true;
             resDayOff = false;
           }
           break;
      case 13:
           if(daysOptions[indexDays] == "MI" || daysOptions[indexDays] == "J" || daysOptions[indexDays] == "V"){
             resDayOn = true;
             resDayOff = false;
           }
           break;
      case 14:
           if(daysOptions[indexDays] == "L" || daysOptions[indexDays] == "M" || daysOptions[indexDays] == "MI" || daysOptions[indexDays] == "J" || daysOptions[indexDays] == "V" || daysOptions[indexDays] == "S" || daysOptions[indexDays] == "D" ){       
             resDayOn = true;
             resDayOff = false;
           }
           break;
  }
}

void hourOnStart(){
  Serial.print("hour on: ");
  Serial.print(hourOn);
  Serial.print(":");
  Serial.println(minuteOn);
  if(hourOn == clockHour && minuteOn == clockMinutes){
    resHourOn = true;      
  }
}

void mode_daysOff(){
  Serial.print("mode day off: ");
  Serial.println(mode_day_off);
  switch(mode_day_off){
    case 0:
           //const String daysOptions[7] = {"L","M","MI","J","V","S","D"};
           //const String daySetup[15] = {"L","M","M", "J", "V", "S", "D", "L M M J V", "S D", "L M M J V S","L M M", "J V S","L Mi V","M J V","L M M J V S D"}; // days setup
           if(daysOptions[indexDays] == "L"){
             
             resDayOff = true;
             
           }
           break;
     case 1:
           if(daysOptions[indexDays] == "M"){
             resDayOff = true;
           }
           break;
     case 2:
           if(daysOptions[indexDays] == "MI"){
             resDayOff = true;
           }
           break;
     case 3:
           if(daysOptions[indexDays] == "J"){
             resDayOff = true;
           }
           break; 
     case 4:
           if(daysOptions[indexDays] == "V"){
             resDayOff = true;
           }
           break;
     case 5:
           if(daysOptions[indexDays] == "S"){
             resDayOff = true;
           }
           break;
     case 6:
           if(daysOptions[indexDays] == "D"){
             resDayOff = true;
           }
           break;
      case 7:
           if(daysOptions[indexDays] == "L" || daysOptions[indexDays] == "M" || daysOptions[indexDays] == "MI" || daysOptions[indexDays] == "J" || daysOptions[indexDays] == "V" ){
             resDayOff = true;
           }
           break;
      case 8:
           if(daysOptions[indexDays] == "S" || daysOptions[indexDays] == "D"){
             resDayOff = true;
           }
           break;
      case 9:
           if(daysOptions[indexDays] == "L" || daysOptions[indexDays] == "M" || daysOptions[indexDays] == "MI" || daysOptions[indexDays] == "J" || daysOptions[indexDays] == "V" || daysOptions[indexDays] == "S" ){
             resDayOn = false;
           }
           break; 
      case 10:
           if(daysOptions[indexDays] == "L" || daysOptions[indexDays] == "M" || daysOptions[indexDays] == "MI" ){
             resDayOff = true;
           }
           break;
      case 11:
           if(daysOptions[indexDays] == "J" || daysOptions[indexDays] == "V" || daysOptions[indexDays] == "S" ){
             resDayOff = true;
           }
           break;
      case 12:
           if(daysOptions[indexDays] == "L" || daysOptions[indexDays] == "MI" || daysOptions[indexDays] == "V"){ // falta viernes
             resDayOff = true;
           }
           break;
      case 13:
           if(daysOptions[indexDays] == "MI" || daysOptions[indexDays] == "J" || daysOptions[indexDays] == "V"){
             resDayOff = true;
           }
           break;
      case 14:
           if(daysOptions[indexDays] == "L" || daysOptions[indexDays] == "M" || daysOptions[indexDays] == "MI" || daysOptions[indexDays] == "J" || daysOptions[indexDays] == "V" || daysOptions[indexDays] == "S" || daysOptions[indexDays] == "D" ){       
             resDayOff = true;
           }
           break;
  }
}

void hourOffStart(){
  Serial.print("hour off: ");
  Serial.print(hourOff);
  Serial.print(":");
  Serial.println(minuteOff);
  if(hourOff == clockHour && minuteOff == clockMinutes){
    resHourOn = false;
  }

}


void clockShow(){

  pointerSecond = !pointerSecond;
  
  

  if(clockMinutes < 10){
    clockMinutesPrint = "0"+String(clockMinutes);
  }
  else{
    clockMinutesPrint = String(clockMinutes);
  }
  if(clockHour < 10){
    clockHourPrint = "0"+String(clockHour);
  }
  else{
    clockHourPrint = String(clockHour);
  }
  if (clockSeconds > 59)
  {
    clockSeconds = 0;
    clockMinutes++;
    if(enable_auto){
        mode_daysOn();
        hourOnStart();
        
        mode_daysOff();
        hourOffStart();

        Serial.println(resDayOn && resHourOn);
        
        if(resDayOn && resHourOn ){
           statusStart = true;
           digitalWrite(RUN,statusStart);
         }
         else if(resDayOff && resHourOn == false){
           statusStart = false;
           digitalWrite(RUN,statusStart);
         }
         else{
          statusStart = false;
          digitalWrite(RUN,statusStart);
          }
        }
  }

  if(clockMinutes > 59){
    clockMinutes = 0;
    clockHour ++;
    
  }

  if(clockHour > 23){
    clockHour = 0;
    indexDays ++;
    if(indexDays > 6){
      indexDays = 0;
    }
    
  }

  String clockTimeSet = clockHourPrint+" "+clockMinutesPrint;
  if(flagMenu == false){
    lcd.setCursor(3,1);
    lcd.print(clockTimeSet);
    if(flagMenu == false){
      lcd.setCursor(12,1);
      lcd.print(daysOptions[indexDays]);
    }
  if(pointerSecond){
    lcd.setCursor(5,1);
    lcd.print(":");
  }else{
    lcd.setCursor(5,1);
    lcd.print(" ");
  }
  }

  Serial.println("test clock"); 
  
  }

void daySet(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Conf dia");
  lcd.setCursor(0,1);
  lcd.print("Dia: ");
  lcd.setCursor(5,1);
  if(indexDays > 6){
    indexDays = 0;
   }
  lcd.print(daysOptions[indexDays]);
}

void hourSet(){

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Conf reloj");
  lcd.setCursor(1,0);
  pointerSecond = !pointerSecond;
  
  

  if(clockMinutes < 10){
    clockMinutesPrint = "0"+String(clockMinutes);
  }
  else{
    clockMinutesPrint = String(clockMinutes);
  }
  if(clockHour < 10){
    clockHourPrint = "0"+String(clockHour);
  }
  else{
    clockHourPrint = String(clockHour);
  }
  if (clockSeconds > 59)
  {
    clockSeconds = 0;
    clockMinutes++;
  }

  if(clockMinutes > 59){
    clockMinutes = 0;
    clockHour ++;
    
  }

  if(clockHour > 23){
    clockHour = 0;
  }

  String clockTimeSet = clockHourPrint+" "+clockMinutesPrint;
  lcd.setCursor(3,1);
  lcd.print(clockTimeSet); 
  lcd.setCursor(5,1);
  lcd.print(":");
  //toggle hour
  //clockHour = 
  
  }

bool pointSecond = false;

void menu(String option1,String option2, int pointerPos){

  if(pointerPos == 1){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("*"+option1);
    lcd.setCursor(0,1);
    lcd.print(option2);
  }else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(option1);
    lcd.setCursor(0,1);
    lcd.print("*"+option2);
  }
}

long minutesAux = 0;

void time_elapsep(){
  if(seconds < 10){
    secondsPrint = "0"+String(seconds);
  }
  else{
    secondsPrint = String(seconds);
  }
  if(minutes < 10){
    minutesPrint = "0"+String(minutes);
  }
  else{
    minutesPrint = String(minutes);
  }
  if(hour < 10){
    hourPrint = "0"+String(hour);
  }
  else{
    hourPrint = String(hour);
  }
  if (seconds > 59)
  {
    seconds = 0;
    minutes++;
    minutesAux = minutes;
  }

  if(minutes > 59){
    minutes = 0;
    hour ++;
  }

  String timeSet = hourPrint+":"+minutesPrint+":"+secondsPrint;
  Serial.println(timeSet);
  if(flagMenu == false){
    lcd.setCursor(7,0);
    lcd.print(String(minutesAux));
    lcd.setCursor(15,0);
    pointSecond = !pointSecond;
    if(pointSecond){
       lcd.print(".");
      }else{
         lcd.print(" ");
      }
    
  }
  
}



void loop() {

  timeRunning = millis() - timeRunningAux;
  if(timeRunning > 1000){
    if(statusStart){
      time_elapsep();
      seconds++;
    }
      clockShow();
      clockSeconds++;
      
      timeRunningAux = millis();
   }  
  
  if(digitalRead(START)){
    delay(300);
    
    statusStart = !statusStart;
    digitalWrite(RUN,statusStart);
    OptionsMenu[4] = "Habilitar";
    enable_auto = false;
  }
  
  if(digitalRead(RESET)){
    reset_cnf = true;
    delay(400);
  }

  if(digitalRead(MENU)){
    delay(300);
    flagMenu = !flagMenu;
    setHour = false;
    setDay = false;
    enable_day_select = false;
    flag_option_auto = false;
    setOn = 0;
    setOff = 0;
    flagOptions = 0;
    if(flagMenu){
      menu("Hora","Dia",1);
    }
    else{
     lcd.clear(); 
     lcd.setCursor(0,0);
     lcd.print("Tiempo: ");
     lcd.setCursor(0,2);
     lcd.print("H: 00:00 D: L");
     time_elapsep();
    }
  }

  if(digitalRead(DOWN) && flagMenu && setHour == false && setDay == false && setOn == 0 && setOff == 0 && enable_day_select == false && enable_hour_select == false){
    delay(300);
    flagOptions++;
    if(flagOptions > 4){
      flagOptions = 0;
      }
    int auxFlagOptions = flagOptions+1;
    Serial.println(flagOptions);
    lcd.clear();
    menu(OptionsMenu[flagOptions],OptionsMenu[auxFlagOptions],1);
    
  }
  else if(digitalRead(DOWN) && flagMenu && setHour && setDay == false && setOn == 0  && setOff == 0  && enable_day_select == false && enable_hour_select == false){
    delay(300);
    clockHour++;
    hourSet();
  }
  else if(digitalRead(DOWN) && flagMenu && setHour == false && setDay && setOn == 0  && setOff == 0 && enable_day_select == false && enable_hour_select == false){
    delay(300);
    indexDays++;
    daySet();
  }
  else if(digitalRead(DOWN) && flagMenu && setHour == false && setDay == false && (setOn == 1  || setOff == 1) && enable_day_select == false && enable_hour_select == false){
   delay(250);
   flag_option_auto = !flag_option_auto;
   menuAuto();
  }

  else if(digitalRead(DOWN) && flagMenu && setHour == false && setDay == false && setOn == 1  && setOff == 0 && enable_day_select == true && enable_hour_select == false){
   delay(250);
   indexMemoryOnDays++;
   dayOnSetup();
  }

  else if(digitalRead(DOWN) && flagMenu && setHour == false && setDay == false && setOn == 0  && setOff == 1 && enable_day_select == true && enable_hour_select == false){
   delay(250);
   Serial.println("push off day");
   indexMemoryOffDays++;
   dayOffSetup();
  }

  else if(digitalRead(DOWN) && flagMenu && setHour == false && setDay == false && setOn == 1  && setOff == 0 && enable_day_select == false && enable_hour_select == true){
   delay(250);
   hourOn++;
   hourOnSetup();
  }
  else if(digitalRead(DOWN) && flagMenu && setHour == false && setDay == false && setOn == 0  && setOff == 1 && enable_day_select == false && enable_hour_select == true){
   delay(250);
   hourOff++;
   hourOffSetup();
  }
  

  

  if(digitalRead(UP) && flagMenu && setHour && setDay == false && setOn == 0  && setOff == 0 && enable_day_select == false && enable_hour_select == false){
    delay(300);
    clockMinutes++;
    hourSet();
  }
  else if(digitalRead(UP) && flagMenu && setHour == false && setDay == false && setOn == 1  && setOff == 0 && enable_day_select == false && enable_hour_select == true){
   delay(250);
   minuteOn ++;
   hourOnSetup();
  }
  else if(digitalRead(UP) && flagMenu && setHour == false && setDay == false && setOn == 0  && setOff == 1 && enable_day_select == false && enable_hour_select == true){
   delay(250);
   minuteOff ++;
   hourOffSetup();
  }

  
  if(reset_cnf){
    seconds = 0;
    minutes = 0;
    hour = 0;
    time_elapsep();
    reset_cnf = false;
  }

  


  if(digitalRead(ENTER) && flagMenu && setOn == 0 && setOff == 0 && enable_day_select == false && enable_hour_select == false){
      delay(250);
      switch(flagOptions){
        case 0: setHour = true;
                hourSet();
                break;
        case 1: setDay = true;  
                daySet();
                break;
        case 2: setOff = 0;
                setOn = 1;
                menuAuto();
                flag_option_auto = false;
                //dayOnSetup();
                break;
        case 3: setOn = 0;
                setOff = 1;
                menuAuto();
                flag_option_auto = false;
                //dayOffSetup();
                break;
        case 4: //enable auto
                if(statusStart == false){
                enable_auto = !enable_auto;
                if(enable_auto){
                  OptionsMenu[4] = "Desabilitar";
                }else{
                  OptionsMenu[4] = "Habilitar";
                }
                int auxFlagOptions = flagOptions+1;
                lcd.clear();
                menu(OptionsMenu[flagOptions],OptionsMenu[auxFlagOptions],1);
                Serial.println("push enable");
                }
                break;
                
      }
      
  }

  else if(digitalRead(ENTER) && flagMenu && (setOn == 1 || setOff == 1) && enable_day_select == false && enable_hour_select == false){
      delay(250);
      
      switch(flag_option_auto){
        case false:
                enable_day_select = true;
                enable_hour_select = false;
                if(setOn == 1){
                  dayOnSetup();
                  }
                 if(setOff == 1){
                  dayOffSetup();
                  
                  }
                break;
        case true: 
                 enable_day_select = false;
                 enable_hour_select = true;
                 if(setOn == 1){
                  hourOnSetup();
                  }
                 if(setOff == 1){
                  hourOffSetup();
                  }
                break;
      }
      
  }

  // auto on save

  else if(digitalRead(ENTER) && flagMenu && setOn == 1 && setOff == 0  && enable_day_select && enable_hour_select == false){
      delay(250);
      enable_day_select = false;

      mode_day_on = indexMemoryOnDays;

      menuAuto();
      
      Serial.print("save: ");
      Serial.println(daySetup[indexMemoryOnDays]);
      Serial.print("Mode: ");
      Serial.println(mode_day_on);
      
  }

  else if(digitalRead(ENTER) && flagMenu && setOn == 1 && setOff == 0 && enable_day_select == false && enable_hour_select ){
    delay(250);
    enable_hour_select = false;
    
    menuAuto();
      
    Serial.print("save hour ");
    Serial.println();
  }

  // auto off save
  else if(digitalRead(ENTER) && flagMenu && setOn == 0 && setOff == 1  && enable_day_select && enable_hour_select == false){
      delay(250);
      enable_day_select = false;

      mode_day_off = indexMemoryOffDays;

      menuAuto();
      
      Serial.print("save: ");
      Serial.println(daySetup[indexMemoryOffDays]);
      Serial.print("Mode: ");
      Serial.println(mode_day_on);
      
  }

  else if(digitalRead(ENTER) && flagMenu && setOn == 0 && setOff == 1 && enable_day_select == false && enable_hour_select ){
    delay(250);
    enable_hour_select = false;
    
    menuAuto();
      
    Serial.print("save hour");
  }

  

  
}
