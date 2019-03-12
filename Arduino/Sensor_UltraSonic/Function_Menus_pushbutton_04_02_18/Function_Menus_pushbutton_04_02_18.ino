#include <Wire.h> 
#include <LiquidCrystal_I2C.h> //ประกาศ Library ของจอ I2C
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 20, 4);
/* Basic Digital Read
 * ------------------ 
 *
 * turns on and off a light emitting diode(LED) connected to digital  
 * pin 13, when pressing a pushbutton attached to pin 7. It illustrates the
 * concept of Active-Low, which consists in connecting buttons using a
 * 1K to 10K pull-up resistor.
 *
 * Created 1 December 2005
 * copyleft 2005 DojoDave <http://www.0j0.org>
 * http://arduino.berlios.de
 *
 */
#define MAX 3 
#define MIN 1 
int ledPin = 7; // choose the pin for the LED
int buttonPin = 6;   // choose the input pin (for a pushbutton) 
int buttonPin2 = 5;   // choose the input pin (for a pushbutton)
int buttonEnterPin = 4;   // choose the input pin (for a pushbutton)
int checkP1 = 0;     // variable for reading the pin status
int checkP2 = 0;
int enter = 0;
int sum = 1;
bool checksum;
/*bool isInStage_choose_chemecals ;
enum Stage {
  none,
  display_sg,
  display_times,
  choose_chemecals
};
Stage curStage ;*/

void setup() {
  lcd.begin();
  //curStage = none ;
  pinMode(ledPin, OUTPUT);  // declare LED as output
  //pinMode(ledPin2, OUTPUT);  // declare LED as output
  //pinMode(ledPin3, OUTPUT);  // declare LED as output
  pinMode(buttonPin, INPUT);    // declare pushbutton as input
  pinMode(buttonPin2, INPUT);    // declare pushbutton as input
  Serial.begin(9600);
  checksum = false;
  //isInStage_choose_chemecals = false ;
}

void loop(){  
  
  checkP1 = digitalRead(buttonPin);  // read input value
  checkP2 = digitalRead(buttonPin2);  // read input value
  enter = digitalRead(buttonEnterPin);  // read input value
  
  if (checkP1 == HIGH) {         // check if the input is HIGH (button released)
    Serial.print("Val P1 : ");
    Serial.println(checkP1);
    digitalWrite(ledPin,HIGH);  // turn LED ON
    checksum = true;
    delay(500);
    //checksum = true;
  } else {
    digitalWrite(ledPin, LOW);  // turn LED OFF
    Serial.print("Val P1 : ");
    Serial.println(checkP1);
    if(checksum){  
      if(sum<MAX){
          sum++;               
          //checksum=false;
        }
      checksum=false;      
    }  
  }    
  if (checkP2 == HIGH) {         // check if the input is HIGH (button released)
    Serial.print("Val P2 : ");
    Serial.println(checkP2);
    digitalWrite(ledPin,HIGH);  // turn LED ON
    checksum = true;
    delay(500);
    //checksum = true;
  } else {
    digitalWrite(ledPin, LOW);  // turn LED OFF
    Serial.print("Val P2 : ");
    Serial.println(checkP2);
    if(checksum){    
      if(sum>MIN){
        sum--;
        //checksum=false;
        }
      checksum=false;
    }        
  }
Serial.print("sumary:");
Serial.println(sum);    
//if(sum==2)
  //Serial.print("-------Menu  List-------");
if(sum==1){
          MenuList_1();
          /*lcd.print("-----Menu  List-----");
          lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
          lcd.print("- 1.Setting Working");
          lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
          lcd.print("2.Choose chemical");
          lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
          lcd.print("3.Exit");
          lcd.setCursor(0, 4); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor */
            }else{
              if(sum==2){
                MenuList_2();
                /*lcd.print("-----Menu  List-----");
                lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
                lcd.print("1.Setting Working");
                lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
                lcd.print("- 2.Choose chemical");
                lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
                lcd.print("3.Exit");
                lcd.setCursor(0, 4); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor*/ 
                  }else{
                    if(sum==3){
                      MenuList_3();
                      /*lcd.print("-----Menu  List-----");
                      lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
                      lcd.print("1.Setting Working");
                      lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
                      lcd.print("2.Choose chemical");
                      lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
                      lcd.print("- 3.Exit");
                      lcd.setCursor(0, 4); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor*/ 
                      }
                 }
            } 
//delay(1000);    

}

void MenuList_1(){
          lcd.print("-----Menu  List-----");
          lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
          lcd.print("- 1.Setting Working");
          lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
          lcd.print("2.Choose chemical");
          lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
          lcd.print("3.Exit");
          lcd.setCursor(0, 4); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor 
  }
void MenuList_2(){
         lcd.print("-----Menu  List-----");
         lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
         lcd.print("1.Setting Working");
         lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
         lcd.print("- 2.Choose chemical");
         lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
         lcd.print("3.Exit");
         lcd.setCursor(0, 4); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor 
  }
void MenuList_3(){
          lcd.print("-----Menu  List-----");
          lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
          lcd.print("1.Setting Working");
          lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
          lcd.print("2.Choose chemical");
          lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
          lcd.print("- 3.Exit");
          lcd.setCursor(0, 4); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor 
  }

