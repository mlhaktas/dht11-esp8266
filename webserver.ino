#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <dht11.h>
dht11 DHT11;

ESP8266WebServer server(80);

const char* ssid = "Wi-Fi SSID";
const char* password =  "Wi-Fi Password";
 
void setup() {
  Serial.begin(115200); //Begin Serial at 115200 Baud
  WiFi.begin(ssid, password);  //Connect to the WiFi network
  
  while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
      delay(1000);
      Serial.println("Waiting...");
  }
  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address
  server.on("/", handle_index);
  server.begin();
  Serial.println("Server listening");
}

void loop() {
  int chk = DHT11.read(0);
  server.handleClient();
}

void handle_index() {
  server.send(200, "text/plain", "ESP8226 - Uzaktan Okuma , Deger : " + String((float)DHT11.temperature, 2));
}
