#include <Ultrasonic.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the pins for th4e ultrasonic sensor
#define TRIG_PIN 5
#define ECHO_PIN 23

// Create an instance of the Ultrasonic library
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

// Create an instance of the LiquidCrystal_I2C library with the LCD address
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adjust the address if needed

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize the I2C communication with custom SDA and SCL pins
  Wire.begin(21, 22);  // SDA = GPIO 21, SCL = GPIO 22

  // Initialize the LCD
  lcd.begin(16, 2);  // Specify the number of columns and rows
  lcd.backlight();  // Turn on the backlight
}

void loop() {
  // Read the distance in centimeters
  long distance = ultrasonic.read(CM);

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Print the distance to the LCD
  lcd.clear();
  lcd.setCursor(0, 0);  // Set cursor to first column, first row
  lcd.print("Distance:");
  lcd.setCursor(0, 1);  // Set cursor to first column, second row
  lcd.print(distance);
  lcd.print(" cm");

  // Wait for a bit before taking another reading
  delay(500);
}
