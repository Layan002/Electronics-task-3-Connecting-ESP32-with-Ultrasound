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
