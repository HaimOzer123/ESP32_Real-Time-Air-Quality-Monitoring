#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_AHTX0.h>
#include <ScioSense_ENS160.h>

// Initialize the I2C LCD (16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adjust the I2C address of the LCD

// Create sensor objects
Adafruit_AHTX0 aht;
ScioSense_ENS160 ens160;

float temperature = 0.0;
float humidity = 0.0;
uint16_t co2 = 0;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);

  // Initialize the LCD (SDA=D4, SCL=D16 for LCD)
  Wire.begin(4, 16);  
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Init Sensors...");

  // Initialize I2C for AHT21 and ENS160 sensors (SDA=D12, SCL=D13)
  TwoWire I2C_Sensors = TwoWire(1);  // I2C for sensors
  I2C_Sensors.begin(12, 13);  

  // Initialize AHT21 (Temperature & Humidity)
  if (!aht.begin(&I2C_Sensors, 0x38)) {
    lcd.setCursor(0, 1);
    lcd.print("AHT Fail");
    while (1);
  }

  // Initialize ENS160 (CO2)
  if (!ens160.begin()) {
    lcd.setCursor(0, 1);
    lcd.print("ENS160 Fail");
    while (1);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensors Ready");
  delay(2000);
}

void loop() {
  // Read sensor data
  sensors_event_t humidity_event, temp_event;
  aht.getEvent(&humidity_event, &temp_event);
  temperature = temp_event.temperature;
  humidity = humidity_event.relative_humidity;

  co2 = ens160.geteCO2();

  // Display the sensor data on the LCD
  lcd.clear();
  
  // Display temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);  // Show 1 decimal
  lcd.print("C");

  // Display humidity
  lcd.setCursor(0, 1);
  lcd.print("Humid: ");
  lcd.print(humidity, 1);
  lcd.print("%");

  delay(2000);

  // Display CO2
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CO2: ");
  lcd.print(co2);
  lcd.print(" ppm");

  delay(2000);  // Update every 2 seconds
}
