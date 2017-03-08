// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

//#include "DHT.h"
#include <Ethernet.h>
#include <SPI.h>
#define DHTPIN 9  
#define DHTTYPE DHT22   // DHT 22  (AM2302)

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x2A, 0x8D };
byte ip[] = { 10, 220, 216, 76 };
byte gw[] = {10,220,216,1};
byte subnet[] = { 255, 255, 255, 0 };

EthernetClient client;//(server, 80);

byte server[] = { 10, 200, 10, 24  }; // Server IP
float h =0.0;
float t =0.0;
int mq7_analogPin = A0;

//DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac, ip, gw, gw, subnet);
  delay(1000);
  //dht.begin();
}

void loop() {
  
  //float h = dht.readHumidity();
  //float t = dht.readTemperature();
  int mq7_value = analogRead(mq7_analogPin);
  delay(5000);
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    senddata(h,t,mq7_value );
  }
}
void senddata(float h, float t,int mq7_value )
{

Serial.println();
Serial.println("ATE :)");
delay(10000);                                    //Keeps the connection from freezing

if (client.connect(server, 80)) {
Serial.println("Connected");
client.print("GET /hopar/rob/add.php?data=");
client.print(h);
client.print("&data2=");
client.print(t);
client.print("&data3=");
client.print(mq7_value );
client.println(" HTTP/1.1");
client.println("Host: 10.200.10.24");
client.println("Connection: close");
client.println();
Serial.println();
while(client.connected()) {
  while(client.available()) {
    Serial.write(client.read());
    }
   }
}

else
{
Serial.println("Connection unsuccesful");
}
//}
 //stop client
 client.stop();
 while(client.status() != 0)
{
  delay(5);
}
}
