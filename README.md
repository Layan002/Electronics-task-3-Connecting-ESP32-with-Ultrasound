# Components
- ESP32 development board
- LCD 16x2 display
- Ultrasonic sensor (HC-SR04)
- Breadboard and jumper wires

# Wiring
#### Ultrasonic Sensor (HC-SR04) to ESP32:
- VCC to 5V
- GND to GND
- Trig to GPIO 5
- Echo to GPIO 18

#### LCD 16x2 Display to ESP32:
- VSS (pin 1) to GND
- VDD (pin 2) to 5V
- RS (pin 4) to GPIO 16
- RW (pin 5) to GND (grounded to set the LCD in write mode)
- E (pin 6) to GPIO 17
- D4 (pin 11) to GPIO 23
- D5 (pin 12) to GPIO 19
- D6 (pin 13) to GPIO 21
- D7 (pin 14) to GPIO 22
- A (pin 15) to 5V (to keep the backlight permanently on, assuming it has a built-in resistor)

# Arduino Code:
#### Install Libraries:
Ensure you have the LiquidCrystal library installed. You can install it via the Arduino Library Manager if it's not already installed.
#### Arduino Sketch:
``` CPP
#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(16, 17, 23, 19, 21, 22);

// Ultrasonic sensor pins
const int trigPin = 5;
const int echoPin = 18;

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);

  // Print a message to the LCD.
  lcd.setCursor(0, 0); // Set cursor to column 0, row 0
  lcd.print("Distance: ");
  
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Set pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Measure distance
  long duration, distance;
  
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters (cm)
  distance = duration * 0.034 / 2;

  // Print distance to serial monitor for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Print distance on LCD
  lcd.setCursor(10, 0); // Set cursor to column 10, row 0
  lcd.print("     "); // Clear previous distance value
  lcd.setCursor(10, 0); // Set cursor again to column 10, row 0
  lcd.print(distance);
  lcd.print(" cm");
  
  delay(500); // Delay for stability
}

```
## Explanation:
- Wiring: The ultrasonic sensor (HC-SR04) is connected to measure distance, and the LCD 16x2 display is used to output the distance measurement.
- Code: The Arduino sketch initializes the LCD and continuously measures and displays the distance from the ultrasonic sensor.
## Testing 
- Upload the sketch to your ESP32.
- Ensure the ultrasonic sensor is placed in a suitable location to measure distances.
- Verify that the LCD displays accurate distance measurements in centimeters.
> [!NOTE]
> This setup combines the functionality of displaying ultrasonic sensor readings on an LCD 16x2 display using an ESP32, providing a practical integration for distance measurement projects.


# Adding AA bettaries
Yes, you can use AA batteries to power your ultrasonic sensor, LCD, and backlight, but there are a few important considerations to ensure everything works correctly and safely.

Powering Components with AA Batteries
Voltage Considerations:

Ultrasonic Sensor (HC-SR04): Typically operates at 5V. You will need to ensure that the AA battery setup provides an appropriate voltage.
LCD Display: Commonly operates at 5V, but if your LCD can operate at 3.3V, it's better to match it with the ESP32's logic level.
ESP32: Typically operates at 3.3V, and its pins are not 5V tolerant.
Using AA Batteries:

AA batteries typically provide 1.5V each. Using 4 AA batteries in series will give you 6V, which can be regulated to 5V using a voltage regulator.
Connecting AA Batteries:
Voltage Regulator:

Use a 5V voltage regulator (like a 7805) to step down 6V from 4 AA batteries to 5V for your components.
Battery Configuration:

Connect 4 AA batteries in series to get 6V.
Use the 6V output from the batteries and pass it through a 5V voltage regulator to get a stable 5V output.
Wiring Diagram:
Connect 4 AA Batteries in Series:

Positive Terminal of Battery Pack (6V) -> Input of 5V Voltage Regulator
Ground Terminal of Battery Pack -> Ground of 5V Voltage Regulator
Output of 5V Voltage Regulator:

Output (5V) -> VCC of Ultrasonic Sensor, VDD of LCD, and A (backlight) of LCD
Ground -> Ground of Ultrasonic Sensor, LCD

[Battery Pack (6V)]
     +----+----+----+----+
     | AA | AA | AA | AA |
     +----+----+----+----+
       |               |
       +-----> 6V      |
              (Output to 5V Regulator)

              
[5V Voltage Regulator (7805)]
     +-------------------------+
     |    IN   GND   OUT       |
     +----+    |    +----+     |
          |    |         |     |
          6V  GND       5V    GND
          |    |         |     |
          |    +---------+     |
          |                    |


Connecting Components:
5V Regulator Output (5V):

VCC of Ultrasonic Sensor
VDD of LCD
A (backlight) of LCD
Ground (GND):

Ground of Ultrasonic Sensor
Ground of LCD
Code Considerations:
Ensure that you have consistent and correct power to avoid any issues with the operation of your components. The code does not need to change, as the power supply is independent of the pin connections.

If you want to implement this setup, you can get a 5V voltage regulator module,

and it should look something like this:

AA Batteries (4x1.5V) -> 5V Regulator -> VCC and Ground for Sensors and LCD

Note:
Battery Life: AA batteries will deplete over time, so consider the current consumption of your components to estimate battery life.
Voltage Drop: Be aware of voltage drops over time as the batteries discharge, which might affect the performance of your components.
Safety: Ensure all connections are secure and check the regulator's specifications to avoid overheating.
If you follow these steps, you should be able to power your ultrasonic sensor, LCD, and backlight with AA batteries.

