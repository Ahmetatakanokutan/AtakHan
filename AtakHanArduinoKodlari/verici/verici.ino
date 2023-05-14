#include <SPI.h>
 #include <nRF24L01.h>
 #include <RF24.h>
 
const byte address[6] = "AtakHan";
  char teststr[32];
RF24 radio(9, 10);

void setup()
 {
 Serial.begin(2000000);
    Serial.println("SimpleTx Starting");

    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setPALevel(RF24_PA_MAX);
    radio.openWritingPipe(address);
 }
 
void loop()
 {
 bool rslt;

  Serial.setTimeout(2);
  if (Serial.available()) {
    Serial.readStringUntil('\n').toCharArray(teststr, 32);
    Serial.println(teststr);
    radio.write(&teststr, sizeof(teststr));

  }
  

    
 }
