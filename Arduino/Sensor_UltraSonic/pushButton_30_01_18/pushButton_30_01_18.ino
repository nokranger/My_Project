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
int ledPin = 8; // choose the pin for the LED
//int ledPin2 = 9; // choose the pin for the LED
//int ledPin3 = 10; // choose the pin for the LED
int buttonPin = 6;   // choose the input pin (for a pushbutton) 
int buttonPin2 = 7;   // choose the input pin (for a pushbutton)
int buttonEnterPin = 5;   // choose the input pin (for a pushbutton)
int val = 0;     // variable for reading the pin status
int val2=0;
int enter;
int sum = 1;
bool checksum;
bool isInStage_choose_chemecals ;
enum Stage {
  none,
  display_sg,
  display_times,
  choose_chemecals
};
Stage curStage ;

void setup() {
  curStage = none ;
  pinMode(ledPin, OUTPUT);  // declare LED as output
  //pinMode(ledPin2, OUTPUT);  // declare LED as output
  //pinMode(ledPin3, OUTPUT);  // declare LED as output
  pinMode(buttonPin, INPUT);    // declare pushbutton as input
  pinMode(buttonPin2, INPUT);    // declare pushbutton as input
  Serial.begin(9600);
  checksum = false;
  isInStage_choose_chemecals = false ;
}

void loop(){
  
  val = digitalRead(buttonPin);  // read input value
  val2 = digitalRead(buttonPin2);  // read input value
  enter = digitalRead(buttonEnterPin);  // read input value
  
  if (val == HIGH) {         // check if the input is HIGH (button released)
    digitalWrite(ledPin,HIGH);  // turn LED ON
    //digitalWrite(ledPin3,LOW);  // turn LED ON
    checksum = true;
    delay(500);
    /*digitalWrite(ledPin2,HIGH);  // turn LED ON
    digitalWrite(ledPin, LOW);  // turn LED OFF
    digitalWrite(ledPin3,LOW);  // turn LED ON
    delay(500);
    digitalWrite(ledPin3,HIGH);  // turn LED ON
    digitalWrite(ledPin2, LOW);  // turn LED OFF
    digitalWrite(ledPin,LOW);  // turn LED ON
    delay(500);*/
  } else {
    digitalWrite(ledPin, LOW);  // turn LED OFF
    //digitalWrite(ledPin2,LOW);  // turn LED ON
    //digitalWrite(ledPin3,LOW);  // turn LED ON
    if(checksum){
      
      if(sum<MAX){
          sum++;
          //checksum=false;
        }
      checksum=false;
    }
    
    
  }
  if (val2 == HIGH) {         // check if the input is HIGH (button released)
    digitalWrite(ledPin,HIGH);  // turn LED ON
    //digitalWrite(ledPin2,LOW);  // turn LED ON
    //digitalWrite(ledPin3,LOW);  // turn LED ON
    checksum = true;
    delay(500);
    /*digitalWrite(ledPin2,HIGH);  // turn LED ON
    digitalWrite(ledPin, LOW);  // turn LED OFF
    digitalWrite(ledPin3,LOW);  // turn LED ON
    delay(500);
    digitalWrite(ledPin,HIGH);  // turn LED ON
    digitalWrite(ledPin2, LOW);  // turn LED OFF
    digitalWrite(ledPin3,LOW);  // turn LED ON
    delay(500);*/
  } else {
    digitalWrite(ledPin, LOW);  // turn LED OFF
    //digitalWrite(ledPin2,LOW);  // turn LED ON
    //digitalWrite(ledPin3,LOW);  // turn LED ON
    if(checksum){
      
      if(sum>MIN){
        sum--;
        //checksum=false;
        }
      checksum=false;
    }
    
    
  }

  
  if(enter == HIGH){
     
         
        

         switch(sum){
             case 1 :
              curStage = display_sg ;
              break ;
            case 2 :
              curStage = display_times ;
              break ;
            case 3 :
              curStage = choose_chemecals ;
              isInStage_choose_chemecals = true ;
              break ;
        }

  }

  if(curStage==display_sg){
    Serial.print("Stage = ");
    Serial.println("sg=00.00");
  }else if(curStage==display_times){
    Serial.print("Stage = ");
    Serial.println("wp=1h2m26s");
  }else if(curStage==choose_chemecals){
    Serial.print("Stage = ");
    Serial.println("1. aaa");
    Serial.println("2. aaa");
    Serial.println("3. aaa");
    Serial.println();
  }

    if(sum==1){
      Serial.print("Stage = ");
      Serial.println("sg=00.00");
    }else if(sum==2){
      Serial.print("Stage = ");
      Serial.println("wp=1h2m26s");
    }else if(sum==3){
      Serial.print("Stage = ");
      Serial.println("1. aaa");
      Serial.println("2. aaa");
      Serial.println("3. aaa");
      Serial.println();
    }
  }


