////////////////////////////////////////////////////
//Ultrasonic Pins Definition
const int echo_left = 14, Trig_left = 13;  // Pins for Left Ultrasonic
const int echo_right = 17, Trig_right = 8; // Pins for Right Ultrasonic

////////////////////////////////////////////////////
//Time Update Variables
long duration_left, duration_right, cm_left, cm_right; // Variables for timing and distances

////////////////////////////////////////////////////
// Setup Function
void setup() {
  Serial.begin(115200);             // Initialize Serial COM Port with 115200 baud rate
  pinMode(Trig_left, OUTPUT);       // Trigger is OUTPUT
  pinMode(echo_left, INPUT);        // Echo is INPUT
  pinMode(Trig_right, OUTPUT);      
  pinMode(echo_right, INPUT);

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
  
}

////////////////////////////////////////////////////
// Main Loop
void loop() {
  // Update distances from both sensors
  updateUltrasonic();

  // Delay for stability
  delay(100); 
}

////////////////////////////////////////////////////
// Ultrasonic Update Function
void updateUltrasonic() {
  // Get distance from the left sensor
  cm_left = getDistance(Trig_left, echo_left);

  // Short delay to prevent interference
  delay(50);

  // Get distance from the right sensor
  cm_right = getDistance(Trig_right, echo_right);

  // Print results
  Serial.print("Distance Left: ");
  Serial.print(cm_left);
  Serial.print(" cm\t");

  Serial.print("Distance Right: ");
  Serial.print(cm_right);
  Serial.println(" cm");
}

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

  distance_cm = (0.0343 * duration) / 2; // Speed of sound: 343 m/s or 0.0343 cm/us
  return distance_cm;
}
