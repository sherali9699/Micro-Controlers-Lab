////////////////////////////////////////////////////
//Ultrasonic Pins Definition, here we specify pin usage for our tivaC Board

const int echo = 9, Trig = 10;  //Pin connections for HC-SR04
const int LED1 = 12;          //Specify Pin for LED1
const int LED2 = 13;
const int LED3 = 11;
const int SW1 = 31;
const int SW2 = 17;

////////////////////////////////////////////////////
//Time Update Variables

long duration, cm;                          //To measure pulse width and distance in cm
long distance = 0;                          //To return distance of object
unsigned long LastUpdateMicrosecs = 0;    
unsigned long LastUpdateMillisecs = 0;
unsigned long CurrentMicrosecs = 0;
unsigned long MicrosecsSinceLastUpdate = 0;
float SecondsSinceLastUpdate = 0;
bool sw1_pressed = false;
bool sw2_pressed = false;
////////////////////////////////////////////////////
//Initializing Pins Function

void setup()
{
  Serial.begin(115200);     //Initialize Serial COM Port with 115200 buad rate
  pinMode(Trig, OUTPUT);    //Trigger is output since it will send 8 pulses at 40KHz from HC-SR04
  pinMode(echo, INPUT);     //Echo is input since it will detect the reflected wave from HC-SR04
  pinMode(LED1, OUTPUT);    //Pin for LED1 should output HIGH(on) or LOW(off)
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
}



////////////////////////////////////////////////////
//Main Loop that will keep on running, it is similar to int main()
void loop()
{
    int switch1 = digitalRead(SW1);
    int switch2 = digitalRead(SW2);
    

    if ((!sw1_pressed) && (!switch1)){
      sw1_pressed = true;
      sw2_pressed = false;
      Serial.print("SW1 Pressed\n");
    }

    if ((!sw2_pressed) && (!switch2)){
      sw1_pressed = false;
      sw2_pressed = true;      
      Serial.print("SW2 Pressed\n");
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
    }    

    if (sw1_pressed) {    
      Update_Ultra_Sonic(); //This function operates HC-SR04
      delay(10);           //Delay between prints on Serial Monitor
     }
}

////////////////////////////////////////////////////
//Will update ultrasonic sensors through Serial port

void Update_Ultra_Sonic()
{
  //Setting Trig Signal HIGH for 10us to produce burst of 8 pulses at 40KHz
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  //digitalRead(anypin/switch) //Use this function to read the state of any Pin/Switch i.e. SW1 and SW2


//  duration = pulseIn(echo, HIGH);   // Reads duration (microseconds) for which Echo pin reads HIGH till wave is reflected
//  cm = microsecondsToCentimeters(duration); // convert the time into a distance, refer to function below
  cm = 0;
  for (int i = 0; i < 10; i++) {
    duration = pulseIn(echo, HIGH);
    cm += microsecondsToCentimeters(duration);
  }

  cm = cm / 10;

  if ((cm <= 30) && (cm > 15)){
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    Serial.print("LED1 ON\n");
  }
  else if ((cm <= 15) && (cm > 5)){    
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    Serial.print("LED1 and LED2 ON\n");
  }
  else if ((cm <= 5)){    
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    Serial.print("ALL ON\n");
  }
  else if (cm > 100){  
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    delay(100);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    Serial.print("Out of Range\n");
    
  }
  else {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    }
  
  //Sending through serial port to print on Monitor
  Serial.print("Distance=");
  Serial.print("\t");
  Serial.print(cm);
  Serial.print("\n");  
  delay(10); 
}

////////////////////////////////////////////////////
//Conversion of microsecond to centimeter
long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.

// convert speed of sound from m/s to cm/us
// Use the formula:     distance(cm) = speed(cm/us) * time(us)
// Write distance formula here
distance = 0.0343  * microseconds;

// We take half of the distance travelled since its a reflected wave
return distance / 2;
}
