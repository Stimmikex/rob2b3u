#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress server_ip(178,62,119,85);

char user[] = "root";
char password[] = "12345678";

char INSERT_SQL[] = "INSERT INTO Sensor (temp) VALUES (2.2)";

EthernetClient client;
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(9600);
  while (!Serial);
    Ethernet.begin(mac);
    Serial.println("Connecting");
  if (conn.connect(server_ip, 3306, user, password)) {
    delay(1000);
  }
  else
    Serial.println("Connection failed.");

}

void loop() {
  delay(2000);

  Serial.println("Recording data.");

  // Initiate the query class instance
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Execute the query
  cur_mem->execute(INSERT_SQL);
  // Note: since there are no results, we do not need to read any data
  // Deleting the cursor also frees up memory used
  delete cur_mem;

}
