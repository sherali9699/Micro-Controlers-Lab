//Libraries for I2C communicaiton and Servo below
#include <Wire.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

void setup() {
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onReceive(receiveEvent); // register event, function to be called whenever master call for transmission
  
  Serial.begin(9600);           // start serial for output
  myservo.attach(9);            // attaches the servo on pin 9 to the servo object
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {

  //Below loop is used to read the strings, that is recieved as consecutive characters
  while (1 < Wire.available()) {  // loop through all but the last
    char c = Wire.read();         // receive byte as a character 
    Serial.print(c);             // print character (addedd while doing task 1)
  }

  //Read the integer received below
  int x = Wire.read();        // receive byte as an integer
  myservo.write(x);           //Write the servo position or degree

  Serial.print("The angle received is: ");          // added this line while doing task 1
  Serial.println(x);          // added this line while doing task 1
}
