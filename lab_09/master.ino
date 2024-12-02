//Wire library used for I2C Communication
#include <Wire.h>

//Pin Declaration for Joystick
const int SW_pin = 26; //Connected to digital pin PD3
const int X_pin = 29;  //X potentiometer connected to PE3
const int Y_pin = 28;  //X potentiometer connected to PE2

//JoyStick position tracking variables
int x_pos = 0;    //X-coorindate for joystick
int y_pos = 0;    //Y-coorindate for joystick
byte x = 0;

void setup()
{
  //Initializing the I2C Communication below
  Wire.begin(); // join i2c bus (address optional for master)

  //Initialize Serial communicaiton below at baud rate of 9600 below
  Serial.begin(9600);

  //Declare pin modes for X_pin, Y_pin and SW_pin below
  pinMode(X_pin, INPUT);
  pinMode(Y_pin, INPUT);
  pinMode(SW_pin, INPUT_PULLUP);

}

void loop()
{
  // Uncomment for task 02
  x_pos =  analogRead(X_pin);
  y_pos =  analogRead(Y_pin);
  
  readJoystick();
  
  //If condition for first quadrant satisfied
  //    then call firstQuadrant()

  if ((x_pos >= 0 && x_pos < 2048) && (y_pos >= 2048)) {
     firstQuadrant();  
  }
  else if ((x_pos >= 2048 && x_pos <= 4096) && (y_pos >= 2048)) {
     secondQuadrant();  
  }
  else if ((x_pos >= 2048 && x_pos <= 4096) && (y_pos < 2048)) {
     thirdQuadrant();  
  }
  else if ((x_pos >= 0 && x_pos < 2048) && (y_pos < 2048)) {
     fourthQuadrant();  
  }
//  sendString();
  delay(500);
}

void sendString(){
  //Use this for Task 01
  Wire.beginTransmission(2);  // transmit to device #2
  Wire.write("HELLO WORLD ");      // sends consecutive bytes for each character
  Wire.endTransmission();     // stop transmitting
}

void sendInteger(){
  //Use this for Task 01
  Wire.beginTransmission(2);  // transmit to device #2
  Wire.write(0);              // sends six bytes
  Wire.endTransmission();     // stop transmitting
}

void firstQuadrant(){
  //Use this for Task 02
  //send command for 45 degree roation from here
  Wire.beginTransmission(2);  // transmit to device #2
  Wire.write(45);              // sends six bytes
  Wire.endTransmission();     // stop transmitting
}

void secondQuadrant(){
  //Use this for Task 02
  //send command for 90 degree roation from here
  Wire.beginTransmission(2);  // transmit to device #2
  Wire.write(90);              // sends six bytes
  Wire.endTransmission();     // stop transmitting
}

void thirdQuadrant(){
  //Use this for Task 02
  //send command for 90 degree roation from here
  Wire.beginTransmission(2);  // transmit to device #2
  Wire.write(135);              // sends six bytes
  Wire.endTransmission();     // stop transmitting
}

void fourthQuadrant(){
  //Use this for Task 02
  //send command for 90 degree roation from here
  Wire.beginTransmission(2);  // transmit to device #2
  Wire.write(180);              // sends six bytes
  Wire.endTransmission();     // stop transmitting
}


void readJoystick(){
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");
}
