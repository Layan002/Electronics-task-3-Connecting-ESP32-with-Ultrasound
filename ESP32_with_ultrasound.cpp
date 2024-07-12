#include <Ultrasonic.h>

// Define the pins for the ultrasonic sensor
#define TRIG_PIN 5
#define ECHO_PIN 23

// Create an instance of the Ultrasonic library
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
}

void loop() {
  // Read the distance in centimeters
  long distance = ultrasonic.read(CM);

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Wait for a bit before taking another reading
  delay(500);
}
