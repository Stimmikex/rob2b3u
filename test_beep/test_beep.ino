#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

#include <DHT.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 



/*******
 
 All the resources for this project:
 https://www.hackster.io/Aritro

*******/
int buzzer = 9;
int smokeA0 = A0;
int humi = 2;

#define DHTPIN 2

#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.setCursor(0,1);
  lcd.print("No Gas Leaking");
  
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  lcd.display();
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
