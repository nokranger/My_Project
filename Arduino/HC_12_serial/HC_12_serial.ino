
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
        Serial1.println("AD1 + S1");
        Serial1.end();
        delay(1000);
        Serial.println("Solid 1 open");
        delay(500);
        Serial.println("Solid 2 off");
        delay(500);
        Serial.println("Solid 1 off");
        Serial.println("Waiting for calulate data");
        delay(2000);
        int mm[9];
        int total = 0;
        int count = 0;
        for(int i = 0;i < 10;i++){
          mm[i] = sensor.readRangeContinuousMillimeters();
          total = total + mm[i];
          Serial.print("Total : ");
          Serial.print(i);
          Serial.print(" = ");
          Serial.println(total);
          count++;
        }
        total = total / count;
        Serial.print("Total : ");
        Serial.println(total);
        if (sensor.timeoutOccurred())Serial.print(" TIMEOUT"); 
//        Serial.println("mm");
        delay(500);
        Serial.print("AD1 + DS");
        Serial.print(total);
        Serial.println(" +S1OFF + S2OFF + WFCD3s");
        Serial1.begin(9600);
        Serial1.print("AD1 + DS");
        Serial1.print(total);
        Serial1.println(" +S1OFF + S2OFF + WFCD3s");
        Serial1.end();
        delay(3000);
        Serial.println("Solid 1 off");
        delay(500);
        Serial.println("Solid 2 on");
        delay(500);
        Serial1.begin(9600);
        Serial1.println("AD1 + S1OFF + S2ON");
        Serial1.end();
        delay(3000);
        status = 0;
        Serial1.begin(9600);
        Serial1.println("AD1 + S1OFF + S2OFF");
        Serial1.println("AD1 + END");
        Serial.println("AD1 + END");
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
