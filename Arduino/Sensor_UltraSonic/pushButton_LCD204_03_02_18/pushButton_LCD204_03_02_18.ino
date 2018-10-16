#include <Wire.h> 
#include <LiquidCrystal_I2C.h> //ประกาศ Library ของจอ I2C

LiquidCrystal_I2C lcd(0x3F, 20, 4);// Set the LCD address to 0x3F for a 20 chars and 4 line display

#define MAX 4 
#define MIN 1 
int ledPin = 7; // choose the pin for the LED
int buttonPin = 6;   // choose the input pin (for a pushbutton) 
int buttonPin2 = 5;   // choose the input pin (for a pushbutton)
int buttonEnterPin = 4;   // choose the input pin (for a pushbutton)
int checkP1,checkP2,enter = 0;     // variable for reading the pin status
int sum = 1;
int index = 1;
int menuchem=1;
bool checksum;

int TricRelay = 4;
float mval = 0.28;
float sgval = 0.0;
float boronval = 0.0;
const int TricPin = 13;//Tric
      int EchoPin = 12;//Echo
      double duration, cm,cm2,cm3,cmavg;
/*bool isInStage_choose_chemecals ;
enum Stage {
  none,
  display_sg,
  display_times,
  choose_chemecals
};
Stage curStage ;*/

void setup() {
  setupPin();  
}

void loop(){    
  digitalPin();
  readDistance();

  if (checkP1 == HIGH) {         // check if the input is HIGH (button released)
    Serial.print("Val P1 : ");
    Serial.println(checkP1);
    digitalWrite(ledPin,HIGH);  // turn LED ON
    checksum = true;
    delay(50);
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
    delay(50);
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
    if(enter == HIGH){
    Serial.print("enter : ");
      Serial.println(enter);
      delay(50);
    }       
  }
Serial.print("sumary:");
Serial.println(sum);
   Mainmenu();
   delay(2000); 
   
  /*if(sum==1){
    MenuList_1();
    }else if(sum==2){
     MenuList_2(); 
      }else if(sum==3){
        MenuList_3();
        }else if(sum==4){
          MenuList_4();
          }*/
    
    /*if(enter == HIGH){
      Serial.print("enter : ");
      Serial.println(enter);
      checksum = true;
      delay(50);
      switch(sum){
        case 1:
        while(1){
        if(sum==1){
                lcd.clear();
                sum = 0;
                } 
                  
                  }
                  
              break;   
        case 2:
              if(sum==2){
                lcd.clear();
                sum = 0;
                }
                //MenuChemicalList_1();              
              break;
        case 3:
              break;
        }
      }*/
}

void MenuList_1(){          
          lcd.print("--Choose  Chemical--");
          lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor  
          lcd.print("- 1.Chemical A 0%");
          lcd.print(""); 
          lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor  
          lcd.print("2.Chemical A 1%");
          lcd.print("  ");
          lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor 
          lcd.print("3.Chemical B 0%");
          lcd.print("  ");
          lcd.setCursor(0, 4); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
  }  
void MenuList_2(){          
          lcd.print("--Choose  Chemical--");
          lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
          lcd.print("1.Chemical A 0%");
          lcd.print("  ");
          lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
          lcd.print("- 2.Chemical A 1%");
          lcd.print("");
          lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
          lcd.print("3.Chemical B 0%");
          lcd.print("  ");
          lcd.setCursor(0, 4); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor 
  }
void MenuList_3(){         
         lcd.print("--Choose  Chemical--");
         lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
         lcd.print("1.Chemical A 0%");
         lcd.print("  ");
         lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
         lcd.print("2.Chemical A 1%");
         lcd.print("  ");
         lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
         lcd.print("- 3.Chemical B 0%");
         lcd.print("");
         lcd.setCursor(0, 4); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
  }
void MenuList_4(){          
         lcd.print("--Choose  Chemical--");
         lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
         lcd.print("2.Chemical A 1%");
         lcd.print("  ");
         lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
         lcd.print("3.Chemical B 1%");
         lcd.print("  ");
         lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
         lcd.print("- 4.Chemical B 1%");
         lcd.print("");
         lcd.setCursor(0, 4); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor 
  }
void MenuChemicalList_1(){
          lcd.print("---Chemical  List---");
          lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
          lcd.print("- 1.Chemical A");
          lcd.print("");
          lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
          lcd.print("2.Chemical B");
          lcd.print("  ");
          lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
          lcd.print("3.Chemical C");
          lcd.print("  ");
          lcd.setCursor(0, 4); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor 
  }
void MenuChemicalList_2(){
          lcd.print("---Chemical  List---");
          lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
          lcd.print("1.Chemical A");
          lcd.print("  ");
          lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
          lcd.print("- 2.Chemical B");
          lcd.print("");
          lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
          lcd.print("3.Chemical C");
          lcd.print("  ");
          lcd.setCursor(0, 4); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor 
  }
void MenuChemicalList_3(){
          lcd.print("---Chemical  List---");
          lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
          lcd.print("1.Chemical A");
          lcd.print("  ");
          lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
          lcd.print("2.Chemical B");
          lcd.print("  ");
          lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
          lcd.print("- 3.Exit");
          lcd.print("");
          lcd.setCursor(0, 4); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor 
  }
void Mainmenu(){       
          lcd.print("--Specific gravity--");
          lcd.print("");
          lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor  
          lcd.print("SG : ");
          lcd.print(sgval);
          lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor  
          lcd.print("% Boron : ");
          lcd.print(boronval);
          lcd.print(" %");
          lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor           
          if(sgval>=3.01){
            digitalWrite(TricRelay, HIGH);
            lcd.print("Solenoid valve Open");
            lcd.print(" ");
            lcd.setCursor(0, 4); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
             }else{
                digitalWrite(TricRelay, LOW);
                lcd.print("Solenoid valve Close");
                lcd.print(" ");
                lcd.setCursor(0, 4); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
                 }
  }
void setupPin(){
  lcd.begin();
  //curStage = none ;
  pinMode(ledPin, OUTPUT);  // declare LED as output
  //pinMode(ledPin2, OUTPUT);  // declare LED as output
  //pinMode(ledPin3, OUTPUT);  // declare LED as output
  pinMode(buttonPin, INPUT);    // declare pushbutton as input
  pinMode(buttonPin2, INPUT);    // declare pushbutton as input
  pinMode(buttonEnterPin, INPUT);    // declare pushbutton as input
  Serial.begin(9600);
  checksum = false;  
  }
void digitalPin(){
  checkP1 = digitalRead(buttonPin);  // read input value
  checkP2 = digitalRead(buttonPin2);  // read input value
  enter = digitalRead(buttonEnterPin);  // read input value 
  }
void readDistance(){
  pinMode(TricRelay, OUTPUT);  // Tric Relay output
  pinMode(TricPin, OUTPUT);          
  digitalWrite(TricPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TricPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(TricPin, LOW);
  pinMode(EchoPin, INPUT);
  duration = pulseIn(EchoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  cm2 = microsecondsToCentimeters(duration);
  cm3 = microsecondsToCentimeters(duration);
  cmavg = (cm+cm2+cm3) / 3;//ค่าสมมุติ
  sgval = (mval*cmavg)+(1*0.1);//ค่าสมมุติ
  boronval = (sgval*mval)+(1*0.1);//ค่าสมมุติ
  //isInStage_choose_chemecals = false ;
  }
double microsecondsToCentimeters(double microseconds){
      // The speed of sound is 340 m/s or 58 microseconds per centimeter.
      // The ping travels out and back, so to find the distance of the
      // object we take half of the distance travelled.
      return microseconds / 58;
    }
