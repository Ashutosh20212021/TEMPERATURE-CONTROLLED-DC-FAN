#include <math.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with the I2C address 0x27 and a 16x2 display size
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Thermistor function to calculate temperature in Celsius
double readTemperature(int analogValue) {
  double resistance, temperatureC, temperatureF;
  
  // Calculate resistance of thermistor
  resistance = 10000.0 * ((1024.0 / analogValue) - 1);

  // Using Steinhart-Hart equation to calculate temperature
  temperatureC = log(resistance); 
  temperatureC = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperatureC * temperatureC)) * temperatureC);
  temperatureC = temperatureC - 273.15; // Convert Kelvin to Celsius
  
  return temperatureC;
}

void displayTemperature(double tempC) {
  // Convert Celsius to Fahrenheit
  double tempF = (tempC * 9.0) / 5.0 + 32.0;

  // Display temperature on LCD in both Celsius and Fahrenheit
  lcd.clear();  // Clear screen before printing
  lcd.setCursor(0, 0);  // Move cursor to first row
  lcd.print("Temp: ");
  lcd.print(tempC);
  lcd.print(" C");

  lcd.setCursor(0, 1);  // Move cursor to second row
  lcd.print("Temp: ");
  lcd.print(tempF);
  lcd.print(" F");

  // Print to Serial Monitor for debugging purposes
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" C, ");
  Serial.print(tempF);
  Serial.println(" F");
}

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  lcd.begin();         // Initialize the LCD
  lcd.backlight();     // Turn on the LCD backlight
}

void loop() {
  int analogValue = analogRead(A0);      // Read analog value from the thermistor
  double temperatureC = readTemperature(analogValue);  // Get temperature in Celsius
  displayTemperature(temperatureC);      // Display temperature on LCD and Serial Monitor

  delay(1000);  // Wait for 1 second before updating again
}
