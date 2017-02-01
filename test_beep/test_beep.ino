#include <DHT.h>


/*******
 
 All the resources for this project:
 https://www.hackster.io/Aritro

*******/
int buzzer = 10;
int smokeA0 = A0;
int humi = 2;

#define DHTPIN 2

#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  // MQ-7 sensor
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  int MQ = analogRead(smokeA0);
  /*if(MQ > 500) {
     tone(buzzer, 1000, 200);
     delay(1000);
  }*/

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");
  Serial.println(MQ);
  
  delay(2000);
}
