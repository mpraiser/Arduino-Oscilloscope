int sensorPin=A0;
void setup(){
    Serial.begin(115200);
}
void loop(){
    int sensorValue=analogRead(sensorPin);
    Serial.println(sensorValue);
}
