/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

byte mac_addr[] = { 0x00, 0x13, 0xEF, 0xF4, 0x23, 0xCD };

IPAddress server_addr(10,0,1,35);  // IP of the MySQL *server* here
char user[] = "root";              // MySQL user login username
char password[] = "secret";        // MySQL user login password

// Sample query
char INSERT_SQL[] = "INSERT INTO test_arduino.hello_arduino (message) VALUES ('Hello, Arduino!')";

EthernetClient client;
MySQL_Connection conn((Client *)&client);

const int ledPin =  13;
const int ledPin2 =  2;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect
  Ethernet.begin(mac_addr);
  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
  }
  else
    Serial.println("Connection failed.");
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(ledPin, HIGH);
  digitalWrite(ledPin2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(ledPin, LOW);
  digitalWrite(ledPin2, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second

  Serial.println("Recording data.");

  // Initiate the query class instance
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Execute the query
  cur_mem->execute(INSERT_SQL);
  // Note: since there are no results, we do not need to read any data
  // Deleting the cursor also frees up memory used
  delete cur_mem;


}
