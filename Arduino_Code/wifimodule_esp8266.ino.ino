#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "circuitbreakers";
const char* password = "android1234";
const int iopin = 2;
 
void setup () {
 
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  pinMode(iopin, INPUT); // setup  gpio2 pin as input
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..\n");
 
  }
  Serial.print("Connected..\n");
}
 
void loop() {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
     Serial.print("Entered loop() in connection state \n");
     HTTPClient http;  //Declare an object of class HTTPClient
     boolean val = digitalRead(iopin); // read value from io pin
     // update data to field 
    Serial.println("Sensor value:");    
    Serial.println(val);
     http.begin((String)"http://api.thingspeak.com/update?api_key=PBF2KIV4QP5CXZV3&field1=" + val);
    int httpCode = http.GET();                                                                  //Send the request
    Serial.println("HTTP CODE :");    
    Serial.print(httpCode);
    if (httpCode > 0) { //Check the returning code
      Serial.println("http code > 0");
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                  //Print the response payload    
    }
    http.end();   //Close connection
  }
  delay(15000);    //Send a request every 30 seconds
}
