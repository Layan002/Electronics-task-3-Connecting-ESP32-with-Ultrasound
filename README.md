# Components
- AITRIP ESP32-WROOM-32 board
- LCD 16x2 display
- I2C module
- Ultrasonic sensor (HC-SR04)
- jumper wires

# Wiring
#### Ultrasonic Sensor (HC-SR04) to ESP32:
- VCC to ESP32 5V (or 3.3V, if your sensor supports it)
- GND to ESP32 GND
- TRIG_PIN to ESP32 GPIO 5
- ECHO_PIN to ESP32 GPIO 18

#### LCD (with I2C Module) to ESP32
- LCD VCC to ESP32 3.3V (or 5V, depending on your LCD module)
- LCD GND to ESP32 GND
- LCD SDA to ESP32 GPIO 21
- LCD SCL to ESP32 GPIO 22

# Arduino Code:
#### Install Libraries:
> [1IMPORTANT]
> Include the necessary libraries:
- Wire for I2C communication.
- LiquidCrystal_I2C for the LCD with I2C module.
- Ultrasonic for the ultrasonic sensor.

#### Arduino Sketch:
``` CPP
#include <Ultrasonic.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the pins for the ultrasonic sensor
#define TRIG_PIN 5
#define ECHO_PIN 18

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

```
## Explanation:
### Libraries: 
- The 'Wire' library is used for I2C communication on the ESP32. LiquidCrystal_I2C is used for the LCD, and Ultrasonic is for the ultrasonic sensor.
### Initialization:
- 'Wire.begin(21, 22)' initializes the I2C communication with SDA on GPIO 21 and SCL on GPIO 22 for the ESP32.
- 'lcd.begin()' initializes the LCD, including parameters 16 and 2 to specify the LCD's number of columns and rows. And 'lcd.backlight()' turns on the LCD backlight.
Loop:
- The distance is read using the ultrasonic sensor.
- The distance is printed to both the Serial Monitor and the LCD display.
- 'lcd.clear()' clears the previous content on the LCD.
- 'lcd.setCursor(0, 0)' and 'lcd.setCursor(0, 1)' position the cursor on the LCD to display the distance.

> [!NOTE]
> With this setup, you should see the distance measured by the ultrasonic sensor displayed on the LCD screen when using the ESP32. Adjust the I2C address (0x27) if your LCD has a different address.


# Circuit Diagram
<img src= "https://github.com/Layan002/Electronics-task-3-Connecting-ESP32-with-any-sensor-on-WOKWI/assets/107956591/1096c1b7-470c-4ecc-8d64-43e8f85fae0f" width = 700>

# Testing ESP32 on WOKWI

https://github.com/Layan002/Electronics-task-3-Connecting-ESP32-with-any-sensor-on-WOKWI/assets/107956591/9ad63df6-5957-4eba-b0cc-9feaca67d0d9




