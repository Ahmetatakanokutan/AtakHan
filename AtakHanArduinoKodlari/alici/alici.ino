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
int SagKanatDeger = 90;
int SolKanatDeger = 90;
int YavasDonusDeger = 90;
int KalkisDeger = 90;
unsigned long YavYonEtkZam = 0;
unsigned long YatayEtkZam = 0;
unsigned long DikeyEtkZam = 0;
long ZamanKont;

void setup() {

  Serial.begin(19200);
  Brushless.attach(8);
  Kalkis.attach(7);
  SolKanat.attach(6);
  SagKanat.attach(5);
  YavasDonus.attach(4);
  radio.begin();
  radio.setDataRate( RF24_250KBPS );
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, address);
  radio.startListening();
  Brushless.write(10);
}

void loop() {
  
   if (radio.available()) {
    radio.read( &str, sizeof(str) );
    Serial.print(str);

    // Parçalanmış veriyi tutacak değişkenler
    char command[10];
    char valueStr[10];

    // Komutun başında "motor:" var mı kontrol et
    if (strncmp(str, "motor:", 6) == 0) {
      // Gelen değeri al
      char* valuePtr = str + 6; // "motor:" kısmını atla
      int value = atoi(valuePtr);
      
      // Gelen değeri kontrol et
      if (value >= 0 && value <= 100) {
        // Değeri uygun aralığa map et ve servo pozisyonunu ayarla
        int mappedValue = map(value, 0, 100, 1100, 1280);
        Brushless.write(mappedValue);
      }
    }

    
      if (!strcmp(str, "asagi")) {
        if(KalkisDeger > 40){

        KalkisDeger -= 5;
        Kalkis.write(KalkisDeger);
        }
        DikeyEtkZam = millis();
      }
      
    else if(!strcmp(str, "yukari")) {
      if(KalkisDeger <= 140){
        KalkisDeger += 5;
        Kalkis.write(KalkisDeger);
      }
      DikeyEtkZam = millis();
    }


    if (!strcmp(str, "sag")) {
      if (SagKanatDeger > 40 && SolKanatDeger > 40) {
        SagKanatDeger -= 5;
        SolKanatDeger -= 5;
        SagKanat.write(SagKanatDeger);
        SolKanat.write(SolKanatDeger);
      }
      YatayEtkZam = millis();
    }
    else if (!strcmp(str, "sol")) {
      if (SolKanatDeger < 140 && SagKanatDeger < 140) {
        SolKanatDeger += 5;
        SagKanatDeger += 5;
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
  else { // Eğer bağlantı kesilirse
    // Yeniden bağlantı kurma işlemleri
    if (!radio.isChipConnected()) {
      radio.begin();
      radio.setDataRate( RF24_250KBPS );
      radio.setPALevel(RF24_PA_MIN);
      radio.openReadingPipe(1, address);
      radio.startListening();
      Brushless.write(10); // Motoru başlangıç konumuna getir
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
if(!radio.isChipConnected()){
  Brushless.write(10);
}
    
}
