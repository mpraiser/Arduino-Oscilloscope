#define MAX_BUFFER_LENGTH 600
int sensorPin=A0;
int PWMPin=3;
int sample_rate=4000;
unsigned char mybuffer[MAX_BUFFER_LENGTH];
int buffer_tail=0;
int buffer_head=0;
void setup(){
  setP16();
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  Serial.begin(230400);
  attachInterrupt(0,RunSample,RISING);//use pin 2 to interrupt
  tone(PWMPin,sample_rate);
}
void loop(){
  if(buffer_head==buffer_tail){
    //digitalWrite(LED_BUILTIN,HIGH); //queue is empty, turn on LED to warn  
  }
  else{
    Serial.write(mybuffer[buffer_head]);
    buffer_head=(buffer_head+1)%MAX_BUFFER_LENGTH;
    digitalWrite(LED_BUILTIN,LOW);
  }
    
}

void RunSample(){
   int sensorValue=analogRead(sensorPin);
   if((buffer_tail+1)%MAX_BUFFER_LENGTH==buffer_head){
      digitalWrite(LED_BUILTIN,HIGH); //turn LED on to warn overflow
   }
   else{
      //digitalwrite(13,LOW);
      mybuffer[buffer_tail]=sensorValue>>2;//push into quene
      buffer_tail=(buffer_tail+1)%MAX_BUFFER_LENGTH;
      digitalWrite(LED_BUILTIN,LOW);
    }
}

void setP32( ) {
  Serial.println("ADC Prescaler = 32");  // 101
  ADCSRA |=  (1 << ADPS2);  // 1
  ADCSRA &=  ~(1 << ADPS1);  // 0
  ADCSRA |=  (1 << ADPS0);  // 1
}
void setP16( ) {
  Serial.println("ADC Prescaler = 16");  // 100
  ADCSRA |=  (1 << ADPS2);  // 1
  ADCSRA &=  ~(1 << ADPS1);  // 0
  ADCSRA &=  ~(1 << ADPS0);  // 0
}
void setP8( ) {  // prescaler = 8
  Serial.println("ADC Prescaler = 8");  // 011
  ADCSRA &=  ~(1 << ADPS2);  // 0
  ADCSRA |=  (1 << ADPS1);  // 1
  ADCSRA |=  (1 << ADPS0);  // 1
}
void setP4( ) {  // prescaler = 4
  Serial.println("ADC Prescaler = 4");  // 010
  ADCSRA &=  ~(1 << ADPS2);  // 0
  ADCSRA |=  (1 << ADPS1);  // 1
  ADCSRA &=  ~(1 << ADPS0);  // 0
}
void setP128( ) { // default value 128
  Serial.println("ADC Prescaler = 128");  // 111
  ADCSRA |=  (1 << ADPS2);  // 1
  ADCSRA |=  (1 << ADPS1);  // 1
  ADCSRA |=  (1 << ADPS0);  // 1
} // setP128
