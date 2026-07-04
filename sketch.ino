#define BLYNK_TEMPLATE_ID "TMPL66N8BelBZ"
#define BLYNK_TEMPLATE_NAME "Pengendalian Multi Relay Lampu Kipas dan Charger"
#define BLYNK_AUTH_TOKEN "bjXDCGg6LvzdAvCBhcPknS2c3l_Bd0Kg"


#define BLYNK_PRINT Serial

// Import library untuk koneksi ke Wifi dan Blynk khusus ESP32
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Konfigurasi jaringan WiFi
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST"; // Jaringan publik
char pass[] = "";            // Tanpa password

// Variabel untuk menyimpan status tombol dari Blynk
int value0, value1, value2, value6; 

// Mendefinisikan pin GPIO tempat LED atau relay terhubung
byte LED_Y = 26; // LED Kuning
byte LED_B = 27; // LED Biru
byte LED_R = 14; // LED Merah

// FUNGSI MENERIMA PERINTAH DARI APLIKASI BLYNK 

// Fungsi untuk Tombol V0 (LED Kuning)
BLYNK_WRITE(V0) {
  value0 = param.asInt();
  digitalWrite(LED_Y, value0);
  Blynk.virtualWrite(V7, value0); // Update LED indicator V7
  cekAllLed();
}

// Fungsi untuk Tombol V1 (LED Biru)
BLYNK_WRITE(V1) {
  value1 = param.asInt();
  digitalWrite(LED_B, value1);
  Blynk.virtualWrite(V8, value1); // Update LED indicator V8
  cekAllLed();
}

// Fungsi untuk Tombol V2 (LED Merah)
BLYNK_WRITE(V2) {
  value2 = param.asInt(); // FIX: Menggunakan variabel value2
  digitalWrite(LED_R, value2);
  Blynk.virtualWrite(V9, value2); // FIX: Mengirim status dari value2 ke LED indicator V9
  cekAllLed();
}

// Fungsi untuk Tombol V6 (Master Control)
BLYNK_WRITE(V6) {
  value6 = param.asInt();

  // Update semua LED fisik
  digitalWrite(LED_Y, value6);
  digitalWrite(LED_B, value6);
  digitalWrite(LED_R, value6);

  // Update semua variabel state
  value0 = value6;
  value1 = value6;
  value2 = value6;

  // Update semua widget di aplikasi agar sinkron
  Blynk.virtualWrite(V0, value6); // Sinkronkan tombol V0
  Blynk.virtualWrite(V1, value6); // Sinkronkan tombol V1
  Blynk.virtualWrite(V2, value6); // Sinkronkan tombol V2

  Blynk.virtualWrite(V7, value6); // Sinkronkan indikator V7
  Blynk.virtualWrite(V8, value6); // Sinkronkan indikator V8
  Blynk.virtualWrite(V9, value6); // Sinkronkan indikator V9
}

// FUNGSI BANTU

// Berfungsi untuk mengecek apakah semua LED individu menyala
void cekAllLed() {
  // FIX: Memeriksa value0, value1, dan value2
  if (value0 == 1 && value1 == 1 && value2 == 1) {
    Blynk.virtualWrite(V6, 1); // Jika semua ON, set tombol master ke ON
    value6 = 1;
  } else {
    Blynk.virtualWrite(V6, 0); // Jika ada yg OFF, set tombol master ke OFF
    value6 = 0;
  }
}

// FUNGSI UTAMA ESP32

// Inisialisasi pin, koneksi WiFi, dan Blynk
void setup() {
  Serial.begin(115200);
  
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_R, OUTPUT);
  
  Blynk.begin(auth, ssid, pass);
}

// Fungsi wajib untuk menjalankan Blynk secara terus-menerus
void loop() {
  Blynk.run();
}