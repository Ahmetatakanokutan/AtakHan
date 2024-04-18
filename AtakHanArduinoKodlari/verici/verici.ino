#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const byte address[6] = "AtakHan";
char teststr[32];
RF24 radio(9, 10);

void setup() {
  Serial.begin(2000000);
  Serial.println("Verici kart ile baglanti saglandi");

  radio.begin();
  radio.setDataRate( RF24_250KBPS );
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(address);
}

void loop() {
  if (Serial.available()) {
    // Gelen veriyi oku
    String input = Serial.readStringUntil('\n');
    
    // Stringi char dizisine kopyala ve sonuna null karakter ekle
    input.toCharArray(teststr, sizeof(teststr));
    
    // Veriyi radyo modülü aracılığıyla gönder
    radio.write(&teststr, sizeof(teststr));
    
    // Gelen veriyi seri port üzerinden tekrar gönder
    Serial.println(teststr);
  }
  
  // Bağlantı kontrolü
  if (!radio.isChipConnected()) {
    // Bağlantı kesildi, tekrar bağlan
    Serial.println("Baglanti kesildi, tekrar baglaniliyor...");
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setPALevel(RF24_PA_MAX);
    radio.openWritingPipe(address);
    Serial.println("Baglanti yeniden saglandi");
  }

}
