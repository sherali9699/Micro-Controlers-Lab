// IR Sensor Pin
const int IR_SENSOR = 28;  // IR sensor connected to pin PE1 (ADC1)

////////////////////////////////////////////////////
// IR Sensor Mapping Function (simple approximation for distance)
float mapIRDistance(int ir_value) {
  // The following formula is a general approximation for typical IR sensors.
  // You may need to adjust it based on your specific sensor.
  if (ir_value < 100) {
    return 0;  // If the value is too low, return 0 (out of range)
  }
  
  // Example formula for a generic IR sensor (adjust this based on your specific sensor)
  float distance = 27.98 * pow(ir_value, -1.15);  // Empirical formula
  return distance;  // Return the distance in cm
}

////////////////////////////////////////////////////
// Setup function
void setup() {
  // Initialize Serial communication
  Serial.begin(115200);               // Set baud rate to 115200
  pinMode(IR_SENSOR, INPUT);          // Set IR sensor pin as INPUT

  // Start the ADC
  analogReadResolution(12);          // Set ADC resolution to 12 bits (0-4095)
}

////////////////////////////////////////////////////
// Main loop
void loop() {
  // Read analog value from IR sensor (0-4095 range)
  int ir_reading = analogRead(IR_SENSOR); 
  
  // Map the analog reading to a distance in cm
  float ir_distance = mapIRDistance(ir_reading);
  
  // Print the raw IR sensor value and the corresponding distance
  Serial.print("IR Sensor Reading (Raw): ");
  Serial.print(ir_reading);
  Serial.print("\tDistance: ");
  Serial.print(ir_distance);
  Serial.println(" cm");
  
  delay(100);  // Delay for stability, adjust as needed
}
