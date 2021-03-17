
#define ON 11
#define CONTROL 12
#define SENSOR 13
#define  UPSET A0
#define  DOWNSET A1
#define  UPCAL A2
#define  DOWNCAL A3
#define HOT A4


float tempSet = 25;
long timeWait = 1000;
long timeCurrent = 0;


void setup() {
    Serial.begin(115200);

    pinMode(ON,1);
    pinMode(CONTROL,1);
    pinMode(SENSOR,1);

    pinMode(UPSET,0);
    pinMode(DOWNSET,0);
    pinMode(UPCAL,0);
    pinMode(DOWNCAL,0);
    
    pinMode(HOT,1);
    

    digitalWrite(ON,1);
    digitalWrite(CONTROL,1);
    digitalWrite(SENSOR,1);
    
    pinMode(2, 1);
    pinMode(3, 1);
    pinMode(4, 1);
    pinMode(5, 1);
    pinMode(6, 1);
    pinMode(7, 1);
    pinMode(8, 1);
    pinMode(9, 1);
    pinMode(10, 1);
    digitalWrite(4,1);
    digitalWrite(5,1);
    digitalWrite(6,1);
    digitalWrite(7,1);
    digitalWrite(8,1);
    digitalWrite(9,1);
    digitalWrite(10,1);
    
}

void num_print_und(int num){
  digitalWrite(2,0);
  digitalWrite(3,1);
  switch(num){
    case 0:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,0);
     digitalWrite(9,0);
     digitalWrite(10,1);
     break;
    case 1:
     digitalWrite(4,1);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,1);
     digitalWrite(8,1);
     digitalWrite(9,1);
     digitalWrite(10,1);
     break;
    case 2:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,1);
     digitalWrite(7,0);
     digitalWrite(8,0);
     digitalWrite(9,1);
     digitalWrite(10,0);
     break;
    case 3:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,1);
     digitalWrite(9,1);
     digitalWrite(10,0);
     break;
    case 4:
     digitalWrite(4,1);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,1);
     digitalWrite(8,1);
     digitalWrite(9,0);
     digitalWrite(10,0);
     break;
    case 5:
     digitalWrite(4,0);
     digitalWrite(5,1);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,1);
     digitalWrite(9,0);
     digitalWrite(10,0);
     break;
    case 6:
     digitalWrite(4,0);
     digitalWrite(5,1);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,0);
     digitalWrite(9,0);
     digitalWrite(10,0);
     break;
    case 7:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,1);
     digitalWrite(8,1);
     digitalWrite(9,1);
     digitalWrite(10,1);
     break;
    case 8:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,0);
     digitalWrite(9,0);
     digitalWrite(10,0);
     break;
    case 9:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,1);
     digitalWrite(9,0);
     digitalWrite(10,0);
     break;
    
  }
}

void num_print_dec(int num){
  digitalWrite(2,1);
  digitalWrite(3,0);
  switch(num){
    case 0:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,0);
     digitalWrite(9,0);
     digitalWrite(10,1);
     break;
    case 1:
     digitalWrite(4,1);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,1);
     digitalWrite(8,1);
     digitalWrite(9,1);
     digitalWrite(10,1);
     break;
    case 2:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,1);
     digitalWrite(7,0);
     digitalWrite(8,0);
     digitalWrite(9,1);
     digitalWrite(10,0);
     break;
    case 3:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,1);
     digitalWrite(9,1);
     digitalWrite(10,0);
     break;
    case 4:
     digitalWrite(4,1);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,1);
     digitalWrite(8,1);
     digitalWrite(9,0);
     digitalWrite(10,0);
     break;
    case 5:
     digitalWrite(4,0);
     digitalWrite(5,1);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,1);
     digitalWrite(9,0);
     digitalWrite(10,0);
     break;
    case 6:
     digitalWrite(4,0);
     digitalWrite(5,1);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,0);
     digitalWrite(9,0);
     digitalWrite(10,0);
     break;
    case 7:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,1);
     digitalWrite(8,1);
     digitalWrite(9,1);
     digitalWrite(10,1);
     break;
    case 8:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,0);
     digitalWrite(9,0);
     digitalWrite(10,0);
     break;
    case 9:
     digitalWrite(4,0);
     digitalWrite(5,0);
     digitalWrite(6,0);
     digitalWrite(7,0);
     digitalWrite(8,1);
     digitalWrite(9,0);
     digitalWrite(10,0);
     break;
    
  }
}


void loop() {

   if(digitalRead(UPSET) == 1){
    delay(50);
    if(tempSet < 99){
      tempSet ++; 
     }
   }

   if(digitalRead(DOWNSET) == 1){
    delay(50);
    if(tempSet > 00){
      tempSet --; 
     }
   }

   
  
   float des = tempSet/10;
   
   int dec = (int)des;
   
   float und = (des-(float)dec)*10;
   

   num_print_dec(dec);
   delay(2);
   num_print_und(und);
   delay(2);
  
}
