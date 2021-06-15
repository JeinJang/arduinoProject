#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

int trigPin = D1;
int echoPin = D2;
int piezoPin = D3;

float measureDistance(){
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  
  return (pulseIn(echoPin, HIGH)*17)/100;
}
 
const char* ssid = "pushoong";//"yourNetworkName";
const char* password = "poomang!";//"yourNetworkPassword";
 
void setup() {
 
  Serial.begin(9600);
  delay(1000);   //Delay needed before calling the WiFi.begin
 
  WiFi.begin(ssid, password);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(piezoPin, OUTPUT); 
 
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
}
 
void loop() {
 float dist = measureDistance();
 
 
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
   HTTPClient http;   
 
   http.begin("http://jsonplaceholder.typicode.com/posts");  //Specify destination for HTTP request
   http.addHeader("Content-Type", "text/plain");             //Specify content-type header
 
   int httpResponseCode = http.POST("{\"value\":\""+ String(dist)+"\"}");   //Send the actual POST request
 
   if(httpResponseCode>0){
 
    String response = http.getString();                       //Get the response to the request
 
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
 
   }else{
 
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
 
   }
 
   http.end();  //Free resources
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(100);
 
}
