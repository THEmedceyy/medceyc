#include <SoftwareSerial.h>
#include <DHT.h>

// --- Bluetooth Tanımları ---
SoftwareSerial BTSerial(6, 7); // RX, TX

// --- Donanım Tanımları ---
#define DHTPIN 5
#define DHTTYPE DHT11
#define BUZZER_PIN 9
#define LED_PIN 3
#define SMOKE_PIN A0

DHT dht(DHTPIN, DHTTYPE);

// --- Eşik Değerler ---
int esikDegeriSic = 25;
int esikDegeri = 100;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  dht.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Sistem Başlatıldı");
  BTSerial.println("Bluetooth bağlantısı kuruldu.");
}

void loop() {
  int smokeValue = analogRead(SMOKE_PIN);
  float temperature = dht.readTemperature();

  Serial.print("Duman: ");
  Serial.print(smokeValue);
  Serial.print(" | Sıcaklık: ");
  Serial.println(temperature);

  if (smokeValue > esikDegeri && temperature > esikDegeriSic) {
    tone(BUZZER_PIN, 4000); // 4000 Hz ile daha yüksek ses
    digitalWrite(LED_PIN, HIGH);
    BTSerial.println("DİKKAT !!! Yangın Tehlikesi 🔥🔥🔥🔥");

    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
  } else {
    noTone(BUZZER_PIN); // Buzzer'ı durdur
    digitalWrite(LED_PIN, LOW);
  }

  delay(500);
}
