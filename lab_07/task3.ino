/*
 Analog input from LDR, analog output to built-in RED LED, and serial output
 
 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.
 
 The circuit:
 * potentiometer/LDR connected to analog pin 0 i.e. PE3.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +3.3V and ground
 * LED connected from Analog pin 30 i.e. PF1 (Buil-in LED)
*/

// Pin Connections
const int analogInPin = 29;  // Connect Output from LDR at PE3/A0
const int analogOutPin = 30; // Analog Output to Built-in RED LED at PF1

int ADCValue = 0;      // ADC Value read from LDR in range 0-4095
int brightness = 0;    // ADC Output to Built-in LED to control it's brightness
float voltage = 0;     //Voltage to be calculated basedd on ADC value

void setup() {
  // initialize serial communications at 115200 bps:
  Serial.begin(115200);
  
  //Declare Pin modes for analogInPin and analogOutPin
  pinMode(analogInPin, INPUT);
  pinMode(analogOutPin, OUTPUT);
}

void loop() {
  //Read the analog value using analogRead(pin) and store in variable ADCValue:
  ADCValue = analogRead(analogInPin);      
    
  //Mapping the input value of 0-4095 to 0-255 for output and store in variable brightness
  brightness = map(ADCValue, 0, 4095, 0, 255);
  
  //Control brightness of LED at analogOutPin using analogWrite(pin, value)
  analogWrite(analogOutPin, brightness);

  //Calculate the voltage value below using ADCValue
  voltage = (ADCValue * 3.3) / 4095;
  
  //Print the results to the Serial Monitor:
  Serial.print("ADC Input Value = " );                   
  Serial.print(ADCValue);      
  Serial.print("\t Brightness = ");      
  Serial.println(brightness);
  Serial.print("\t Voltage = ");      
  Serial.println(voltage);  

  // wait 100 milliseconds before the next loop for ADC settling
  delay(100);                     
}
