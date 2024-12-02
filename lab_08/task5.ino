// Motor A, TivaC and L298N connections
int enA = 7;   //ENABLE pin (PD3) for Motor A to provide PWM 
int in1 = 11;   //IN1 pin (PA2) for Motor A for direction
int in2 = 12;   //IN2 pin (PA3) for Motor A for direction
const int SW2 = 17;   //Pin number for Switch SW2
bool direction = true;  //Flag for clockwise or anti-clockwise direction
int enB = 6;   
int in1B = 13;  
int in2B = 14;  

void setup() {
  Serial.begin(115200); //Serial initializing for Debugging
  
  //Specify pinModes for enA, in1 and in2 below
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // for b
  pinMode(enB, OUTPUT);
  pinMode(in1B, OUTPUT);
  pinMode(in2B, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in1B, LOW);
  digitalWrite(in2B, LOW);

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



void changeDirection(){
  //To be used for task03 only
    if(digitalRead(SW2) == 0){
      direction = !direction;
    }
    if (direction == false){ // left turn
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH); 
	digitalWrite(in1B, HIGH); 
        digitalWrite(in2B, LOW);
    } else {	// right turn
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in1B, LOW); 
      digitalWrite(in2B, HIGH);
    }
    delay(1000);  
}
