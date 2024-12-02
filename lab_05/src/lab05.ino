//Below lines are used for Task02 and Task03
#include <Servo.h>   //Using built-in servo library with precise PWMs, for Task02/03
Servo myservo;       //Creates an object of Servo, for Task02/03
 
//Variables for pins and servo position "pos"
int pos = 0;                        // variable to store the servo position in
const int Servo_control_pin = 30;   //Pin connection for Servo PWM, equivalent to PF1

const int echo = 9, Trig = 10;      //Pin connections for HC-SR04 ultrasonic, for Task02/03
const int SW2 = 17;                 //Pin number for Switch SW2, for Task02

////////////////////////////////////////////////////
//Time Update Variables for Ultrasonic Sensor, for Task03
long duration, cm;          //To measure pulse width and distance in cm, for task 03
long distance = 0;          //To return distance of object, for task 03

////////////////////////////////////////////////////
void setup() 
{ 
  //Initialize Serial port at 115200 Baud rate here as per previous labs
  //Initialize pin modes for Trig, Echo and SW2 here as INPUT/OUTPUT as per previous labs

  //Use this for Task01
//  pinMode(Servo_control_pin, OUTPUT);    //To produce PWM signal at PF1 pin for servo control without library

  //Use this for Task02/03, comment out above one
  myservo.attach(Servo_control_pin);   //Attaches the servo PWM pin on PF1 (30) using library
  pinMode(SW2, INPUT_PULLUP);  

  Serial.begin(115200);     //Initialize Serial COM Port with 115200 buad rate
  pinMode(Trig, OUTPUT);    //Trigger is output since it will send 8 pulses at 40KHz from HC-SR04
  pinMode(echo, INPUT);
} 

////////////////////////////////////////////////////
void loop() 
{ 
    //Task 01: PWM Gernation using delay functions
    //Go through servo_0_Degree(), complete servo_p90_Degree() and servo_m90_Degree() logic
    
     /*
    servo_0_Degree();
    delay(1000);
    servo_p90_Degree();
    delay(1000);
    servo_0_Degree();
    delay(1000);
    servo_m90_Degree();
    delay(1000);
    */



    //Task 02: Using <servo.h> library to control angular position and add SW2

//    if (digitalRead(SW2) == 0){
//      delay(5);
//    
//      //Loop here that make servo goes from 0 degrees to 180 degrees 
//      for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
//      {                                  // in steps of 1 degree 
//        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
//        delay(5);                        // waits 5ms for the servo to reach the position 
//      } 
//
//      //Write a Loop here that make servo goes from 180 degrees to 0 degrees
//
//      for(pos = 180; pos > 0; pos -= 1)  // goes from 180 degrees to 0 degrees 
//      {                                  // in steps of 1 degree 
//        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
//        delay(5);                        // waits 5ms for the servo to reach the position 
//      } 
//      }
    

    

    //Task 03: Interfacing servo with ultrasonic sensor
    
    Update_Ultra_Sonic(); //Update distance from ultrasonic sensor
    delay(500);

    //Write your logic for task03 here, use "cm" to read distance

    
} 


////////////////////////////////////////////////////
void servo_0_Degree(){
    //We use delayMicroseconds() instead of delay(ms)... 
    //...since delayMicroseconds() are more precise and give accurate PWM
    
    // Rotates servo to 0 degree, total pulse duration is 20ms
    digitalWrite(Servo_control_pin, HIGH);
    delayMicroseconds(1500); // High for 1.5ms, Duty Cycle of 7.5%
    digitalWrite(Servo_control_pin, LOW);
    delayMicroseconds(18500); // Off for remaining  18.5ms
}

void servo_p90_Degree(){
    // Rotates servo to +90 degree, total pulse duration is 20ms
    // Write your logic here for getting +90 degrees

    digitalWrite(Servo_control_pin, HIGH);
    delayMicroseconds(2000); // High for 2.0ms, Duty Cycle of 10.0%
    digitalWrite(Servo_control_pin, LOW);
    delayMicroseconds(18000); // Off for remaining  18.0ms
}

void servo_m90_Degree(){
    // Rotates servo to -90 degree, total pulse duration is 20ms
    // Write your logic here for getting -90 degrees

    digitalWrite(Servo_control_pin, HIGH);
    delayMicroseconds(1000); // High for 1.0ms, Duty Cycle of 5.0%
    digitalWrite(Servo_control_pin, LOW);
    delayMicroseconds(19000); // Off for remaining  19.0ms
}


////////////////////////////////////////////////////
/////////DON'T CHANGE THE BELOW FUNCTIONS///////////
////////////////////////////////////////////////////

void Update_Ultra_Sonic()
{
  //Setting Trig Signal HIGH for 10us to produce burst of 8 pulses at 40KHz
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  duration = pulseIn(echo, HIGH);   // Reads duration (microseconds) for which Echo pin reads HIGH till wave is reflected
  cm = microsecondsToCentimeters(duration); // convert the time into a distance, refer to function below
  
  //Sending through serial port to print on Monitor
  Serial.print("Distance=");
  Serial.print("\t");
  Serial.print(cm); 
  Serial.print(" cm");
  Serial.print("\n");

  if (cm >=0 && cm < 15){
        myservo.write(45); 
        delay(5);
    }
    else if (cm >= 15 && cm < 30) {
        myservo.write(90); 
        delay(5);
    }
    else if (cm >= 30 && cm < 45) {
        myservo.write(180); 
        delay(5);
    }
    else {
        myservo.write(0); 
        delay(5);
    }
}

////////////////////////////////////////////////////
long microsecondsToCentimeters(long microseconds)
{
  //Gives the distance equivalent to time taken by pulse, speed of sound 340m/s
  distance = 0.034 * microseconds;
  return distance / 2;
}
