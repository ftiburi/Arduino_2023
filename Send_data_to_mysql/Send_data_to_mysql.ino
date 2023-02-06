


#include <WiFi.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
//#include "DHT.h"
//#define DHTPIN 22
///#define DHTTYPE DHT11
//DHT dht(DHTPIN, DHTTYPE);

const char* ssid     = "Fabio Oi Fibra";
const char* password = "10010110";
const char* host = "localhost";

int sensorPin = 34;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int valorAnalogica = 0;  // variable to store the value coming from the sensor


void setup()
{
  
    Serial.begin(115200);
   // Serial.println("DHT11 Output!");
    //dht.begin();
     pinMode(ledPin, OUTPUT); 
    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}



void loop()
{
  //Serial.print("connecting to ");
  //Serial.println(host);

// read the value from the sensor:
  valorAnalogica = analogRead(sensorPin);
 Serial.println(valorAnalogica);
  // turn the ledPin on
  digitalWrite(ledPin, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(valorAnalogica);
  // turn the ledPin off:
  digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  delay(valorAnalogica);


void enviaDados() {
sprintf(query, INSERT_SQL, 1, creditoInserido);
  // Initiate the query class instance
/MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Execute the query
 cur_mem->execute(query);
  // Note: since there are no results, we do not need to read any data
  // Deleting the cursor also frees up memory used
delete cur_mem;
Serial.println("Informações Enviadas");
}

    // Use WiFiClient class to create TCP connections
   /// WiFiClient client;
   // const int httpPort = 5555;
   // if (!client.connect(host, httpPort)) {
   //     Serial.println("connection failed");
   //     return;

            // This will send the request to the server
//client.print(String("GET http://wamp64\www\IOT_ptoject/connect.php?") + ("&valorAnalogica=") + (" HTTP/1.1\r\n") +
//                 "Host: " + host + "\r\n" +
 //                "Connection: close\r\n\r\n");
 //   unsigned long timeout = millis();
//    while (client.available() == 0) {
 //       if (millis() - timeout > 1000) {
 //           Serial.println(">>> Client Timeout !");
 //           client.stop();
 //           return;
//        }
  //  }

    // Read all the lines of the reply from server and print them to Serial
   // while(client.available()) {
   //     String line = client.readStringUntil('\r');
   //     Serial.print(line);
        
  //  }

   // Serial.println();
   // Serial.println("closing connection");

    
 }

  
  /*  
//float temperature = dht.readTemperature();
int 
//  float humidity = dht.readHumidity();  
//  if(isnan(temperature) || isnan(humidity)){
 //   Serial.println("Failed to read DHT11");
//  }else{
////    Serial.print("Humidity: ");
 //   Serial.print(humidity);
 //   Serial.print(" %\t");
 //   Serial.print("Temperature: ");
//    Serial.print(temperature);
//    Serial.println(" *C");
//    delay(3000);
//  }
   
    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 5555;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

 


    // This will send the request to the server
client.print(String("GET http://your_hostname/iot_project/connect.php?") + 
                         ("&temperature=") + 100 +
                         ("&humidity=") + 100 +
                          " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 1000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
        
    }

    Serial.println();
    Serial.println("closing connection");

    */

}