/*******
 
 All the resources for this project:
 https://www.hackster.io/Aritro

*******/
int buzzer = 10;

void setup() {

  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  tone(buzzer, 1000, 200);
  delay(1000);
}
