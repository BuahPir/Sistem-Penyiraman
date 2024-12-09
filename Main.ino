#include <DHT.h>
#include <Wire.h>
#include <RTClib.h>

// Definisi pin dan sensor
#define DHTPIN 9
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHT11);

const int soilMoisturePin = 10;
const int relayPin = 8;
const int LedPin = 7;
int ldr = A0;
RTC_DS3231 rtc;

struct myStruct {
  uint8_t pompa;  // 1 byte instead of 4 bytes
  uint8_t humidity; // 1 byte
  uint8_t tanah; // 1 byte
};

myStruct myData;

void setup() {
  Serial.begin(9600); // Memulai komunikasi serial
  dht.begin();
  Wire.begin(); // Memulai I2C
  Wire.beginTransmission(0x23);
  byte busStatus = Wire.endTransmission();
  if (busStatus != 0) {
    Serial.println("ESP32 is not found!");
    while (1); // Wait forever
  }
  Serial.println("ESP32 is found.");
  
  // Memeriksa koneksi RTC DS3231
  if (!rtc.begin()) {
    Serial.println("Tidak dapat menemukan RTC DS3231");
    while (1); // Hentikan program jika RTC tidak ditemukan
  }
  
  // Periksa apakah RTC kehilangan daya
  if (rtc.lostPower()) { 
    Serial.println("RTC kehilangan daya. Mengatur waktu ke waktu kompilasi.");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Atur waktu RTC ke waktu kompilasi
  }
  
  pinMode(LedPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
}

String Detik(uint8_t x) {
  String DetikStr;
  if (x < 10) DetikStr = "0"; 
  else DetikStr = ""; 
  DetikStr = DetikStr + x;
  return DetikStr;
}

String JamMenit(uint8_t h, uint8_t i) {
  String JamMenit = "";
  JamMenit = JamMenit + Detik(h) + ":" + Detik(i);
  return JamMenit;
}

void loop() {
  DateTime now = rtc.now(); // Membaca waktu saat ini dari RTC
  int humidity = dht.readHumidity();
  int sensorValue = analogRead(soilMoisturePin); // Membaca kelembapan tanah
  int soilMoisturePercent = map(sensorValue, 1023, 0, 0, 100); // Konversi ke persentase
  int SensorLDR = analogRead(ldr); // Membaca nilai sensor LDR
  int lightPercent = map(SensorLDR, 0, 1023, 0, 100);

  // Tampilkan data di serial monitor
  Serial.print("Kelembaban Udara: ");
  Serial.println(humidity);
  Serial.print("Kelembapan Tanah: ");
  Serial.print(soilMoisturePercent);
  Serial.println("%");
  Serial.print("Cahaya: ");
  Serial.print(lightPercent);
  Serial.println("%");
  Serial.print("Jam: ");
  Serial.println(JamMenit(now.hour(), now.minute()));

  myData.humidity = dht.readHumidity();
  myData.tanah = map(sensorValue, 1023, 0, 0, 100);
  
  // Logika kontrol pompa dan LED
  if (soilMoisturePercent < 30 || soilMoisturePercent < 40) {
    myData.pompa = 1;
    if (humidity < 40 || lightPercent > 50) {
      digitalWrite(relayPin, LOW); // Aktifkan pompa
      delay(5000);
    } else if ((humidity > 40 && humidity < 60) || (lightPercent > 40 && lightPercent < 50)) {
      digitalWrite(relayPin, LOW); // Aktifkan pompa
      delay(2000);
    } else {
      digitalWrite(relayPin, LOW); // Aktifkan pompa
      delay(1000);
    }
    digitalWrite(LedPin, HIGH);
  } else {
    digitalWrite(LedPin, LOW);
    digitalWrite(relayPin, HIGH); // Nonaktifkan pompa
    myData.pompa = 0;
  }

  // Kirim data ke ESP32
  Serial.println(sizeof myData);
  Wire.beginTransmission(0x23);
  Wire.write((byte*)&myData, sizeof(myData)); // Mengirim seluruh struktur
  Wire.endTransmission();

  delay(2000); // Tunggu 2 detik
}
