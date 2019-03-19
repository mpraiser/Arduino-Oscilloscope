int sensorPin=A0;
void setup(){
    //initializeserialcommunicationat115200bitspersecondtomatchthatofthepythonscript
    Serial.begin(115200);
}
void loop(){
    int sensorValue=analogRead(sensorPin);
    Serial.println(sensorValue);
}
