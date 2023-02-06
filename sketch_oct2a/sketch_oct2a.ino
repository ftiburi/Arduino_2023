int led = 2;
int ou = 12;
void setup() {
  // put your setup code here, to run once:
 pinMode(led, OUTPUT);
 pinMode(ou,OUTPUT);
 Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(led, LOW);
digitalWrite(ou, HIGH);
//Serial.print("WElcome to IOT Denvelopment...");
delay(1000);

digitalWrite(led, HIGH);
digitalWrite(ou, LOW);
//Serial.println("with ESP32");
delay(1000);
}
