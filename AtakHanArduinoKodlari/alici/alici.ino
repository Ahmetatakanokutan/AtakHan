
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const byte address[6] = "AtakHan";
RF24 radio(9, 10);

char str[7]; // this must match dataToSend in the TX
bool newData = false;

void setup() {

    Serial.begin(19200);
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setPALevel(RF24_PA_MAX);
    radio.openReadingPipe(1, address);
    radio.startListening();
}

void loop() {
if ( radio.available() ) {
        radio.read( &str, sizeof(str) );
        Serial.println(str);
    }
    
}

