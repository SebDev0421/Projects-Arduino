int LAMP = 4;
float data1=7900;
int led = 5;
int up = 6;
int low = 7;


float prom = 0;

/*
void zeroDetector(){
  if(dim_val < 7800){
  int dimming_time = dim_val;
  delayMicroseconds(dimming_time);  
  digitalWrite(4, HIGH);
  digitalWrite(4, LOW);
  }else{
  digitalWrite(4, LOW);
  }
  }*/

void setup() {
  //attachInterrupt(digitalPinToInterrupt(2),zeroDetector,FALLING);
  Serial.begin(9600);
  pinMode(2,0);
  pinMode(4,1);
  pinMode(5,1);
  pinMode(up,0);
  pinMode( low , 0);
  digitalWrite(5,1);
  //tolerance 8.320ms
}


void loop() {
  int data=analogRead(A0);
  
  float data1 = map(data, 0, 1023,1500, 7900);
  /*
  if(digitalRead(up) == 1){
    if(data1 > 1500){
      data1 = data1 - 0.1;
    }
  }
  
  if(digitalRead(low) == 1){
    if(data1 < 7900){
      data1 = data1 + 0.1;
    }
  }
  */
  prom = data1/100;
  
  //Serial.println(data1);

  int dim_val = round(prom)*100;
  //int dim_val = data1;
  
  if(digitalRead(2) == 1){
    delayMicroseconds(dim_val);
    digitalWrite(4, HIGH);
    digitalWrite(4, LOW);
   }
  
  
  
  // put your main code here, to run repeatedly:

}
