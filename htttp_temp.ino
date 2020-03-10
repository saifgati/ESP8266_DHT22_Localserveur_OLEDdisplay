const int refresh=2;//1 seconds
// DHT settings starts
#include "DHT.h"
#define DHTPIN 5     // what digital pin we're connected
#define LED 4
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);
float tValue;// 
float hValue;

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h"
#ifndef STASSID
#define STASSID "globalnet" // Your WiFi SSID
#define STAPSK  "00000000" //Your WiFi password
#endif
SSD1306  display(0x3C, D3, D5);
const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);






void setup(void) {

  display.init();

  // display.flipScreenVertically();

  display.setContrast(255);

  printBuffer0();
  delay(3000);
  display.clear();
  printBuffer01();
  delay(3000);
  display.clear();

  
  dht.begin();
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    uint8_t macAddr[6];
    WiFi.macAddress(macAddr);
    Serial.printf("Connected, mac address: %02x:%02x:%02x:%02x:%02x:%02x", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
  }  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("DHT")) {
    Serial.println("MDNS responder started");
  }
 
  

  server.on("/", sendTemp);
 
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");


}


 


void loop(void) {
  pinMode(LED, OUTPUT);
  // Robojax.com code for ESP8266 and DHT11 DHT22
  server.handleClient();
  MDNS.update();
  float c = dht.readTemperature();// Read temperature as Celsius (the default)
  float h = dht.readHumidity();// Reading humidity 
  float f = dht.readTemperature(true);// Read temperature as Fahrenheit (isFahrenheit = true)
  delay(250);
  String Hu=" %\t";
  String Tc=" *C";

  Serial.print("Humidity: "); 
  Serial.println(h+Hu);
  tValue =c;
  delay(250);
  Serial.print("Temperature: "); 
  Serial.println(c+Tc);
  hValue =h;
  delay(250);

  display.clear();
  display.setLogBuffer(2, 30);
  display.setFont(ArialMT_Plain_10);
  display.print("Humidity: ");
  display.print(hValue);
  display.println(" %\t");
  display.print("Temperature: "); 
  display.print(tValue);
  display.println(" *C");


    
    // Draw it to the internal screen buffer
    display.drawLogBuffer(0, 0);
    // Display it on the screen
    display.display();
    delay(4000);

    bool temp_state = true ;
    digitalWrite(LED, LOW);  // Turn the LED off by making the voltage HIGH
   

    if(tValue>=23){
    temp_state = false ;
   
    Serial.println("temperature issue") ;
    display.println(" temperature over limit");
  
    display.clear();
    printBuffer03();
    led();
   
    delay(2500);
    display.clear();
   
     
     }
   
}
