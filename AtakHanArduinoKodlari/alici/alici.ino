#include<Servo.h>
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
int thrust = 0;
int SagKanatDeger = 90;
int SolKanatDeger = 90;
int YavasDonusDeger = 90;
int KalkisDeger = 90;
unsigned long YavYonEtkZam = 0; //motorlarin calistiktan sonra origin noktalarina donmeleri icin hazirlanmis zaman degerleri
unsigned long YatayEtkZam = 0;
unsigned long DikeyEtkZam = 0;
long ZamanKont;

void setup() {

  Serial.begin(19200);
  Brushless.attach(8);
  Kalkis.attach(7);
  SolKanat.attach(6);
  SagKanat.attach(5);
  YavasDonus.attach(4);;
  radio.begin();
  radio.setDataRate( RF24_250KBPS );
  radio.setPALevel(RF24_PA_MAX);
  radio.openReadingPipe(1, address);
  radio.startListening();
  Brushless.write(10);
  //SagKanat.write(50);
  //SolKanat.write(50);
  //delay(5000);
}

void loop() {
  
  if (radio.available()) {
    radio.read( &str, sizeof(str) );
    Serial.print(str);

    if (thrust = atoi(str)) {
      thrust = map(thrust, 0, 100, 1000, 2000);
      Brushless.write(thrust);
    }

    
      if (!strcmp(str, "yukari")) {
        if(KalkisDeger > 40){
        KalkisDeger -= 5;
        Kalkis.write(KalkisDeger);
        }
        DikeyEtkZam = millis();
      }
      
    else if(!strcmp(str, "asagi")) {
      if(KalkisDeger <= 140){
        KalkisDeger += 5;
        Kalkis.write(KalkisDeger);
      }
      DikeyEtkZam = millis();
    }


    if (!strcmp(str, "sag")) {
      if (SagKanatDeger < 140 && SolKanatDeger > 40) {
        SagKanatDeger += 5;
        SolKanatDeger -= 5;
        SagKanat.write(SagKanatDeger);
        SolKanat.write(SolKanatDeger);
      }
      YatayEtkZam = millis();
    }
    else if (!strcmp(str, "sol")) {
      if (SolKanatDeger < 140 && SagKanatDeger > 40) {
        SolKanatDeger += 5;
        SagKanatDeger -= 5;
        SagKanat.write(SagKanatDeger);
        SolKanat.write(SolKanatDeger);
      }
      YatayEtkZam = millis();
    }
    if(!strcmp(str, "yavasol")){
      if(YavasDonusDeger <140){
        YavasDonusDeger += 5;
        YavasDonus.write(YavasDonusDeger);
      }
      YavYonEtkZam = millis();
    }
    else if(!strcmp(str, "yavasag")){
      if(YavasDonusDeger > 40){
        YavasDonusDeger -= 5;
        YavasDonus.write(YavasDonusDeger);
      }
      YavYonEtkZam = millis();
    }
  }

  ZamanKont = (YavYonEtkZam + 100) - millis();
  if(ZamanKont < 0){
    YavasDonusDeger = 90;
    YavasDonus.write(YavasDonusDeger);
  }

  ZamanKont = (YatayEtkZam+ 100)- millis();
  if(ZamanKont < 0){
    SagKanatDeger = 90;
    SolKanatDeger = 90;
    SagKanat.write(SagKanatDeger);
    SolKanat.write(SolKanatDeger);
  }

  ZamanKont = (DikeyEtkZam + 100)- millis();
  if(ZamanKont < 0){
    KalkisDeger = 90;
    Kalkis.write(KalkisDeger);
  }
    
}

