// Cole Hengstebeck ECE 387 Midterm
// This program takes two GNSS lat/long pairs and calculates the distance between
// them in meters. This number is output to an LCD screen.
// Based on Example 3 code from SparkFun u-blox GNSS library.

#include <Wire.h> //Needed for I2C to GNSS
#include <SparkFun_u-blox_GNSS_Arduino_Library.h> //http://librarymanager/All#SparkFun_u-blox_GNSS
#include <LiquidCrystal.h>

const int BTTN = 2;
const double R_EARTH = 6371000; // radius of Earth in meters
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;


SFE_UBLOX_GNSS SAMM8Q;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pinMode(BTTN, INPUT);
  
  Serial.begin(115200);
  Serial.println("Running");
  
  Wire.begin();

  if (SAMM8Q.begin() == false) //Connect to the u-blox module using Wire port
  {
    Serial.println("u-blox GNSS not detected at default I2C address. Please check wiring. Freezing.");
    while (1);
  }
  
  SAMM8Q.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
  SAMM8Q.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT); //Save (only) the communications port settings to flash and BBR

  lcd.begin(16, 2);
  lcd.print("Running");
  delay(1500);
}

void loop() {
    lcd.clear();
    while(digitalRead(BTTN) == LOW) {
      delay(100); // Wait for button to be pushed the first time
      lcd.setCursor(0, 0);
      lcd.print("Press to cap");
      lcd.setCursor(0,1);
      lcd.print("location 1");
    }
    double lat1 = SAMM8Q.getLatitude() / (pow(10, 7));
    Serial.print("Lat: ");
    Serial.print(lat1, 7);

    double long1 = SAMM8Q.getLongitude() / (pow(10, 7));
    Serial.print(" Long: ");
    Serial.println(long1, 7);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Captured #1");
    delay(2500);
    
    lcd.clear();
    while(digitalRead(BTTN) == LOW) {
      delay(100); // Wait for button to be pushed the first time
      lcd.setCursor(0, 0);
      lcd.print("Press to cap");
      lcd.setCursor(0,1);
      lcd.print("location 2");
    }

    double lat2 = SAMM8Q.getLatitude() / (pow(10, 7));
    Serial.print("Lat: ");
    Serial.print(lat2, 7);

    double long2 = SAMM8Q.getLongitude() / (pow(10, 7));
    Serial.print(" Long: ");
    Serial.println(long2, 7);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Captured #2");
    delay(2500);
    lcd.clear();

    double dist = haversine_dist(lat1, long1, lat2, long2);

    Serial.print("Dist: ");
    Serial.println(dist, 7);
    
    while(digitalRead(BTTN) == LOW) {
      delay(100); // Wait for button to be pushed the first time
      lcd.setCursor(0, 0);
      lcd.print("Distance = ");
      lcd.setCursor(0,1);
      lcd.print(dist);
      lcd.print("m");
    }
    delay(1500);
}

// Calculates the distance on a sphere between two sets of coordiantes
double haversine_dist(double lat1, double long1, double lat2, double long2) {
  double delta_lat = (lat2 - lat1) * (PI / 180.0);
  double delta_long = (long2 - long1) * (PI / 180.0);
  double lat1_rad = lat1 * (PI / 180.0);
  double lat2_rad = lat2 * (PI / 180.0);
  double a = sq(sin(delta_lat / 2)) + (sq(sin(delta_long / 2)) * cos(lat1_rad) * cos(lat2_rad));
  double c = 2 * atan2(sqrt(a), sqrt(1-a));
  return R_EARTH * c;
}
