#define MAX_BUFFER_LENGTH 512
int sensorPin=A0;
int PWMPin=3;
int sample_rate=4000;
int mybuffer[MAX_BUFFER_LENGTH];
int buffer_tail=0;
int buffer_head=0;
void setup(){
  pinMode(13,OUTPUT);
    Serial.begin(115200);
    attachInterrupt(0,RunSample,RISING);//use pin 2 to interrupt
    tone(PWMPin,sample_rate);
}
void loop(){
  if(buffer_head==buffer_tail){
    digitalWrite(13,HIGH); //queue is empty, turn on LED to warn  
  }
  else{
    Serial.println(mybuffer[buffer_head]);
    buffer_head=(buffer_head+1)%MAX_BUFFER_LENGTH;
  }
    
}

void RunSample(){
   int sensorValue=analogRead(sensorPin);
   if((buffer_tail+1)%MAX_BUFFER_LENGTH==buffer_head){
      digitalWrite(13,HIGH); //turn LED on to warn overflow
   }
   else{
      //digitalwrite(13,LOW);
      mybuffer[buffer_tail]=sensorValue;//push into quene
      buffer_tail=(buffer_tail+1)%MAX_BUFFER_LENGTH;
    }
}
