







void setup() {
  Serial.begin(9600);
  Serial.println("Enter AT command: ");
  Serial1.begin(9600);
  
}

void loop() {
  if (Serial1.available()) {
      Serial.write(Serial1.read());
      //Serial1.print("I'm OK");
      //Serial1.print("\r\n");
      
  }

  // read from port 0, send to port 1:
  if (Serial.available()) {
      Serial1.write(Serial.read());
  }
}
