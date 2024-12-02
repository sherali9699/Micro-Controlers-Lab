// Motor A, TivaC and L298N connections
int enA = 7;   //ENABLE pin (PD3) for Motor A to provide PWM 
int in1 = 11;   //IN1 pin (PA2) for Motor A for direction
int in2 = 12;   //IN2 pin (PA3) for Motor A for direction
const int SW2 = 17;   //Pin number for Switch SW2
bool direction = true;  //Flag for clockwise or anti-clockwise direction


void setup() {
  Serial.begin(115200); //Serial initializing for Debugging
  
  //Specify pinModes for enA, in1 and in2 below
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  //Initialize SW2 Switch as Input
  pinMode(SW2, INPUT_PULLUP);  //State for SW2 with pullUp resistor
}

void loop() {
    // Make the motor run clockwise direction using in1 and in2 states below

    changeDirection();
  
    //Varying Speed for motor below with delay of 2 seconds
    analogWrite(enA, 0);
    changeDirection();
    Serial.print("0 Speed\n");
    delay(2000);
    analogWrite(enA, 64);
    changeDirection();
    Serial.print("25% Speed\n");
    changeDirection();
    delay(2000);
    analogWrite(enA, 191);
    changeDirection();
    Serial.print("75% Speed\n");
    delay(2000);
    analogWrite(enA, 255);
    changeDirection();
    Serial.print("100% Speed\n");
    delay(2000);
}

void tenP_Speed() {
    //Generates PWM of 50Hz (20ms total) with Duty Cycle of 10%
    for (int i=0; i<50; i++){
      digitalWrite(enA, HIGH);
      delayMicroseconds(10000); // High for 2ms, Duty Cycle of 10%
      digitalWrite(enA, LOW);
      delayMicroseconds(10000); // Off for remaining  18ms
  }
}

void zeroP_Speed() {
    //Generates PWM of 50Hz (20ms total) with Duty Cycle of 0%
    for (int i=0; i<50; i++){
      digitalWrite(enA, LOW);
      delayMicroseconds(20000); // Off for remaining  18ms
  }
}

void medP_Speed() {
    //Generates PWM of 50Hz (20ms total) with Duty Cycle of 25%
    for (int i=0; i<50; i++){
      digitalWrite(enA, HIGH);
      delayMicroseconds(5000); // High for 2ms, Duty Cycle of 25%
      digitalWrite(enA, LOW);
      delayMicroseconds(15000); // Off for remaining  ms
  }
}

void highP_Speed() {
    //Generates PWM of 50Hz (20ms total) with Duty Cycle of 75%
    for (int i=0; i<50; i++){
      digitalWrite(enA, HIGH);
      delayMicroseconds(15000); // High for 2ms, Duty Cycle of 75%
      digitalWrite(enA, LOW);
      delayMicroseconds(5000); // Off for remaining  
  }
}

void fullP_Speed() {
    //Generates PWM of 50Hz (20ms total) with Duty Cycle of 100%
    for (int i=0; i<50; i++){
      digitalWrite(enA, HIGH);
      delayMicroseconds(20000); // High for 2ms, Duty Cycle of 100%
  }
}


void changeDirection(){
  //To be used for task03 only
    if(digitalRead(SW2) == 0){
      direction = !direction;
    }
    if (direction == false){
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH); 
    } else {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    }
    delay(1000);  
}
