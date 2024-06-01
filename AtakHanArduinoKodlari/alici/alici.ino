#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const byte address[6] = "AtakHan";
RF24 radio(9, 10);
Servo Brushless;
Servo SagKanat;
Servo SolKanat;
Servo YavasDonus;
Servo Kalkis;
char str[32];
unsigned long lastReceivedTime = 0; // Son veri alım zamanı
unsigned long connectionTimeout = 3000; // Bağlantı kesilme süresi (3 saniye)
bool connectionLost = false;

void setup() {
  Serial.begin(19200);
  Brushless.attach(8);
  Kalkis.attach(7);
  SolKanat.attach(6);
  SagKanat.attach(5);
  YavasDonus.attach(4);
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, address);
  radio.startListening();
  Brushless.write(10);
}

void loop() {
  if (radio.available()) {
    radio.read(&str, sizeof(str));
    Serial.print(str);

    // Son veri alım zamanını güncelle
    lastReceivedTime = millis();
    connectionLost = false;

    // Parçalanmış veriyi tutacak değişkenler
    int throttle = 0;
    int rudder = 0;
    int elevator = 0;
    int aileronRight = 0;
    int aileronLeft = 0;

    // Gelen veriyi ayrıştır
    sscanf(str, "%d/%d/%d/%d/%d", &throttle, &rudder, &elevator, &aileronRight, &aileronLeft);

    // Throttle kontrolü
    if (throttle >= 0 && throttle <= 100) {
      int mappedThrottle = map(throttle, 0, 100, 0, 180);
      Brushless.write(mappedThrottle);
    }

    // Rudder kontrolü
    if (rudder >= -50 && rudder <= 50) {
      int mappedRudder = map(rudder, -50, 50, 40, 140);
      YavasDonus.write(mappedRudder);
    }

    // Elevator kontrolü
    if (elevator >= -50 && elevator <= 50) {
      int mappedElevator = map(elevator, -50, 50, 40, 140);
      Kalkis.write(mappedElevator);
    }

    // Aileron Right kontrolü
    if (aileronRight >= -50 && aileronRight <= 50) {
      int mappedAileronRight = map(aileronRight, -50, 50, 40, 140);
      SagKanat.write(mappedAileronRight);
    }

    // Aileron Left kontrolü
    if (aileronLeft >= -50 && aileronLeft <= 50) {
      int mappedAileronLeft = map(aileronLeft, -50, 50, 40, 140);
      SolKanat.write(mappedAileronLeft);
    }
  } else { // Eğer bağlantı kesilirse
    unsigned long currentMillis = millis();

    // Bağlantı kesilme süresi kontrolü
    if (currentMillis - lastReceivedTime >= connectionTimeout) {
      if (!connectionLost) {
        connectionLost = true;
        YavasDonus.write(110); // YavasDonus servosunu 110 değerine ayarla
        delay(2000); // 2 saniye bekle
        YavasDonus.write(90); // YavasDonus servosunu 90 değerine geri getir
      }
    } else if (currentMillis - lastReceivedTime >= 500) { // Kısa süreli bağlantı kesilmesi
      YavasDonus.write(90);
      SagKanat.write(90);
      SolKanat.write(90);
      Kalkis.write(90);
    }
    
    // Yeniden bağlantı kurma işlemleri
    if (!radio.isChipConnected()) {
      radio.begin();
      radio.setDataRate(RF24_250KBPS);
      radio.setPALevel(RF24_PA_MIN);
      radio.openReadingPipe(1, address);
      radio.startListening();
      Brushless.write(10); // Motoru başlangıç konumuna getir
    }
  }

  // ZamanKont işlemleri
  static unsigned long YavYonEtkZam = 0;
  static unsigned long YatayEtkZam = 0;
  static unsigned long DikeyEtkZam = 0;
  long ZamanKont;

  ZamanKont = (YavYonEtkZam + 100) - millis();
  if (ZamanKont < 0) {
    YavasDonus.write(90);
  }

  ZamanKont = (YatayEtkZam + 100) - millis();
  if (ZamanKont < 0) {
    SagKanat.write(90);
    SolKanat.write(90);
  }

  ZamanKont = (DikeyEtkZam + 100) - millis();
  if (ZamanKont < 0) {
    Kalkis.write(90);
  }

  if (!radio.isChipConnected()) {
    Brushless.write(10);
  }
}
