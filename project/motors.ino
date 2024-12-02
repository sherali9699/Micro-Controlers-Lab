// Motor A, TivaC and L298N connections
int enA = 40;   //ENABLE pin (PF2) for Motor A to provide PWM -> right wheel
int in1 = 12;   //IN1 pin (PA3) for Motor A for direction -> right wheel
int in2 = 11;   //IN2 pin (PA2) for Motor A for direction -> right wheel 

int enB = 39; // ENABLE pin (PF3) for Motor B to provide PWM -> left wheel
int in3 = 9;  // IN3 pin (PA6) for Motor B for direction -> left wheel
int in4 = 10; // IN4 pin (PA7) for Motor B for direction -> left wheel

const int SW2 = 17;   //Pin number for Switch SW2
bool direction = true;  //Flag for clockwise or anti-clockwise direction


void setup() {
  Serial.begin(115200); //Serial initializing for Debugging
  
  //Specify pinModes for enA, in1 and in2 for right motor
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Specify pinModes for enB, in3, and in4 for left motor
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  

  //Initialize SW2 Switch as Input
  pinMode(SW2, INPUT_PULLUP);  //State for SW2 with pullUp resistor
}

void loop() {
    // Make the motor run clockwise direction using in1 and in2 states below

    changeDirection();
  
    //Varying Speed for motor below with delay of 2 seconds
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    changeDirection();
    Serial.print("0 Speed\n");
    delay(2000);
    analogWrite(enA, 64);
    analogWrite(enB, 64);
    changeDirection();
    Serial.print("25% Speed\n");
    changeDirection();
    delay(2000);
    analogWrite(enA, 191);
    analogWrite(enB, 191);
    changeDirection();
    Serial.print("75% Speed\n");
    delay(2000);
    analogWrite(enA, 255);
    analogWrite(enB, 255);
    changeDirection();
    Serial.print("100% Speed\n");
    delay(2000);
}

void tenP_Speed() {
    //Generates PWM of 50Hz (20ms total) with Duty Cycle of 10%
    for (int i=0; i<50; i++){
      digitalWrite(enA, HIGH);
      digitalWrite(enB, HIGH);
      delayMicroseconds(10000); // High for 2ms, Duty Cycle of 10%
      digitalWrite(enA, LOW);
      digitalWrite(enB, LOW);
      delayMicroseconds(10000); // Off for remaining  18ms
  }
}

void zeroP_Speed() {
    //Generates PWM of 50Hz (20ms total) with Duty Cycle of 0%
    for (int i=0; i<50; i++){
      digitalWrite(enA, LOW);
      digitalWrite(enB, LOW);
      delayMicroseconds(20000); // Off for remaining  18ms
  }
}

void medP_Speed() {
    //Generates PWM of 50Hz (20ms total) with Duty Cycle of 25%
    for (int i=0; i<50; i++){
      digitalWrite(enA, HIGH);
      digitalWrite(enB, HIGH);
      delayMicroseconds(5000); // High for 2ms, Duty Cycle of 25%
      digitalWrite(enA, LOW);
      digitalWrite(enB, LOW);
      delayMicroseconds(15000); // Off for remaining  ms
  }
}

void highP_Speed() {
    //Generates PWM of 50Hz (20ms total) with Duty Cycle of 75%
    for (int i=0; i<50; i++){
      digitalWrite(enA, HIGH);
      digitalWrite(enB, HIGH);
      delayMicroseconds(15000); // High for 2ms, Duty Cycle of 75%
      digitalWrite(enA, LOW);
      digitalWrite(enB, LOW);
      delayMicroseconds(5000); // Off for remaining  
  }
}

void fullP_Speed() {
    //Generates PWM of 50Hz (20ms total) with Duty Cycle of 100%
    for (int i=0; i<50; i++){
      digitalWrite(enA, HIGH);
      digitalWrite(enB, HIGH);
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
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH); 
    } else {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    delay(1000);  
}
