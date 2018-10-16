/* getTAG.ino
 *
 * Created by Danilo Queiroz Barbosa, August 26, 2016.
 * Member of electronicdrops.com
 *
 * This example shows how to use the RFIDRdm630 library.
 * When a card is read, an ASCII TAG and a Card Number
 * will be show in the Serial.*
 *
 *
 *   This example code is in the public domain.

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 */

#include "RFIDRdm630mod.h"
//char * tag;

RFIDtag  in_tag;  // RFIDtag object
RFIDtag  out_tag;  // RFIDtag object

RFIDRdm630 in_reader = RFIDRdm630(&Serial1);    // the reader object.
RFIDRdm630 out_reader = RFIDRdm630(&Serial2);    // the reader object.

int updates;
int failedUpdates;
int pos;
int stringplace = 0;

String latitude = "";
String longitude = "";

String timeUp;
String nmea[15];

int count;
const int MAX = 4;
const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;
void setup() {
  count=0;
  Serial.begin(9600);   // open the Serial for show data
  gps_setup();
    pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);

}

void loop() {
  digitalWrite(ledPin, state);
  if(state==HIGH){
    Serial.println("R");
    }else{
      Serial.println("S");
      }
  if (in_reader.isAvailable()){  // tests if a card was read by the module
    
    in_tag = in_reader.getTag();  // if true, then receives a tag object
    Serial.print("IN Card Number: ");
    Serial.print(in_tag.getCardNumber());  // get cardNumber in long format

    gps_loop();
    
    Serial.print(" GPS Latitude: ");
    Serial.print(latitude);  // get cardNumber in long format
    Serial.print(" GPS Longitude: ");
    Serial.print(longitude);  // get cardNumber in long format
    Serial.print("\r\n");

    if(count<MAX){
      count++;
    }
    Serial.print("count is ");
    Serial.println(count);
  }

  if (out_reader.isAvailable()){  // tests if a card was read by the module

    out_tag = out_reader.getTag();  // if true, then receives a tag object
    Serial.print("OUT Card Number: ");
    Serial.print(out_tag.getCardNumber());  // get cardNumber in long format
    
    gps_loop();
    
    Serial.print(" GPS Latitude: ");
    Serial.print(latitude);  // get cardNumber in long format
    Serial.print(" GPS Longitude: ");
    Serial.print(longitude);  // get cardNumber in long format
    Serial.print("\r\n");
    
    if(count>0){
      count--;
    }
    Serial.print("count is ");
    Serial.println(count);
  }

}
  void blink() {
  state = !state;
}
