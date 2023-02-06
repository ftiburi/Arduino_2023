#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <MySQL_Encrypt_Sha1.h>
#include <MySQL_Packet.h>

// INCLUSÃO DE BIBLIOTECAS
#include <SPI.h>
#include <WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

#include "arduino_secrets.h"

// DEFINIÇÕES
#define pinNoteiro 8
#define esperaLeitura 500 // TIME OUT DA LEITURA
#define FINALIZADA true

// DECLARAÇÃO DE VARIÁVEIS GLOBAIS
bool sinalNoteiro = HIGH;
bool sinalNoteiroAnt = HIGH;
int creditoInserido = 0;
unsigned long controleLeitura = 0;

// DECLARAÇÃO DE VARIÁVEIS PARA WIFI
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;        // your network password
int status = WL_IDLE_STATUS;      // status

// DECLARAÇÃO DE VARIÁVEIS PARA MySQL
IPAddress server_addr(85, 10, 205, 173);  // IP of the MySQL *server* here
char user[] = SECRET_USERDB;              // MySQL user login username
char password[] = SECRET_PASSDB;          // MySQL user login password

char INSERT_SQL[] = "INSERT INTO bcitest.Noteiro (DEVICE_ID, CASH) VALUES ('%d', '%d')";
char query[128];

// INSTANCIANDO OBJETOS
WiFiClient client;
MySQL_Connection conn((Client *)&client);

// DECLARAÇÃO DE FUNÇÕES
void conectaWifi();
void enviaDados();
void leituraNoteiro();

// ***************** INÍCIO DO SETUP *************************
void setup()
{
    Serial.begin(115200);

    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");

  //Init WiFi as Station, start SmartConfig
  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig();

  //Wait for SmartConfig packet from mobile
  Serial.println("Waiting for SmartConfig.");
  while (!WiFi.smartConfigDone()) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("SmartConfig received.");

  //Wait for WiFi to connect to AP
  Serial.println("Waiting for WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }


  Serial.println("WiFi Connected.");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
{
  conectaWifi();

  // CONECTA NO MySQL

  while (!conn.connect(server_addr, 3306, user, password)) {
    Serial.println("Conexão SQL falhou.");
    conn.close();
    delay(1000);
    Serial.println("Conectando SQL novamente.");
  }
  Serial.println("Conectado ao servidor SQL.");
 // digitalWrite(LED_BUILTIN, HIGH);
  
  attachInterrupt(digitalPinToInterrupt(pinNoteiro), leituraNoteiro, RISING);

// ***************** FIM DO SETUP ***************************

// ***************** INÍCIO DO LOOP *************************
void loop() {

  if( ((millis() - controleLeitura) > esperaLeitura) && (creditoInserido > 0) ){
    Serial.print("Enviando credito inserido: ");
    Serial.println(creditoInserido);
    enviaDados();
    creditoInserido = 0;
  }
  delay(10);
}
// ***************** FIM DO LOOP ***************************

void conectaWifi() {
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }
}
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
}

void enviaDados() {
  sprintf(query, INSERT_SQL, 1, creditoInserido);
  // Initiate the query class instance
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Execute the query
  cur_mem->execute(query);
  // Note: since there are no results, we do not need to read any data
  // Deleting the cursor also frees up memory used
  delete cur_mem;
  Serial.println("Informações Enviadas");
}

void leituraNoteiro() {
  creditoInserido++;
  controleLeitura = millis();
}
