# Simulation on WOKWi
Before getting started with ESP32 in real life. we should try to simulate everything on any online simulator. I chose WOKWI because it contains ESP32 unlike TinkerCAD which lacks of this component

## Components
- AITRIP ESP32-WROOM-32 board
- LCD 16x2 display
- I2C module
- Ultrasonic sensor (HC-SR04)
- jumper wires

## Wiring
### Ultrasonic Sensor (HC-SR04) to ESP32:
- VCC to ESP32 5V (or 3.3V, if your sensor supports it)
- GND to ESP32 GND
- TRIG_PIN to ESP32 GPIO 5
- ECHO_PIN to ESP32 GPIO 18

### LCD (with I2C Module) to ESP32
- LCD VCC to ESP32 3.3V (or 5V, depending on your LCD module)
- LCD GND to ESP32 GND
- LCD SDA to ESP32 GPIO 21
- LCD SCL to ESP32 GPIO 22

## Circuit Diagram
As mentioned before: 
- For ultrasound: Trig takes pin 5, Echo takes pin 23, and VCC takes 5V. <br>
- For LCD with I2C: SDA takes pin 21, SCL takes pin 22, and VCC takes 3.3V. <br>
<img src= "https://github.com/Layan002/Electronics-task-3-Connecting-ESP32-with-any-sensor-on-WOKWI/assets/107956591/d76026bf-d029-4938-801c-ded82bbf0e60" width = 700>

## Code 
> [!IMPORTANT]
> You need to install the libraries of: 'Ultrasonic' and 'LiquidCrystal_I2C' on WOKWI first to make the code runs without errors. 
``` CPP
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
```
### Explanation:
#### Libraries: 
- The 'Wire' library is used for I2C communication on the ESP32. LiquidCrystal_I2C is used for the LCD, and Ultrasonic is for the ultrasonic sensor.
#### Initialization:
- 'Wire.begin(21, 22)' initializes the I2C communication with SDA on GPIO 21 and SCL on GPIO 22 for the ESP32.
- 'lcd.begin()' initializes the LCD, including parameters 16 and 2 to specify the LCD's number of columns and rows. And 'lcd.backlight()' turns on the LCD backlight.
Loop:
- The distance is read using the ultrasonic sensor.
- The distance is printed to both the Serial Monitor and the LCD display.
- 'lcd.clear()' clears the previous content on the LCD.
- 'lcd.setCursor(0, 0)' and 'lcd.setCursor(0, 1)' position the cursor on the LCD to display the distance.

> [!NOTE]
> With this setup, you should see the distance measured by the ultrasonic sensor displayed on the LCD screen when using the ESP32. Adjust the I2C address (0x27) if your LCD has a different address.

## Testing ESP32 on WOKWI
https://github.com/Layan002/Electronics-task-3-Connecting-ESP32-with-any-sensor-on-WOKWI/assets/107956591/9ad63df6-5957-4eba-b0cc-9feaca67d0d9



# Real life implementation using Arduino IDE:
After successfully running the code on the emulator, we can now use the real piece for ESP32. But first of all we have important steps to:

## Uploading ESP32 to Arduino IDE 1.8.19

### Install Arduino IDE:
If you haven't installed Arduino IDE yet, download it from the [Arduino website](https://www.arduino.cc/en/software) and install it on your computer.

### Install ESP32 Board Manager:
- Open Arduino IDE.
- Go to File > Preferences.
- In the "Additional Board Manager URLs" field, add the following URL
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
- Click "OK" to close the Preferences window.
  
### Install ESP32 Board Package:
- Go to Tools > Board > Boards Manager.
- In the Boards Manager window, search for "ESP32".
- Select "ESP32 by Espressif Systems" and click "Install".
  
### Select ESP32 Board:
- Go to Tools > Board.
- Select your specific ESP32 board from the list (e.g., "ESP32 Dev Module"). I have ESP32-WROOM-32 board so I will choose **"ESP32 WROOM-DA Module"**
  
### Select the Port:
- Connect your ESP32 to your computer using a USB cable.
- Go to Tools > Port and select the port to which your ESP32 is connected (e.g., COM3 on Windows, /dev/ttyUSB0 or /dev/ttyS0 on Linux).
  
### Configure the Upload Settings:
Make sure the following settings are selected under the 'Tools' menu:
- Flash Mode: QIO
- Flash Frequency: 40MHz
- Partition Scheme: Default
- Core Debug Level: None
- PSRAM: Disabled (unless your board supports and requires PSRAM)

### Testing the ESP32 
We must first make sure that the ESP32 is valid to use and does NOT have any malfunctions. To do that, we do the following:
- Connect the ESP32 to your laptob by blogging the USB into the port.
- File -> Examples -> Basics -> Blink
- Upload the code and wait
> [!NOTE]
> You should see a blue light blinking.

https://github.com/user-attachments/assets/c6772f7e-678e-4ab7-a4dc-4df92b7d372d


### Install Libraries:
> [!IMPORTANT]
> Include the necessary libraries:
To do that, go to Scetch -> Include library -> menage libraries -> search for the library -> install
- LiquidCrystal_I2C by Frank de Brabander.
- Ultrasonic by Erick Simões.
You DONT have to install wire library as it is built in.

> [!NOTE]
> If you cant find the LiquidCrystal_I2C library by Frank de Brabander, download the ZIP file from the [GitHub repository](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library) and install it manually by going to: <br>
> Sketch -> Include Library -> Add .ZIP Library... and selecting the downloaded ZIP file.

> [!CAUTION]
> LiquidCrystal_I2C library has something important to change to make the ESP32 communicates and works with the LCD: <br>
>
> go to the Arduino file on your laptob -> libraies ->  LiquidCrystal_I2C -> library.properties. <br>
>
> C:\Users\welcome\Documents\Arduino\libraries\LiquidCrystal_I2C. usually it is like this path. <br>
> 
> inside library.properties add esp32 to 'architectures'.<br>

inside Arduino libraries specificly for LiquidI2C, add esp32 as I did: <br>
<img src= "https://github.com/user-attachments/assets/dcc8a2ad-bad0-4d8b-bf19-058a547dd63a" alt= "image" width= 700>

> [!CAUTION]
> DO NOT forget to rotate the potentiometer of the I2C, if you didn't, it may not work! <br>
<img src= "https://github.com/user-attachments/assets/ac39e6f0-1abf-4f32-91d9-2f55b0a7b924" alt= "image" width= 400>


### Arduino Sketch:
Arduino sketch is the same as WOKWI sketck: <br>

### Write or Open a Sketch:
``` CPP
#include <Ultrasonic.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the pins for the ultrasonic sensor
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

```
### Upload the Code:
- Click the "Upload" button (the right-arrow icon) in the Arduino IDE toolbar.
- The IDE will compile the sketch and upload it to your ESP32 board.
- You should see the progress in the status window at the bottom of the IDE.

### Monitor the Serial Output (Optional):
- Go to Tools > Serial Monitor to open the Serial Monitor.
- Ensure the baud rate matches the one specified in your code (e.g., 115200).

## Testing both LCD and ultrasound individually:
Usually we need to break down the code to test everything usually because sometimes the main code doesn't work and we need to check which makes the problem. So, I sketched the following codes: <br>
- Testing LCD: <br>
``` CPP
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address found by the I2C scanner
#define LCD_ADDRESS 0x27 // Replace with your LCD's I2C address
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// Initialize the LiquidCrystal_I2C library with the I2C address, columns, and rows
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup() {
  // Initialize the Wire library with the specified SDA and SCL pins for the ESP32
  Wire.begin(21, 22);
  
  // Initialize the LCD
  lcd.init();
  
  // Turn on the backlight (if supported)
  lcd.backlight();
  
  // Print a message to the LCD
  lcd.print("hello, world!");
}

void loop() {
  // Turn off the display
  lcd.noDisplay();
  delay(500);
  
  // Turn on the display
  lcd.display();
  delay(500);
}
```
- Testing Ultrasound: <br>
``` CPP
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
```




