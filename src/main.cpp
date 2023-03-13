#include <Arduino.h>
#include <Wifi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "env.h"
#define fan 
#define light 
void setup(){
Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.println("Connecting to wifi");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}
void loop(){
   if(WiFi.status()== WL_CONNECTED){
    Serial.println("");
    HTTPClient http;
float test=random((210,330)/10.0);
    http.begin(endpoint);
    http.addHeader("Content-type", "application/json");

    StaticJsonDocument<23> doc;
      String httpRequestData;

      // Serialise JSON object into a string to be sent to the API
      doc["temperature"] = test;
  
      // convert JSON document, doc, to string and copies it into httpRequestData
      serializeJson(doc, httpRequestData);


    // Send HTTP PUT request
    int httpResponseCode = http.PUT(httpRequestData);
    String http_response;

    // check reuslt of PUT request. negative response code means server wasn't reached
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      Serial.print("HTTP Response from server: ");
      http_response = http.getString();
      Serial.println(http_response);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }

    http.end();    



    http.begin(endpoint);
    httpResponseCode = http.GET();

    Serial.println("");
    Serial.println("");

    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        Serial.print("Response from server: ");
        http_response = http.getString();
        Serial.println(http_response);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
 
    StaticJsonDocument<1024> doc2;

    DeserializationError error = deserializeJson(doc2, http_response);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }
    
    bool temp = doc2["fan"]; 
    bool light= doc2["light"]; 

    digitalWrite(fan,temp);
    digitalWrite(light,light);
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}

    