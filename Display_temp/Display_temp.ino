#include <OneWire.h>                 //Se importan las librerías
#include <DallasTemperature.h>
#define Pin 12                    //Se declara el pin donde se conectará la DATA
OneWire ourWire(Pin);                //Se establece el pin declarado como bus para la comunicación OneWire
DallasTemperature sensors(&ourWire); //Se llama a la librería DallasTemperature


float temp = 0;
long timeWait = 1000;
long timeCurrent = 0;


void setup() {
    Serial.begin(115200);
    
    pinMode(2, 1);
    pinMode(3, 1);
    pinMode(4, 1);
    pinMode(5, 1);
    pinMode(6, 1);
    pinMode(7, 1);
    pinMode(8, 1);
    pinMode(13, 1);
    pinMode(10, 1);
    digitalWrite(4,1);
    digitalWrite(5,1);
    digitalWrite(6,1);
    digitalWrite(7,1);
    digitalWrite(8,1);
    digitalWrite(13,1);
    digitalWrite(10,1);
    
}

void num_print_und(int num){
  digitalWrite(2,1);
  digitalWrite(3,0);
  switch(num){
    case 0:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,0);
     digitalWrite(13,1);
     digitalWrite(10,0);
     break;
    case 1:
     digitalWrite(4,1);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,1);
     digitalWrite(8,1);
     digitalWrite(13,1);
     digitalWrite(10,1);
     break;
    case 2:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,1);
     digitalWrite(7,0);
     digitalWrite(8,0);
     digitalWrite(13,0);
     digitalWrite(10,1);
     break;
    case 3:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,1);
     digitalWrite(13,0);
     digitalWrite(10,1);
     break;
    case 4:
     digitalWrite(4,1);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,1);
     digitalWrite(8,1);
     digitalWrite(13,0);
     digitalWrite(10,0);
     break;
    case 5:
     digitalWrite(4,0);
     digitalWrite(5,1);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,1);
     digitalWrite(13,0);
     digitalWrite(10,0);
     break;
    case 6:
     digitalWrite(4,0);
     digitalWrite(5,1);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,0);
     digitalWrite(13,0);
     digitalWrite(10,0);
     break;
    case 7:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,1);
     digitalWrite(8,1);
     digitalWrite(13,1);
     digitalWrite(10,1);
     break;
    case 8:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,0);
     digitalWrite(13,0);
     digitalWrite(10,0);
     break;
    case 9:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,1);
     digitalWrite(13,0);
     digitalWrite(10,0);
     break;
    
  }
}

void num_print_dec(int num){
  digitalWrite(2,0);
  digitalWrite(3,1);
  switch(num){
    case 0:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,0);
     digitalWrite(13,1);
     digitalWrite(10,0);
     break;
    case 1:
     digitalWrite(4,1);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,1);
     digitalWrite(8,1);
     digitalWrite(13,1);
     digitalWrite(10,1);
     break;
    case 2:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,1);
     digitalWrite(7,0);
     digitalWrite(8,0);
     digitalWrite(13,0);
     digitalWrite(10,1);
     break;
    case 3:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,1);
     digitalWrite(13,0);
     digitalWrite(10,1);
     break;
    case 4:
     digitalWrite(4,1);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,1);
     digitalWrite(8,1);
     digitalWrite(13,0);
     digitalWrite(10,0);
     break;
    case 5:
     digitalWrite(4,0);
     digitalWrite(5,1);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,1);
     digitalWrite(13,0);
     digitalWrite(10,0);
     break;
    case 6:
     digitalWrite(4,0);
     digitalWrite(5,1);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,0);
     digitalWrite(13,0);
     digitalWrite(10,0);
     break;
    case 7:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,1);
     digitalWrite(8,1);
     digitalWrite(13,1);
     digitalWrite(10,1);
     break;
    case 8:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,0);
     digitalWrite(13,0);
     digitalWrite(10,0);
     break;
    case 9:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,1);
     digitalWrite(13,0);
     digitalWrite(10,0);
     break;
    
  }
}


void loop() {
   
   if(millis() - timeCurrent > timeWait){
    timeCurrent = millis();
    //sensors.requestTemperatures();
    temp = random(20,35);
    //Serial.println(sensors.getTempCByIndex(0));
   }

   
  
   float des = temp/10;
   
   int dec = (int)des;
   
   float und = (des-(float)dec)*10;
   

   num_print_dec(dec);
   delay(3);
   num_print_und(und);
   delay(3);
  
}
