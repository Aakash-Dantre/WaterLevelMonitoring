#include "WiFi.h"
#include "HTTPClient.h"
#include "ArduinoJson.h"
#include "time.h"

char* wifi_ssid = "aakash";
char* wifi_pwd = "spimander";
char* wifi_ssid2="";
char* wifi_pwd2="";

String cse_ip = "139.59.42.21";
String cse_port = "8080";
String server = "https://"+cse_ip+":"+cse_port+"/~/in-cse/in-name/";

int ledFlag=0;
uint8_t SENSOR_PIN = 2;
int LED_G = 4;
int LED_R = 5; 

StaticJsonBuffer<200> jsonBuffer;
JsonObject& user_data = jsonBuffer.createObject();
JsonObject& temp_user_data = jsonBuffer.createObject();
JsonObject& sensor_data = jsonBuffer.createObject();

void ledUpdate(){
  if(ledFlag==1){
    digitalWrite(LED_R,0);
    digitalWrite(LED_G,1);
  }
  else{
    digitalWrite(LED_R,1);
    digitalWrite(LED_G,0);
  }
}

String createCI(String server, String ae, String cnt, String val)
{
  HTTPClient http;
  http.begin(server + ae + "/" + cnt + "/");
  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json;ty=4");
  http.addHeader("Content-Length", "100");
  http.addHeader("Connection", "close");
  int code = http.POST("{\"m2m:cin\": {\"cnf\": \"text/plain:0\",\"con\": "+ String(val) +"}}");
  http.end();
  Serial.println(code);
  if(code==-1){
    Serial.println("UNABLE TO CONNECT TO THE SERVER");
    ledFlag=0;
    ledUpdate();
  }
  delay(300);
}

void connect_to_WIFI(){
  int flag=1;
  WiFi.mode(WIFI_STA);// Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.disconnect();
  delay(100);
  WiFi.begin(wifi_ssid, wifi_pwd);
  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED || WiFi.status()==WL_CONNECT_FAILED){
    delay(500);
    Serial.print(".");
  }
  if(WiFi.status()==WL_CONNECTED){
    Serial.println("Connected to the WiFi network");
    ledFlag=1;
    ledUpdate();
  }
  else{
    
  }
  Serial.println("Connected to the WiFi network");
}

void setup()
{
  Serial.begin(115200);
  ledUpdate();
  connect_to_WIFI();

  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G,OUTPUT);
  Serial.println("Setup done");

  // DOUBT -----------------------------------------------------------------------------------------------------------------------------------------??
  //createCI(server, "\"Team22_Water_Level_Monitoring_in_Overhead_Tanks", "project_description", "measuring_water_level_in_overhead_tanks");
  //createCI(server, "Team22_Water_Level_Monitoring_in_Overhead_Tanks", "node_description", "node_1:(photo_electric_fluid_level(=75%)");

}

void loop()
{
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connection lost.. trying to reconnect");
    ledFlag=0;ledUpdate();
    connect_to_WIFI();
  }
  
  int OUT = digitalRead(SENSOR_PIN);
  Serial.println(OUT);
  // convert it to a string
  String val = (String)OUT;

//  getLocalTime();//updates the timestamp
  delay(10);
  val = "\""  + val + "\"";

  // Send data to OneM2M server
  createCI(server, "Team4_Water_Level_Monitoring_in_Overhead_Tanks", "node_1", val);
  delay(60*5*1000); // DO NOT CHANGE THIS LINE 10 min delay

  
}