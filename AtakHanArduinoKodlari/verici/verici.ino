#include <SPI.h>
 #include <nRF24L01.h>
 #include <RF24.h>
 
const byte address[6] = "AtakHan";
char teststr[32];
RF24 radio(9, 10);
char bos = '\n';


void setup()
 {
 Serial.begin(2000000);
    Serial.println("Verici kart ile baglanti saglandi");

    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setPALevel(RF24_PA_MIN);
    radio.openWritingPipe(address);
 }
 
void loop()
 {

  Serial.setTimeout(2);
  if (Serial.available()) {
    Serial.readStringUntil('\n').toCharArray(teststr, 32);
    strcat(teststr,bos);
    Serial.println(teststr);
    radio.write(&teststr, sizeof(teststr));

  }
  //radio.write(&bos, sizeof(bos));
  

    
 }
