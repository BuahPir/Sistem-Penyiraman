# Sistem Penyiraman Otomatis Berbasis Mikrokontroller
Ini adalah projek Mata Kuliah Sistem Mikroprosessor.
Sistem Penyiraman akan otomatis menyala jika memenuhi kondisi pada cuaca, cahaya ataupun kelembaban tanah

## Komponen
<ol type="1">
  <li>DS3231</li>
  <li>Arduino Uno</li>
  <li>ESP32</li>
  <li>DHT11</li>
  <li>Soil Moisture Sensor</li>
  <li>Pompa Air</li>
  <li>Relay Module</li>
  <li>Baterai 18650 x4</li>
  <li>LDR</li>
</ol>

## Cara Kerja
<ol type="1">
  <li>Arduino akan membaca data dari Komponen DHT, Soil Moisture, LDR atau DS3231</li>
  <li>Jika Data dari Komponen memenuhi kondisi yang di tentukan maka Pompa Air akan menyala</li>
  <li>Lalu Arduino akan melakukan Communication I2C ke ESP32 yang dimana Arduino sebagai Master dan ESP32 sebagai Slave</li>
  <li>Dan ESP32 akan mengirim data Status ke Server lalu ke Database (Disini saya menggunakan Laptop sebagai server)</li>
</ol>

## Video Percobaan
https://youtu.be/nti7PfLroRU

## Rangkaian
<img src="Untitled Sketch_bb.png">

## Schematic
<img src="Untitled Sketch_schem.png">
