#include "UbidotsMicroESP8266.h"
#define TOKEN  "osJnl2LQetypfRSPn8VnPx4XICE4qi"  // Put here your Ubidots TOKEN
#define WIFISSID "Hkst"
#define PASSWORD "1234abcd"
Ubidots client(TOKEN);
int redLed = 0;
int greenLed = 5;
int buzzer = 10;
int smokeA0 = A0;
// Our threshold value
int sensorThres = 450;

void setup() {
  //Serial.begin(115200);
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  client.add("smokeA0", analogSensor);
    client.sendAll(true);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
     Serial.print("red");
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);
  }
  else
  {
    Serial.print("green");
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
  }
  delay(500);
}
