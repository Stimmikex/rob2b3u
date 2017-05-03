const int gasInn = 10;
const int gasOut = A3;

void setup() {
pinMode(gasInn, INPUT);
pinMode(gasOut, INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorReading = digitalRead(gasInn);
  int gasAnalogReading = analogRead(gasOut);
  Serial.println(sensorReading);
  delay(1000);
  Serial.println(gasAnalogReading);
  delay(1000);
  

}
