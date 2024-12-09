#include <Wire.h>
#include <HTTPClient.h>
#include <WiFi.h>

String url = "http://192.168.1.5/Penyiraman/index.php";
volatile bool flag = false;
byte n;

// Struktur data yang diterima melalui I2C
struct myStruct {
  uint8_t pompa;  // 1 byte instead of 4 bytes
  uint8_t humidity; // 1 byte
  uint8_t tanah; // 1 byte
};

myStruct myData; // Data yang diterima

const char* ssid = "Projek";
const char* password = "TekomB23";

IPAddress local_IP(192, 168, 1, 2);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

String pompa;
void setup() {
  Serial.begin(9600);
  Wire.begin(0x23);           // Initialize ESP32 as I2C slave with address 0x23
  Wire.onReceive(receiveEvent); // Register receive event handler

  // Konfigurasi WiFi Access Point
  Serial.print("Setting up Access Point . . .");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
  Serial.print("Setting AP . . .");
  Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");
  Serial.print("IP Address = ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  if (flag) {
    // Cetak data yang diterima
    Serial.println("Data received:");
    Serial.print("Message: ");
    if (myData.pompa == 1) {
      pompa = "Pompa_Aktif";
      Serial.println("Pompa Aktif");
    } else if (myData.pompa == 0) {
      pompa = "Pompa_Tidak_Aktif";
      Serial.println("Pompa_Tidak_Aktif");
    }
    Serial.print("Humidity: ");
    Serial.println(myData.humidity);
    Serial.print("Tanah: ");
    Serial.println(myData.tanah);
    // Kirim data ke server melalui HTTP
    HTTPClient http;
    String postData = url + "?status=" + String(pompa) + "&humidity=" + String(myData.humidity) + "&soil=" + String(myData.tanah);
    http.begin(postData.c_str());
    int httpCode = http.GET();
    String payload = http.getString();
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Cetak hasil HTTP
    Serial.print("URL: "); Serial.println(url);
    Serial.print("Data: "); Serial.println(postData);
    Serial.print("HTTP Code: "); Serial.println(httpCode);
    Serial.print("Payload: "); Serial.println(payload);
    Serial.println("-----------------------------------------------------------------------");
    http.end();

    // Reset flag
    flag = false;
  }
}

void receiveEvent(int howMany) {
  n = howMany; // Jumlah byte yang diterima
  Serial.print("Bytes received: ");
  Serial.println(n);

  // Periksa apakah ukuran data sesuai dengan ukuran struktur
  if (howMany == sizeof(myData)) { 
    Wire.readBytes((byte*)&myData, sizeof(myData));
    flag = true; // Tandai bahwa data baru telah diterima
  } else {
    Serial.print("Incorrect data size received. Expected: ");
    Serial.print(sizeof(myData));
    Serial.print(", Received: ");
    Serial.println(howMany);
  }
}
