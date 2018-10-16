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
bool checkleft,checkright,checkup,checkdown,checkselect;
float L1 = 15.00;//ระยะปากกระบอกถึงรู
float L2 = 5.00;//ระยะสะท้อนถึงจุด 0 
float Ds, cm,cm2,cm3,cm4,cm5,cmavg = 0.00; //ระยะที่เราต้องการ

const byte NONE = 0;
const byte LEFT = 1;
const byte UP = 2;
const byte RIGHT = 3;
const byte DOWN = 4;
const byte SELECT = 5;

const byte keypadPin = A3;
byte key = 0;

int TricRelay = 4;
float mval = 0.28;
float sgval = 0.0;
float boronval = 0.0;
const int TricPin = 13;//Tric
const int EchoPin = 12;//Echo
double duration;
void setup() {
  setupPin();
  loadingLCD();
  mainMenuList();    
}

void loop(){    
  readDistance();
  //key = getKey();
  pushKey();
delay(100);  
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

  Serial.begin(9600);
  while (!Serial) { ; }
  Serial.println(F("Start\n"));
  pinMode(keypadPin, INPUT_PULLUP);// sets analog pin for input
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
  //isInStage_choose_chemecals = false ;
  }
void pushKey(){
  //CalculateSG();
  key = getKey();
  if(key==LEFT){
    lcd.clear();
    Serial.println("LEFT");
    checkleft = true;
    checkselect = false;
    checkup = false;
    checkdown = false;
    checkright = false;
    }else if(checkleft){
      Workmenu_A0();
      delay(500);
      } 
      if(key==SELECT){
        lcd.clear();
        Serial.println("SELECT");
        checkleft = false;
        checkselect = true;
        checkup = false;
        checkdown = false;
        checkright = false;
        }else if(checkselect){
          mainMenuList();
          delay(500);                    
          }
          if(key==RIGHT){
            lcd.clear();
            Serial.println("RIGHT");
            checkleft = false;
            checkselect = false;
            checkup = false;
            checkdown = false;
            checkright = true;                      
            }else if(checkright){
              Workmenu_B0();
              delay(500);
              }
              if(key==UP){
                lcd.clear();
                Serial.println("UP");
                checkleft = false;
                checkselect = false;
                checkup = true;
                checkdown = false;
                checkright = false;                          
                }else if(checkup){
                  //Workmenu_A1();
                  mainMenuList();
                  delay(500);
                  }
                  if(key==DOWN){
                    lcd.clear();
                    Serial.println("DOWN");
                    checkleft = false;
                    checkselect = false;
                    checkup = false;
                    checkdown = true;
                    checkright = false;
                    }else if(checkdown){
                      Workmenu_B1();
                      delay(500);
                      }
delay(100);
  }
void CalculateSG(){
  readDistance();
  duration = pulseIn(EchoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  delay(50);
  cm2 = microsecondsToCentimeters(duration);
  delay(50);
  cm4 = microsecondsToCentimeters(duration);
  delay(50);
  cm3 = microsecondsToCentimeters(duration);
  delay(50);
  cm5 = microsecondsToCentimeters(duration);
  delay(50);
  cmavg = ((cm+cm2+cm3+cm4+cm5) / 5);//ค่าสมมุติ
  delay(50);
  Ds = (L1 - L2 - cmavg);//สูตรหาระยะที่ต้องการ
  delay(50);
  sgval = (mval*cmavg)+(1*0.1);//ค่าสมมุติ
  boronval = (sgval*mval)+(1*0.1);//ค่าสมมุติ
  }
void Workmenu_A0(){
          CalculateSG();
          lcd.setCursor(0,0); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor         
          lcd.print("  Specific gravity  ");
          //lcd.print("");
          lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor  
          lcd.print("Distance : ");
          //ShowNum(cmavg,3);
          lcd.print(("%.2f",cmavg));
          lcd.print("   ");
          lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor  
          lcd.print("% BoronA 1%: ");
          lcd.print(("%.2f",boronval));
          lcd.print("%");
          lcd.print("  ");
          lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor           
          if(boronval<=1.01){
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
void Workmenu_A1(){
          CalculateSG();
          lcd.setCursor(0,0); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor         
          lcd.print("  Specific gravity  ");
          //lcd.print("");
          lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor  
          lcd.print("Distance : ");
          lcd.print(("%.2f",cmavg));
          lcd.print("   ");          
          lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor  
          lcd.print("% BoronA 1%: ");
          lcd.print(("%.2f",boronval));
          lcd.print("%");
          lcd.print("  ");
          lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor           
          if(boronval<=1.01){
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
void Workmenu_B0(){
          CalculateSG();
          lcd.setCursor(0,0); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor         
          lcd.print("  Specific gravity  ");
          //lcd.print("");
          lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor  
          lcd.print("Distance : ");
          lcd.print(("%.2f",cmavg));
          lcd.print("   ");
          lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor  
          lcd.print("% BoronB 0%: ");
          lcd.print(("%.2f",boronval));
          lcd.print("%");
          lcd.print("  ");
          lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor           
          if(boronval<=1.01){
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
void Workmenu_B1(){
          CalculateSG();
          lcd.setCursor(0,0); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor         
          lcd.print("  Specific gravity  ");
          //lcd.print("");
          lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor  
          lcd.print("Distance : ");
          lcd.print(("%.2f",cmavg));
          lcd.print("   ");
          lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor  
          lcd.print("% BoronB 1%: ");
          lcd.print(("%.2f",boronval));
          lcd.print("%");
          lcd.print("  ");
          lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor           
          if(boronval<=1.01){
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
void mainMenuList(){
          lcd.setCursor(0, 0); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
          lcd.print("1.Chemical A at 0%");
          lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
          lcd.print("2.Chemical A at 1%");
          lcd.print("");
          lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
          lcd.print("3.Chemical B at 0%");
          lcd.print("");
          lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor   
          lcd.print("4.Chemical B at 1%");
          lcd.print("");
          lcd.setCursor(0, 4); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor 
  }

double microsecondsToCentimeters(double microseconds){
      // The speed of sound is 340 m/s or 58 microseconds per centimeter.
      // The ping travels out and back, so to find the distance of the
      // object we take half of the distance travelled.
      return microseconds / 58;
  }

byte getKey(){
int val = 0;
byte button = 0;
val = analogRead(keypadPin);
button = NONE;
if (val <=20) { button = LEFT; }
else if ((val >=100) && (val <=200)){button = UP; }
else if ((val >=300) && (val <=400)){button = DOWN; }
else if ((val >=500) && (val <=600)){button = RIGHT; }
else if ((val >=700) && (val <=800)){button = SELECT; }
return button;
}

void loadingLCD(){
    lcd.setCursor(0,0);
    lcd.print("  Specific gravity  ");
    lcd.setCursor(0,2);  
    lcd.print("Loading ");
    for(int i = 0; i <=9 ; i++){    
    
    lcd.setCursor(9,2);
    lcd.print(11.1*i);
    lcd.print("%");
    //lcd.print(".");
    delay(500);
  }
  lcd.clear();
  }
