#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTPIN D4
#define DHTTYPE DHT11 

const char* ssid     = "Uma";
const char* password = "Uma123*!";

DHT dht(DHTPIN, DHTTYPE);
IPAddress ip(192,168,18,5);
IPAddress gateway(192,168,18,5);
IPAddress subnet(255,255,255,0);
#define LED D3
void setup() {
  pinMode(LED, OUTPUT); 
  
  Serial.println("IOT Based Smart Agriculture Monitoring System ");
Serial.println("============================================= ");
Serial.println();
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
Serial.println("=========================================================== ");
}
void loop() {
  Serial.println();
  Serial.println();
  

  int digitalSensor2=digitalRead(D8);
  
  
  
  Serial.print("PIR Sensor : ");
  
   if(digitalRead(D6)==0)
   {
    Serial.println("No Intruders Detected  ");
    digitalWrite(LED, LOW);
Serial.println("=========================================================== ");
   
   }
   else if(digitalRead(D6)==1)
   {
   Serial.println("detected  ");
   digitalWrite(LED, HIGH);
   
Serial.println("=========================================================== ");
   }
   delay(1000);
   
  
  Serial.println();
  Serial.println();
  int analogSensor135=analogRead(A0);
 
  if (analogRead(A0) > 500)
  {
    Serial.println("\n MQ135 Dected Harmfull Gases");
Serial.println("=========================================================== ");
    
  }
  else 
  {
    Serial.println("\n Atmosphere is safe as per MQ135");
Serial.println("=========================================================== ");
    
  }
  delay(1000);
if (digitalRead(D8) == 1)
  {
    Serial.println("\n MQ2 Detected Harmfull Gases");
Serial.println("=========================================================== ");
    
  }
  else if(digitalRead(D8)==0)
  {
    Serial.println("\n Atmosphere is safe as per MQ2 Sensor");
Serial.println("=========================================================== ");
   
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
Serial.println("=========================================================== ");
    return;
  }
  else
  {
    Serial.print(" Humidity : ");
    Serial.println(h);
    Serial.print(" Temperature : ");
    Serial.println(t);
Serial.println("=========================================================== ");
  }
Serial.println();
  Serial.println();
  delay(2000);
if(t >= 22 && t <= 32)
{
Serial.println("Hey!!! It's the perfect climate to grow Paddy. Worth trying!!!");
}
if(t>=10 && t<=15)
{
Serial.println("Hey!!! It's the perfect climate to grow Wheat. Worth trying!!!");
}
if(t>=27 && t<=32)
{
Serial.println("Hey!!! It's the perfect climate to grow Millets. Worth trying!!!");
}
if(t>=20 && t<=25)
{
Serial.println("Hey!!! It's the perfect climate to grow Grams. Worth trying!!!");
}
if(t>=21 && t<=27)
{
Serial.println("Hey!!! It's the perfect climate to grow Sugar Cane. Worth trying!!!");
}
if(t>=21 && t<=30)
{
Serial.println("Hey!!! It's the perfect climate to grow Cotton. Worth trying!!!");
}
if(t>=20 && t<=30)
{
Serial.println("Hey!!! It's the perfect climate to grow Oilseeds. Worth trying!!!");
}
if(t>=20 && t<=30)
{
Serial.println("Hey!!! It's the perfect climate to grow Tea. Worth trying!!!");
}
if(t>=15 && t<=28)
{
Serial.println("Hey!!! It's the perfect climate to grow Coffee. Worth trying!!!");
}
Serial.println("=====================Thank You============================= ");
Serial.println("=========================================================== ");
Serial.println("=========================================================== ");
}
