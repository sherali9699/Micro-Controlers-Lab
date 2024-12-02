const int encoderPinLeft = 29;  // Analog pin for encoder
const int encoderPinRight = 2;
int adcValueRight = 0;  
int adcValueLeft = 0;
int mappedValueRight = 0;  
int mappedValueLeft = 0;    

int enA = 40;   // ENABLE pin (PF2) for Motor A PWM -> right wheel
int in1 = 12;   // IN1 pin (PA3) for Motor A direction -> right wheel
int in2 = 11;   // IN2 pin (PA2) for Motor A direction -> right wheel 

int enB = 39;   // ENABLE pin (PF3) for Motor B PWM -> left wheel
int in3 = 9;    // IN3 pin (PA6) for Motor B direction -> left wheel
int in4 = 10;   // IN4 pin (PA7) for Motor B direction -> left wheel

void setup() {
  Serial.begin(115200);     // Initialize Serial Monitor
  pinMode(encoderPinLeft, INPUT);
  pinMode(encoderPinRight, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  moveForward();
  adcValueRight = analogRead(encoderPinRight); // Read the analog value
  adcValueLeft = analogRead(encoderPinLeft);
  mappedValueRight = map(adcValueRight, 0, 4095, 0, 255);
  mappedValueLeft = map(adcValueLeft, 0, 4095, 0, 255);
  
  Serial.print("Right Value: ");
  Serial.print(mappedValueRight);
  
  Serial.print("  Left Value: ");
  Serial.println(mappedValueLeft);
  delay(100);

  
}

void moveForward() {
  // Set motor speed
  analogWrite(enA, 255); // Full speed for right motor
  analogWrite(enB, 255); // Full speed for left motor

  // both tires move forward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
}

void turnLeft(){
  // Set motor speed
  analogWrite(enA, 255); // Full speed for right motor
  analogWrite(enB, 255); // Full speed for left motor

  // left wheel rotates forward, right backwards
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);     
}
