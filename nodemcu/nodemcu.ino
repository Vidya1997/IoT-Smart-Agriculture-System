//#include <BearSSLHelpers.h>
//#include <CertStoreBearSSL.h>
//#include <ESP8266WiFi.h>
//#include <ArduinoJson.h>
/*#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiGratuitous.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>*/

//#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WiFiServer.h>
//#include <WiFiUdp.h>

#include <ESP8266WiFi.h>
#include "DHT.h"
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


#define DHTPIN D4
#define DHTTYPE DHT11 

const char* ssid     = "Uma";
const char* password = "Uma123*!";
const char* host = "agrosmartz.000webhostapp.com/";
String mq2="";
String mq135="";
String pir="";
DHT dht(DHTPIN, DHTTYPE);
IPAddress ip(192,168,18,5);
IPAddress gateway(192,168,18,5);
IPAddress subnet(255,255,255,0);
#define LED D3
void setup() {
  pinMode(LED, OUTPUT);  
  
  Serial.begin(115200);
  delay(5000);
  dht.begin();
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.config(ip,gateway,subnet);
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print("*");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
}
void loop() {
  Serial.println();
  Serial.println();
  Serial.println("");

  int digitalSensor2=digitalRead(D8);
  Serial.print("Air Sensor : ");
  Serial.println((digitalRead(D8)));
  Serial.print("");
  Serial.print("PIR Sensor : ");
  Serial.println(digitalRead(D6));
   if(digitalRead(D6)==0)
   {
    Serial.println("Not Detected  ");
    digitalWrite(LED, LOW);
    pir="No-Intruders";
   }
   else if(digitalRead(D6)==1)
   {
   Serial.println("detected  ");
   digitalWrite(LED, HIGH);
   pir="Caution!!!-intruders-detected";
   }
   delay(5000);
   Serial.println(digitalRead(D8));
  if (digitalRead(D8) == 1)
  {
    Serial.println("\n MQ2 Gas detected");
    mq2="GAS-Detected";
  }
  else if(digitalRead(D8)==1)
  {
    Serial.println("\n MQ2 Atmosphere is safe");
    mq2="Atmosphere-is-safe";
  }
  delay(1000);
  Serial.println();
  Serial.println();
  int analogSensor135=analogRead(A0);
  Serial.print("Air Sensor : ");
  Serial.println(analogRead(A0)); 
  if (analogRead(A0) > 500)
  {
    Serial.println("\n MQ135 Gas detected");
    mq135="Smoke-Detected";
  }
  else 
  {
    Serial.println("\n MQ135 Atmosphere is safe");
    mq135="Atmosphere-is-safe";
  }
  delay(1000);
  Serial.println();
  Serial.println();
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else
  {
    Serial.print(" Humidity : ");
    Serial.println(h);
    Serial.print(" Temperature : ");
    Serial.println(t);
  }
Serial.println();
  Serial.println();
  delay(2000);
  Serial.print("connecting to ");
  Serial.println(host);

  WiFiClient client;
  
ESP8266WebServer server(80);

  const int httpPort = 80;
  if (!client.connect(host, httpPort)) 
  {
    Serial.println("connection failed");
    return;
  }
  Serial.println();
  Serial.println();
  String url = "/insert.php?temp=" + String(t) + "&hum="+ String(h) + "&mq2="+ String(mq2) + "&mq135="+ String(mq135) + "&pir="+ String(pir);
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(1000);
  
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  
  delay(1000);
}
