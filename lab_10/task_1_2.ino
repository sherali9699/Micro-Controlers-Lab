#include <Servo.h>
Servo myservo;  //Creating a Servo Object
int pos = 0;    //Position of Servo
const int servoPin = 26; //Pin at PD3

//Define the RGB pins
const int red = 30;     //Present at PF1
const int green = 40;   //Present at PF2
const int blue = 39;    //Present at PF3

int colorDetect=0;     //For different color detection
char received;         //Characters to be send/receieve on UART
 
void setup(){
  //Initialize Baud Rate at 9600 below 
  Serial.begin(9600);
  //Specify pin modes for red, green and blue pins below
  pinMode(red, OUTPUT);   //Red color pwm pin defined as output
  pinMode(green, OUTPUT); //Green color pwm pin defined as output
  pinMode(blue, OUTPUT);  //Blue color pwm pin defined as output
  
  //We use analogWrite() to control PWM at each pin PF1, PF2 and PF3
  //There differnt combination would generate different colors for value between 0-255
  //Starting with no color on RGB LEDs
  analogWrite(red,0);
  analogWrite(green,0);
  analogWrite(blue,0);

  //Servo to be connected at PD3
  myservo.attach(servoPin);
 }

 
void loop(){
  //Following Condition is true whenever we send a command from Bluetooth Terminal App
  if(Serial.available()>0){
    
    //Read the bluetoot data and store it in colorDetect variable using Serial.read() command here
    colorDetect = Serial.read();


    //Following lines help debugging by printing whatever character recieved on Serial Monitor
    char Rec = char(colorDetect);
    if (Rec != '0')
    {
    Serial.println(Rec); //This is to visualise the received character on the serial monitor
    }  
  }

  //Following function should take character received on bluetooth as argument and should correspondingly change servo position and RGB color
  chooseColor(colorDetect);
}





void chooseColor(char color){
  //Check condition for character stored in "color" and perform your task 02 here


  //You can use values from below in order to obtain various colors from your LED
  //LEDs off
//    analogWrite(red,0);
//    analogWrite(green,0);
//    analogWrite(blue,0);

  //White
  if (color == 'D'){
    analogWrite(red,255);
    analogWrite(green,255);
    analogWrite(blue,255);

    myservo.write(180);              // tell servo to go to position  
    delay(5);                        // waits 5ms for the servo to reach the position 
  }
  //Red
  else if (color == 'A'){
    analogWrite(red,255);
    analogWrite(green,0);
    analogWrite(blue,0);

    myservo.write(45);              // tell servo to go to position  
    delay(5);                        // waits 5ms for the servo to reach the position 
  }
  //Green
  else if (color == 'B'){
    analogWrite(red,0);
    analogWrite(green,255);
    analogWrite(blue,0);

    myservo.write(90);              // tell servo to go to position  
    delay(5);                        // waits 5ms for the servo to reach the position 
  }
  //  Blue
  else if (color == 'C'){
    analogWrite(red,0);
    analogWrite(green,0);
    analogWrite(blue,255);

    myservo.write(135);              // tell servo to go to position  
    delay(5);                        // waits 5ms for the servo to reach the position 
  }
  //Orange
//    analogWrite(red,255);
//    analogWrite(green,153);
//    analogWrite(blue,0);

  //Violet
//    analogWrite(red,102);
//    analogWrite(green,0);
//    analogWrite(blue,153);

  //Cyan
//    analogWrite(red,0);
//    analogWrite(green,255);
//    analogWrite(blue,255);

  //Yellow 
//    analogWrite(red,255);
//    analogWrite(green,204);
//    analogWrite(blue,0);
}
