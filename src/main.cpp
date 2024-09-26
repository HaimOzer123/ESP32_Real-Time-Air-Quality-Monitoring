#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_AHTX0.h>
#include <ScioSense_ENS160.h>

// Initialize the I2C LCD (16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Initialize the AHT21 sensor (temperature and humidity)
Adafruit_AHTX0 aht;

// Initialize the ENS160 CO2 sensor
ScioSense_ENS160 ens160;

// Global variables to store sensor data
float temperature = 0.0;
float humidity = 0.0;
uint16_t co2 = 0;

// Function declaration
void readSensors();  // Make sure this function is declared

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(115200);

  // Set up I2C pins
  Wire.begin(4, 16);  // LCD I2C: SDA = D4, SCL = D16

  // Initialize LCD (16 columns, 2 rows)
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  // Initialize AHT21 sensor on I2C bus
  if (!aht.begin(&Wire, 0x38)) { //0x38 is the I2C address of the AHT21 sensor
    Serial.println("Failed to initialize AHT21 sensor!");
    lcd.setCursor(0, 1);
    lcd.print("AHT Fail");
    while (1);
  }

  // Initialize ENS160 sensor on I2C bus
  if (!ens160.begin(0x53)) {  // Use 0x53 
      Serial.println("Failed to initialize ENS160 sensor!");
      lcd.setCursor(0, 1);
      lcd.print("ENS160 Fail");
      while (1);
  }

  lcd.setCursor(0, 1);
  lcd.print("Sensors Ready");
  delay(2000);
}

void loop() {
  readSensors();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("READ SENSORS");
  delay(500);

  // Display CO2 sensor reading on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CO2: ");
  lcd.print(co2);
  lcd.print(" ppm");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("CO2 Level: ");
  Serial.print(co2);
  Serial.println(" ppm");

  delay(3000);
}

// Function to read sensor values
void readSensors() {
  sensors_event_t humidity_event, temp_event;

  // Get AHT21 sensor readings
  aht.getEvent(&humidity_event, &temp_event);
  temperature = temp_event.temperature;
  humidity = humidity_event.relative_humidity;

  // Get CO2 sensor reading from ENS160
  co2 = ens160.geteCO2();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//This code is for the I2C scanner TEST
// #include <Arduino.h>
// #include <Wire.h>

// void setup() {
//   Wire.begin(12, 13);  // SDA = D12, SCL = D13 (pins as per your setup)
//   Serial.begin(115200);
//   while (!Serial);  // Wait for serial monitor to open
//   Serial.println("\nI2C Scanner");

//   byte error, address;
//   int nDevices = 0;

//   for (address = 1; address < 127; address++) {
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();

//     if (error == 0) {
//       Serial.print("I2C device found at address 0x");
//       if (address < 16) Serial.print("0");
//       Serial.println(address, HEX);
//       nDevices++;
//     } else if (error == 4) {
//       Serial.print("Unknown error at address 0x");
//       if (address < 16) Serial.print("0");
//       Serial.println(address, HEX);
//     }
//   }

//   if (nDevices == 0)
//     Serial.println("No I2C devices found\n");
//   else
//     Serial.println("done\n");
// }

// void loop() {
// }