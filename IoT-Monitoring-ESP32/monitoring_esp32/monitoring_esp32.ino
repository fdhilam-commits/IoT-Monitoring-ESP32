#include WiFi.h
#include DHT.h

 =====================================
 KONFIGURASI WIFI
 =====================================
const char ssid = MR-FK-01;
const char password = adzanmasjid;


 =====================================
 KONFIGURASI SENSOR DHT22 3 KAKI
 =====================================
#define DHTPIN 27
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

 =====================================
 KONFIGURASI SENSOR HY-SRF05
 =====================================
#define TRIG_PIN 13
#define ECHO_PIN 14

 =====================================
 VARIABEL DATA SENSOR
 =====================================
float suhu;
float kelembapan;
float jarak;

 =====================================
 FUNGSI KONEKSI WIFI
 =====================================
void koneksiWiFi() {

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print(Menghubungkan ke WiFi);

  unsigned long waktuMulai = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - waktuMulai  20000) {

    delay(500);
    Serial.print(.);
  }

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println(nWiFi berhasil terhubung!);

    Serial.print(IP Address );
    Serial.println(WiFi.localIP());

  } else {

    Serial.println(nWiFi gagal terhubung!);
  }
}

 =====================================
 FUNGSI MEMBACA SENSOR HY-SRF05
 =====================================
float bacaJarak() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long durasi = pulseIn(ECHO_PIN, HIGH, 30000);

  if (durasi == 0) {
    return -1;
  }

  float hasilJarak = durasi  0.0343  2;

  return hasilJarak;
}

 =====================================
 SETUP
 =====================================
void setup() {

  Serial.begin(115200);

   Inisialisasi DHT22
  dht.begin();

   Inisialisasi HY-SRF05
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);

  Serial.println();
  Serial.println(==================================);
  Serial.println( SISTEM MONITORING IoT ESP32);
  Serial.println( DHT22 + HY-SRF05);
  Serial.println(==================================);

   Menghubungkan WiFi
  koneksiWiFi();
}

 =====================================
 LOOP UTAMA
 =====================================
void loop() {

   Membaca data DHT22
  suhu = dht.readTemperature();
  kelembapan = dht.readHumidity();

   Membaca data HY-SRF05
  jarak = bacaJarak();

  Serial.println();
  Serial.println(========== DATA SENSOR ==========);

   Menampilkan suhu
  if (isnan(suhu)) {

    Serial.println(Suhu        Gagal membaca!);

  } else {

    Serial.print(Suhu        );
    Serial.print(suhu);
    Serial.println( °C);
  }

   Menampilkan kelembapan
  if (isnan(kelembapan)) {

    Serial.println(Kelembapan  Gagal membaca!);

  } else {

    Serial.print(Kelembapan  );
    Serial.print(kelembapan);
    Serial.println( %);
  }

   Menampilkan jarak
  if (jarak  0) {

    Serial.println(Jarak       Sensor tidak terbaca);

  } else {

    Serial.print(Jarak       );
    Serial.print(jarak);
    Serial.println( cm);

     Logika kondisi objek
    if (jarak  20) {

      Serial.println(Status      Objek terdeteksi dekat!);

    } else {

      Serial.println(Status      Objek berada jauh.);
    }
  }

   Memeriksa koneksi WiFi
  if (WiFi.status() == WL_CONNECTED) {

    Serial.println(WiFi        Terhubung);

  } else {

    Serial.println(WiFi        Terputus);
  }

  Serial.println(=================================);

   Interval pembacaan sensor
  delay(2000);
}

