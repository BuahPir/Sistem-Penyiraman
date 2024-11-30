// Pin analog untuk sensor kelembapan tanah
#include <DHT.h>
#include <SoftwareSerial.h>
#define DHTPIN 9
#define DHTTYPE DHT11
SoftwareSerial arduino(2, 13);
DHT dht(DHTPIN, DHT11);

const int soilMoisturePin = 10;
const int relayPin = 8;
const int LedPin = 7;

void setup() {
  Serial.begin(9600); // Memulai komunikasi serial
  dht.begin();
  arduino.begin(9600);
  pinMode(LedPin,OUTPUT);
  pinMode(relayPin,OUTPUT);
}

void loop() {
  int humidity = dht.readHumidity();
  int sensorValue = analogRead(soilMoisturePin); // Membaca nilai dari sensor
  int soilMoisturePercent = map(sensorValue, 1023, 0, 0, 100); // Mengubah nilai menjadi persentase
  Serial.print("Kelembaban Udara:");
  Serial.println(humidity);
  Serial.print("Kelembapan Tanah: ");
  Serial.print(soilMoisturePercent);
  Serial.println("%");
  if(humidity <90 && soilMoisturePercent < 75 ){
    digitalWrite(LedPin,HIGH);
    digitalWrite(relayPin, LOW); // Menghidupkan pompa (relay aktif)
    delay(3000); // Pompa menyala selama 5 detik
    arduino.print("POMPA_AKTIF");
  } else {
    digitalWrite(LedPin,LOW);
    digitalWrite(relayPin, HIGH);
    arduino.print("POMPA_TIDAK_AKTIF");
    delay(1000);
  }
 // Tunggu 1 detik sebelum membaca lagi
}