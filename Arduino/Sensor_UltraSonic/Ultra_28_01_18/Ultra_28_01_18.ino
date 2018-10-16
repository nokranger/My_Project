const int TricPin = 13;//Tric
    int EchoPin = 12;//Echo
    void setup() {
      Serial.begin(9600);
    }     
void loop()
    {
      double duration, cm;
     
      pinMode(TricPin, OUTPUT);    
      
      digitalWrite(TricPin, LOW);
      delayMicroseconds(2);
      digitalWrite(TricPin, HIGH);
      delayMicroseconds(5);
      digitalWrite(TricPin, LOW);
      pinMode(EchoPin, INPUT);
      duration = pulseIn(EchoPin, HIGH);

      cm = microsecondsToCentimeters(duration);

      Serial.print(cm);
      Serial.print("cm");
      Serial.println();     
      delay(1000);
    }     
    double microsecondsToCentimeters(double microseconds)
    {
      // The speed of sound is 340 m/s or 29 microseconds per centimeter.
      // The ping travels out and back, so to find the distance of the
      // object we take half of the distance travelled.
      return microseconds / 58;
    }
