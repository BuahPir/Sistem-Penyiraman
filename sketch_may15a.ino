#include <HTTPClient.h>
#include <WiFi.h>
#include <NewPing.h>
String url = "http://192.168.1.5/Penyiraman/index.php";
#define max 200
#define RX 13
#define TX 12

const char* ssid = "Projek";
const char* password = "TekomB23";

IPAddress local_IP(192,168,1,2);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1,RX,TX);
  Serial.print("Setting up Access Point . . .");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

  Serial.print("Setting AP . . .");
  Serial.println(WiFi.softAP(ssid, password)? "Ready" : "Failed!");

  Serial.print("IP Address = ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  if (Serial2.available()) {
    String konversi = Serial2.readString();
    HTTPClient http;
    String postData = url +"?status="+String(konversi);
    http.begin(postData.c_str());
    int httpCode = http.GET(); 
    String payload = http.getString();
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    Serial.print("URL: "); Serial.println(url);
    Serial.print("Data: "); Serial.println(postData);
    Serial.print("httpCode: "); Serial.println(httpCode);
    Serial.print("Payload: "); Serial.println(payload);
    Serial.println("-----------------------------------------------------------------------");
    http.end();
  }
}