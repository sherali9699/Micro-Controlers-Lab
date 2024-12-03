////////////////////////////////////////////////////
// Ultrasonic Pins Definition
const int echo_left = 14, Trig_left = 13;  // Pins for Left Ultrasonic
const int echo_right = 17, Trig_right = 8; // Pins for Right Ultrasonic

////////////////////////////////////////////////////
// Time Update Variables
long duration_left, duration_right, cm_left, cm_right; // Variables for timing and distances
unsigned long lastSensorUpdate = 0; // For sensor update timing
const unsigned long sensorInterval = 50; // Update sensors every 50ms

////////////////////////////////////////////////////
// For Motors
// Motor A, TivaC and L298N connections
int enA = 40;   // ENABLE pin (PF2) for Motor A PWM -> right wheel
int in1 = 12;   // IN1 pin (PA3) for Motor A direction -> right wheel
int in2 = 11;   // IN2 pin (PA2) for Motor A direction -> right wheel 

int enB = 39;   // ENABLE pin (PF3) for Motor B PWM -> left wheel
int in3 = 9;    // IN3 pin (PA6) for Motor B direction -> left wheel
int in4 = 10;   // IN4 pin (PA7) for Motor B direction -> left wheel

////////////////////////////////////////////////////
// For Infrared Sensor
int IR_SENSOR_PIN = 28; 

////////////////////////////////////////////////////
// PID Control
float kp, ki;
float prev_err = 0.0;
float integral = 0.0;
float set, dt;
int err;

////////////////////////////////////////////////////
// Setup Function
void setup() {
  Serial.begin(115200);             // Initialize Serial COM Port with 115200 baud rate
  pinMode(Trig_left, OUTPUT);       // Trigger is OUTPUT
  pinMode(echo_left, INPUT);        // Echo is INPUT
  pinMode(Trig_right, OUTPUT);      
  pinMode(echo_right, INPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  pinMode(IR_SENSOR_PIN, INPUT);  // IR sensor pin set as INPUT
}

////////////////////////////////////////////////////
// Main Loop
void loop() {
  unsigned long currentMillis = millis();

  // Update sensors at regular intervals
  if (currentMillis - lastSensorUpdate >= sensorInterval) {
    lastSensorUpdate = currentMillis;
    updateSensors();
  }

  // Control the motors
  controlMotors();
  delay(500);
}

////////////////////////////////////////////////////
// Sensor Update Function
void updateSensors() {
  // Get distance from the left ultrasonic sensor
  cm_left = getDistance(Trig_left, echo_left);

  // Short delay to prevent interference
  delayMicroseconds(100);

  // Get distance from the right ultrasonic sensor
  cm_right = getDistance(Trig_right, echo_right);

  // Get IR sensor reading
  int ir_status = digitalRead(IR_SENSOR_PIN);
  
  // Print all sensor readings to the Serial Monitor
  Serial.print("Left: ");
  Serial.print(cm_left);
  Serial.print(" cm\t");

  Serial.print("Right: ");
  Serial.print(cm_right);
  Serial.print(" cm\t");

  if (ir_status == LOW) {
    Serial.println("Detected");  // IR sensor detects an object
  } else {
    Serial.println("Not Detected");  // No object detected
  }

  // Example condition: Take action based on sensor values
  if (cm_left > 15) {
    Serial.println("Action: Turn left");
  } else if (cm_right > 15) {
    Serial.println("Action: Turn right");
  } else {
    Serial.println("Action: Move forward");
  }
}

//int IR_Detection() {
//  int ir_status = digitalRead(IR_SENSOR_PIN);
//}


////////////////////////////////////////////////////
// Function to Measure Distance from a Sensor
long getDistance(int trigPin, int echoPin) {
  long duration, distance_cm;

  // Send a short pulse to the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo
  duration = pulseIn(echoPin, HIGH, 30000); // Timeout after 30ms (max ~5 meters)

  if (duration == 0) return 0; // No echo detected
  distance_cm = (0.0343 * duration) / 2; // Speed of sound: 343 m/s or 0.0343 cm/us
  return distance_cm;
}

////////////////////////////////////////////////////
// Motor Control Functions
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

void moveBackward(){
  // Set motor speed
  analogWrite(enA, 255); // Full speed for right motor
  analogWrite(enB, 255); // Full speed for left motor

  // both tires move backwards
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);    
}

void turnLeft(){
  // Set motor speed
  analogWrite(enA, 255); // Full speed for right motor
  analogWrite(enB, 255); // Full speed for left motor

  // right wheel rotates forward, left backwards
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);     
}

void turnRight(){
  // Set motor speed
  analogWrite(enA, 255); // Full speed for right motor
  analogWrite(enB, 255); // Full speed for left motor

  // left wheel rotates forward, right backwards
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);     
}

void controlMotors() {
  const int boundaryDistance = 10; // Minimum distance to a boundary in cm
  bool irDetected = digitalRead(IR_SENSOR_PIN) == LOW;

  if (irDetected) {
    // Obstacle directly in front
    Serial.println("IR Detected: Turning left");
    turnLeft();
  } else if (cm_left < boundaryDistance) {
    // Too close to the left boundary
    Serial.println("Too close to left boundary: Turning right");
    turnRight();
  } else if (cm_right < boundaryDistance) {
    // Too close to the right boundary
    Serial.println("Too close to right boundary: Turning left");
    turnLeft();
  } else {
    // Path is clear
    Serial.println("Path clear: Moving forward");
    moveForward();
  }
}

///////////////////////////////////////////////////////////////////
// PID Control
float PID_Update(float setpoint, float measured_value, float dt) { 
    float error = setpoint - measured_value; 
    integral += error * dt;           // Integral term 
    float derivative = (error - prev_err) / dt; // Derivative term 
 
    // Calculate control output 
    float output = (kp * err) + (ki * integral); //+ (pid->Kd * derivative); 
     
    // Save current error for next derivative calculation 
    prev_err = error; 
 
    return output; 
}