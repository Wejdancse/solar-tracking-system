int ldr1 = A0;        // LDR 1 connected to analog pin A0
int ldr2 = A1;        // LDR 2 connected to analog pin A1
int in1 = 2;          // Motor input 1
int in2 = 4;          // Motor input 2
int ena = 9;          // Motor speed control (ENA pin)
int speed1 = 100;     // Reduced motor speed (PWM value for slower movement)
int ledPin = 10;      // LED connected to pin 10 (indicator LED)

int lightThreshold = 700; // Set the light intensity threshold (out of 1023)

void setup() {
  pinMode(ldr1, INPUT);       // Set LDR1 as input
  pinMode(ldr2, INPUT);       // Set LDR2 as input
  pinMode(in1, OUTPUT);       // Set motor input 1 as output
  pinMode(in2, OUTPUT);       // Set motor input 2 as output
  pinMode(ena, OUTPUT);       // Set motor speed control as output
  pinMode(ledPin, OUTPUT);    // Set LED pin as output

  analogWrite(ena, speed1);   // Set motor speed to slower speed
  Serial.begin(9600);         // Start serial for debugging
}

void loop() {
  int data1 = analogRead(ldr1);  // Read the analog value from LDR1 (0-1023)
  int data2 = analogRead(ldr2);  // Read the analog value from LDR2 (0-1023)

  // Print LDR values to serial monitor for debugging
  Serial.print("LDR1: ");
  Serial.print(data1);
  Serial.print(" LDR2: ");
  Serial.println(data2);

  // If LDR1 detects higher light intensity
  if (data1 > data2 && data1 > lightThreshold) {
    // Rotate motor to the left
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(ledPin, HIGH);   // Turn on LED to indicate action
  } 
  // If LDR2 detects higher light intensity
  else if (data2 > data1 && data2 > lightThreshold) {
    // Rotate motor to the right
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(ledPin, HIGH);   // Turn on LED to indicate action
  }
  else {
    // If neither LDR detects sufficient light, stop the motor
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);  // Stop the motor
    digitalWrite(ledPin, LOW);  // Turn off LED when no high light is detected
  }

  delay(500); // Add a longer delay to allow the LDRs to stabilize and prevent rapid switching
}

