

/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 */

#include <SPI.h>
#include <Ethernet.h>
#include <MySQL_Connection.h>
#include "DHT.h"
#include <DHT.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(178.62.119.85);
char user[] = "root";
char password[] = "12345678";  

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);
EthernetClient client;
MySQL_Connection conn((Client *)&client);
int buzzer_digital = 9;
int mq7_analogPin = A0;
int humi_digital = 2;

#define DHTPIN 2

#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  dht.begin();
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  pinMode(buzzer_digital, OUTPUT);
  pinMode(mq7_analogPin, INPUT);
  
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin

            client.println("<br />");
            
            float h = dht.readHumidity();
            // Reads temperature as Celsius
            float t = dht.readTemperature();
            
            int mq0_value;
            int mq7_value = analogRead(mq7_analogPin);
            
            if(mq0_value < 140){
              client.print("");
            }
            if(mq0_value > 140){
              client.print("<H1> Warning!!! Alcahol level high </H1>");
              noTone(9);
              delay(200);
              tone(9, 523, 300);
              delay(200);
            }
            else if(mq7_value > 140){
              client.print("<H1> Warning!!! CO level high </H1>");
            }
            client.println("<H1> Arduino </H1>");
            client.println("<br />Humidity level: ");
            client.print(h);
            client.println("<br />Temperature: ");
            client.print(t);
            client.println("<br />CO level: ");
            client.print(mq7_value);
            Serial.println(mq0_value);
            Serial.println(mq7_value);
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

