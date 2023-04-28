void setup() {
  Serial.begin(2000000);
  pinMode(12, OUTPUT);
}

void loop() {
  
       //wait for data available
  Serial.setTimeout(1);
  String teststr = Serial.readStringUntil('\n');  //read until timeout
  Serial.print(teststr);
  // remove any \r \n whitespace at the end of the String
  if (teststr == "yukari") {
    
     digitalWrite(12, HIGH);
     delay(1000);
     digitalWrite(12, LOW);
     delay(1000);
     
  }
}
