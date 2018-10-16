#include <Wire.h> 
#include <LiquidCrystal_I2C.h> //ประกาศ Library ของจอ I2C
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 20, 4);
int val = 5;
int TricRelay = 4;
float mval = 0.28;
float sgval = 0.0;
float baronval = 0.0;
const int TricPin = 13;//Tric
      int EchoPin = 12;//Echo
      double duration, cm;
void setup()
{
  
}
void loop() 
{
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
      sgval = (mval*cm)+(1*0.1);
      baronval = (sgval*mval)+(1*0.1);
      
// initialize the LCD
lcd.begin();
lcd.print("Specific gravity");
lcd.setCursor(0, 1); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor    
// Print a message to the LCD.
//lcd.print("Hello !!!"); //ฟังก์ชั่นในการกำหนดข้อความที่ต้องการแสดงผล
/*lcd.print("RANGE : ");
lcd.print(cm);
lcd.print(" cm");*/
lcd.print("SG : ");
lcd.print(sgval);

lcd.setCursor(0, 2); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor  
lcd.print("% Baron : ");
lcd.print(baronval);
lcd.print(" %");
//lcd.print(" %BR : ");
//lcd.print(baronval);
lcd.setCursor(0, 3); //ฟังก์ชั่นในการกำหนดตำแหน่ง Cursor
if(sgval>=3.01){
  digitalWrite(TricRelay, HIGH);
  lcd.print("Solenoid valve Open");
  }else{
    digitalWrite(TricRelay, LOW);
  lcd.print("Solenoid valve Close");
    }  
delay(100);
}
double microsecondsToCentimeters(double microseconds)
    {
      // The speed of sound is 340 m/s or 58 microseconds per centimeter.
      // The ping travels out and back, so to find the distance of the
      // object we take half of the distance travelled.
      return microseconds / 58;
    }
