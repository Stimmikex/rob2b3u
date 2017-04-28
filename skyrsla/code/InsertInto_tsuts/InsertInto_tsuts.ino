/*
  Strymir Oli Thorsteinsson
  26/04/2017
  Hita- og gasmaelir.
*/
#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include "DHT.h"
#include <DHT.h>

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server_addr(10,200,10,24);  // IP of the MySQL *server* here
char user[] = "2509972569";              // MySQL user login username
char password[] = "mypassword";

// Sample query
char INSERT_SQL[] = "INSERT INTO 2509972569_robtest.arduino (temp, humi, mq7) VALUES (%d, %d, %d)";


// Sensors
int buzzer_digital = 9;
int mq7_analogPin = A0;
int humi_digital = 2;

#define DHTPIN 2

#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

EthernetClient client;
MySQL_Connection conn((Client *)&client);

char query[128];

void setup() {
  Serial.begin(9600);
  while (!Serial); // wait for serial port to connect
  Ethernet.begin(mac_addr);
  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
  }
  else
    Serial.println("Connection failed.");
}


void loop() {
  delay(120000);

  int h = dht.readHumidity();
  // Reads temperature as Celsius
  int t = dht.readTemperature();
  
  int mq7_value = analogRead(mq7_analogPin);
  Serial.println(t);
  Serial.println(h);
  Serial.println(mq7_value);

  Serial.println("Recording data.");

  // Initiate the query class instance
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);

  sprintf(query, INSERT_SQL, t, h, mq7_value);
  Serial.println(query);
  
  // Execute the query
  cur_mem->execute(query);
  // Note: since there are no results, we do not need to read any data
  // Deleting the cursor also frees up memory used
  delete cur_mem;
}
