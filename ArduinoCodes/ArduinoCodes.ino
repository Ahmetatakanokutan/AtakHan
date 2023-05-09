#include <SPI.h> 
#include <nRF24L01.h> 
#include <RF24.h> 


RF24 radio(9,10);
const byte Address[6] = "atakHan";

void setup() {
  Serial.begin(2000000);
  pinMode(8, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0, Address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}

void loop() {
  char teststr[32];
  if (radio.available()) {
    radio.read(&teststr, sizeof(teststr));
    Serial.println(teststr);
  }
}
