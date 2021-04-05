#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFiMulti.h>
#include "DHTesp.h"

// Stands for dumb humitity and temperature
DHTesp dht;

const int DOC_SIZE = 1024;  
const char* ssid = "Apt2R";
const char* password = "3uv8qjjwh637";
const String SENSOR_ID = "steve";


const int GPIO_OUT = 5;
const int GPIO_D_IN = 4;
const int GPIO_A_IN = A0;


const String GET_DELAY_ENPOINT = "http://192.168.1.100/sensors/config/" + SENSOR_ID + "/sleep_timer";

const char* INFLUX_WRITE_ENDPOINT = "http://influx.kube.norwood.baki.es/api/v2/write?bucket=sensors&org=admin";

void setup () {
 
    Serial.begin(115200);
 
    connectToWifi();
    Serial.println("setup");


    pinMode(GPIO_OUT, OUTPUT);
    pinMode(GPIO_D_IN, INPUT);
    pinMode(2, OUTPUT);
    dht.setup(14, DHTesp::DHT11);
    //pinMode(GPIO_A_IN, INPUT);
}

void loop() {
  digitalWrite(GPIO_OUT, HIGH);
  digitalWrite(2, HIGH);
  delay(5000);


  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    
    
    writeMoistnessToInflux();

    writeTemperatureAndHumanitytoInflux();

    // TODO check for 0 default delay

    //delay(getDelayFromServer());
   
  }else {
     Serial.print("Jon sucks");
  }
  Serial.println("loop");

  
  
  digitalWrite(GPIO_OUT, LOW);
  digitalWrite(2, LOW);


}


void writeTemperatureAndHumanitytoInflux(){
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

   HTTPClient http;
   http.begin(INFLUX_WRITE_ENDPOINT);
   http.addHeader("Authorization", "Token 20QwvH85H1Mjiau5XUSeAx0NCUbCm25MH2S8ASt0eqa57r83VLCnf_hL1o8MqN3H6IVEFOVw0dYnIvUNPWNf3g==");
    
    //doc = generateJson(getSensorData());
    Serial.printf("Sending request to %s\n", INFLUX_WRITE_ENDPOINT);
    String postData = "Ambiance,sensorId=" + SENSOR_ID + " temp=" + String(dht.toFahrenheit(temperature)) + ",humidity=" + String(humidity) + ",heatIndex=" + dht.computeHeatIndex(dht.toFahrenheit(temperature), humidity, true);
    Serial.println(postData);
    int httpCode = http.POST(postData);
    //Check the returning code
    if (httpCode > 0) {
      //Get the request response payload
      String payload = http.getString();
      //Print the response payload
      //TODO deserialize
      Serial.println(payload);
    }else{
      Serial.println("mitch sucks");
    }
}

long getDelayFromServer(){

   HTTPClient http;
   http.begin(GET_DELAY_ENPOINT);
  int httpCode = http.GET();
  //Check the returning code
    if (httpCode > 0) {
      //Get the request response payload
      long payload = http.getString().toInt();
      //Print the response payload
      //TODO deserialize
      Serial.println(payload);
      return payload;
    }else{
      Serial.println("mitch sucks");
    }
}
void writeMoistnessToInflux(){

    HTTPClient http;
    http.begin(INFLUX_WRITE_ENDPOINT);
    http.addHeader("Authorization", "Token 20QwvH85H1Mjiau5XUSeAx0NCUbCm25MH2S8ASt0eqa57r83VLCnf_hL1o8MqN3H6IVEFOVw0dYnIvUNPWNf3g==");
    
    //doc = generateJson(getSensorData());
    Serial.printf("Sending request to %s\n", INFLUX_WRITE_ENDPOINT);
    String postData = "Moisture,sensorId=" + SENSOR_ID + " analog=" + String(analogRead(GPIO_A_IN)) + ",digital=" + String(digitalRead(GPIO_D_IN));
    Serial.println(postData);
    int httpCode = http.POST(postData);
    //Check the returning code
    if (httpCode > 0) {
      //Get the request response payload
      String payload = http.getString();
      //Print the response payload
      //TODO deserialize
      Serial.println(payload);
    }else{
      Serial.println("mitch sucks");
    }
}
/*
void loop() {

  HTTPClient http;

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    
    http.begin(SENSOR_ENDPOINT);
    http.addHeader("Content-Type", "application/json");
    DynamicJsonDocument doc(DOC_SIZE);
    
    doc = generateJson(getSensorData());
    Serial.printf("Sending request to %s\n", SENSOR_ENDPOINT);
    int httpCode = http.POST(doc.as<String>());

    //Check the returning code
    if (httpCode > 0) {
      //Get the request response payload
      String payload = http.getString();
      //Print the response payload
      //TODO deserialize
      Serial.println(payload);
    }else{
      Serial.println("mitch sucks");
    }
   
  }else {
     Serial.print("Jon sucks");
  }
  delay(30000);    //Send a request every 30 seconds
}



DynamicJsonDocument generateJson(String sensorData) {

  DynamicJsonDocument  doc(DOC_SIZE);

  doc["sensor_id"] = SENSOR_ID;
  doc["data"] = sensorData;
  serializeJsonPretty(doc, Serial);

  return doc;
  
}
*/                                                               
void connectToWifi(){

    WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
     Serial.print("Connecting..");
     delay(1000);
  }
  Serial.print("Connected");
      
}
