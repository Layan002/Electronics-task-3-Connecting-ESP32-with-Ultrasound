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

<img src= "https://github.com/Layan002/Electronics-task-3-Connecting-ESP32-with-any-sensor-on-WOKWI/assets/107956591/d76026bf-d029-4938-801c-ded82bbf0e60" width = 700>

# Testing ESP32 on WOKWI

https://github.com/Layan002/Electronics-task-3-Connecting-ESP32-with-any-sensor-on-WOKWI/assets/107956591/9ad63df6-5957-4eba-b0cc-9feaca67d0d9

# Uploading ESP32 to Arduino IDE 1.8.19

To upload code to an ESP32 using Arduino IDE 1.8.19, follow these steps:

#### Install Arduino IDE:
If you haven't installed Arduino IDE yet, download it from the [Arduino website](https://www.arduino.cc/en/software) and install it on your computer.

#### Install ESP32 Board Manager:
- Open Arduino IDE.
- Go to File > Preferences.
- In the "Additional Board Manager URLs" field, add the following URL
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
- Click "OK" to close the Preferences window.
#### Install ESP32 Board Package:
- Go to Tools > Board > Boards Manager.
- In the Boards Manager window, search for "ESP32".
- Select "ESP32 by Espressif Systems" and click "Install".
#### Select ESP32 Board:
- Go to Tools > Board.
- Select your specific ESP32 board from the list (e.g., "ESP32 Dev Module").
#### Select the Port:
- Connect your ESP32 to your computer using a USB cable.
- Go to Tools > Port and select the port to which your ESP32 is connected (e.g., COM3 on Windows, /dev/ttyUSB0 or /dev/ttyS0 on Linux).
#### Configure the Upload Settings:
Make sure the following settings are selected under the 'Tools' menu:
- Flash Mode: QIO
- Flash Frequency: 40MHz
- Partition Scheme: Default
- Core Debug Level: None
- PSRAM: Disabled (unless your board supports and requires PSRAM)

#### Write or Open a Sketch:
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
#### Upload the Code:
- Click the "Upload" button (the right-arrow icon) in the Arduino IDE toolbar.
- The IDE will compile the sketch and upload it to your ESP32 board.
- You should see the progress in the status window at the bottom of the IDE.

#### Monitor the Serial Output (Optional):
- Go to Tools > Serial Monitor to open the Serial Monitor.
- Ensure the baud rate matches the one specified in your code (e.g., 115200).
- If you encounter any issues during these steps, feel free to ask for further assistance!

# Troubleshooting

inside Arduino libraries specificly for LiquidI2C, add esp32 as I did
![image](https://github.com/user-attachments/assets/dcc8a2ad-bad0-4d8b-bf19-058a547dd63a)

# Testing LCD with Arduino

``` CPP
#include <Wire.h>  // Include Wire library for I2C
#include <LiquidCrystal_I2C.h>  // Include LiquidCrystal_I2C library

// Set the LCD address to 0x27 or 0x3F (depends on your module)
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// Initialize the LiquidCrystal_I2C library with the I2C address, columns, and rows
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup() {
  // Initialize the LCD
  lcd.init();
  
  // Turn on the backlight (if supported)
  lcd.backlight();
  
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // Turn off the display:
  lcd.noDisplay();
  delay(500);
  
  // Turn on the display:
  lcd.display();
  delay(500);
}
```
> [!NOTE]
> I've used Marco Library by installing it from Library manager





