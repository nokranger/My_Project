
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

int status = 0;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("Enter AT command: ");
  Serial1.begin(9600);
  sensor.init();
  sensor.startContinuous();
  
}

void loop() {
  if (Serial1.available() > 0) {
      //Serial.write(Serial1.read());
      //Serial1.print("I'm OK");
      //Serial1.print("\r\n");
      String temp = Serial1.readString();
      Serial.print(temp);
      if(temp == "AD1 + ST\r\n"){
        Serial1.end();
        status = 1;
        if(status == 1){
        Serial1.begin(9600);
        Serial1.println("Sta1");
        Serial1.end();
        delay(500);
        int mm = sensor.readRangeContinuousMillimeters();
//        Serial.print(mm);
        if (sensor.timeoutOccurred())Serial.print(" TIMEOUT"); 
//        Serial.println("mm");
        delay(1000);
        Serial.println("Solid 1 open");
        delay(500);
        Serial.println("Solid 2 off");
        delay(500);
        Serial.println("Waiting for calulate data");
        delay(500);
        Serial.print("AD1 + S1OP + S2OFF + WFCD3s + DS");
        Serial.println(mm);
        Serial1.begin(9600);
        Serial1.print("AD1 + S1OP + S2OFF + WFCD3s + DS");
        Serial1.println(mm);
        Serial1.end();
        delay(3000);
        Serial.println("Solid 1 off");
        delay(500);
        Serial.println("Solid 2 on");
        delay(500);
        Serial1.begin(9600);
        Serial1.println("S1OFF + S2ON");
        Serial1.end();
        delay(3000);
        status = 0;
        Serial1.begin(9600);
        Serial1.println("END");
        Serial.println("END");
        Serial1.end();
        Serial1.begin(9600);
        }
        }
      //Serial.println("this is serial read" + Serial1.read());
  }
  // read from port 0, send to port 1:
  if (Serial.available()) {
      Serial1.write(Serial.read());
  }
}
