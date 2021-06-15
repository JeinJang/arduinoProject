#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
int trigPin = D1;
int echoPin = D2;
int piezoPin = D3;
int threshold_low = 90;
int threshold_high = 150;
int indicator = 0;
int count = 0;

#ifndef APSSID
#define APSSID "Meacha_choigochoigo"
#endif

ESP8266WebServer server(80);
/* Set these to your desired credentials. */
//const char *ssid = APSSID;
const char* ssid = "AndroidHotspot0410";//"yourNetworkName";
const char* password = "doraemon@snu99";

float measureDistance(){
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  
  return (pulseIn(echoPin, HIGH)*17)/100;
}

float dist = measureDistance();

String getpage() {
  String page = "<html><head><meta http-equiv=\"refresh\" content=\"1\">\n</head><body>";
  page += "<ul><li>dist : ";
  page += String(dist);
  page += "</li></ul></body></html>";
  return page;
}

void handleRoot(){
  server.send(200, "text/html", getpage());  
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(piezoPin, OUTPUT);
  delay(1000);
  WiFi.softAP(ssid, password);
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  /* button intake */
  if(dist > threshold_high){
    if(indicator){
      tone(piezoPin, 349);
      delay(500);
      noTone(piezoPin);
      count++;
      indicator--;
    }
  }
  if(dist < threshold_low){
    indicator = 1;
  }
  Serial.println(count);
  server.handleClient();
}
