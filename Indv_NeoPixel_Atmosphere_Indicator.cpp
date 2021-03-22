#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_NeoPixel.h>

#define TEMP_PIN 7  // Temperature Jewel <-- these won't be used if using SPI
#define HUM_PIN 9   // Humidity Jewel
#define PRES_PIN 8  // Pressure  Jewel
#define TEMP_PIX 7  // Number of temperature pixels
#define HUM_PIX 7   // Number of humidity pixels
#define PRES_PIX 7  // Number of barometer pixels

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

// Declares the 3 Jewels and their identifier
Adafruit_NeoPixel TempJewel = Adafruit_NeoPixel(TEMP_PIX, TEMP_PIN, NEO_GRB + NEO_KHZ800); // Temp
Adafruit_NeoPixel HumJewel = Adafruit_NeoPixel(HUM_PIX, HUM_PIN, NEO_GRB + NEO_KHZ800); // Humidity
Adafruit_NeoPixel PresJewel = Adafruit_NeoPixel(PRES_PIX, PRES_PIN, NEO_GRB + NEO_KHZ800); // Pressure

unsigned long delayTime;

// Colors for Temperature
//-40.0 to -10.0
uint32_t iceBlue = TempJewel.Color(0, 51, 255);
//-10.1 to 0.0
uint32_t lightBlue = TempJewel.Color(0, 153, 255);
// 0.1 to 10.0
uint32_t babyBlue = TempJewel.Color(51, 204, 255);
//10.1  to 19.9
uint32_t pineGreen = TempJewel.Color(14, 170, 26);
//20.0  to 25.0
uint32_t yellow = TempJewel.Color(255, 229, 0);
//25.1 to 30.0
uint32_t orange = TempJewel.Color(255, 102, 0);
//30.1 to 35.0
uint32_t orgRed = TempJewel.Color(255, 0, 51);
//35.1 to 40.0
uint32_t pureRed = TempJewel.Color(255, 0, 0);

// Colors for Humidity - Colors are very similar, consider a wider range.
// 0.0 to 10.0%
uint32_t lavender = HumJewel.Color(102, 102, 204);
// 10.1 to 20.0%
uint32_t purpBlue = HumJewel.Color(102, 102, 255);
// 20.1 to 30.0%
uint32_t plurble = HumJewel.Color(102, 153, 255);
// 30.1 to 40.0%
uint32_t lightBlue2 = HumJewel.Color(0, 153, 255);
//40.1 to 50.0%
uint32_t bluish = HumJewel.Color(51, 153, 255);
//50.1 to 60.0 %
uint32_t moreBlue = HumJewel.Color(51, 0, 255);
// 60 to 100 %
uint32_t pureBlue = HumJewel.Color(0, 0, 255);
// I'll likely add more colors for 60-70, 70-80, etc

// Colors for Pressure
// Pressure seems to be a fickle mistress for predicting weather
// It may be best to use the system for analog barometers:
// in mb (in Pa):
// 970-984 (97000 - 98400) = stormy = grey
// 984-998 (98401 - 99800)= rain = blue
// 998-1012 (998001 - 101200) = change = purple
// 1012-1026 (101201 - 102600) = fair = green
// 1026-1040 (102601 - 104000) = dry = yellow
// Then add: else if rate of change == pulse or rainbow
uint32_t stormy = PresJewel.Color(163, 159, 164); // Grey
uint32_t rainy = PresJewel.Color(43, 92, 255);    // Blue
uint32_t change = PresJewel.Color(213, 0, 255);   // Purple
uint32_t fair = PresJewel.Color(7, 201, 39);      // Green
uint32_t dry = PresJewel.Color(243, 50, 31);      // Yellow

/* Barometric Pressure Ranges in Pa to show on PresJewel
I'm considering using these to map pressure range to color wheel
The other option is different colors for the rate of change.
minBaro = 87000
maxBaro = 108400
maxColor = 255
minColor = 0 /*/
float press;
float previousPress;



void setup() {
  delayTime = 1000;
  unsigned status;
  // Initializes the BME
  status = bme.begin(0x76);
  // Values used for Pressure Change Colors
  previousPress = press;
  press = bme.readPressure();
  // Below is only used for debugging. Comment out for final product.
  //Serial.begin(9600);

  //Initialization of the Temp Jewel
    TempJewel.setBrightness(10);
    TempJewel.begin();
    TempJewel.show();
  // Initialization of the Humidity Jewel
    HumJewel.setBrightness(10);
    HumJewel.begin();
    HumJewel.show();
  // Initialization of the Pressure Jewel
    PresJewel.setBrightness(10);
    PresJewel.begin();
    PresJewel.show();
}

void loop() {
  delay(1000);
  /* Used only for debugging the BME180
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
  
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure());
  Serial.println(" RAW VAL");
  
  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
  
  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");/*/
  
  Serial.println();
  TempReadings();
  PressureReadings();
  HumidReadings();
}

void TempReadings() {
  if (bme.readTemperature() >= -40.0 && bme.readTemperature() <= -10.0) {
    TempJewel.fill(iceBlue, 0, 7);
    TempJewel.show();
  } else if (bme.readTemperature() >= 10.1 && bme.readTemperature() <= 0.0) {
    TempJewel.fill(lightBlue, 0, 7);
    TempJewel.show();
  } else if (bme.readTemperature() >= 0.1 && bme.readTemperature() <= 10.0) {
    TempJewel.fill(babyBlue, 0, 7);
    TempJewel.show();
  } else if (bme.readTemperature() >= 10.1 && bme.readTemperature() <= 19.9) {
    TempJewel.fill(pineGreen, 0, 7);
    TempJewel.show();
  } else if (bme.readTemperature() >= 20.0 && bme.readTemperature() <= 25.0) {
    TempJewel.fill(yellow, 0, 7);
    TempJewel.show();
  } else if (bme.readTemperature() >= 25.1 && bme.readTemperature() <= 30.0) {
    TempJewel.fill(orange, 0, 7);
    TempJewel.show();
  } else if (bme.readTemperature() >= 30.1 && bme.readTemperature() <= 35.0) {
    TempJewel.fill(orgRed, 0, 7);
    TempJewel.show();
  } else if (bme.readTemperature() >= 35.1 && bme.readTemperature() <= 60.0) {
    TempJewel.fill(pureRed, 0, 7);
    TempJewel.show();
  } else {
    tempRainbow(10);
    TempJewel.show();
    TempJewel.clear();
  }
}

void HumidReadings() {
  if (bme.readHumidity() >= 0.0 && bme.readHumidity() <= 10.0) {
    HumJewel.fill(lavender, 0, 7);
    HumJewel.show();
  } else if (bme.readHumidity() >= 10.1 && bme.readHumidity() <= 20.0) {
    HumJewel.fill(purpBlue, 0, 7);
    HumJewel.show();
  } else if (bme.readHumidity() >= 20.1 && bme.readHumidity() <= 30.0) {
    HumJewel.fill(plurble, 0, 7);
    HumJewel.show();
  } else if (bme.readHumidity() >= 30.1 && bme.readHumidity() <= 40.0) {
    HumJewel.fill(lightBlue, 0, 7);
    HumJewel.show();
  } else if (bme.readHumidity() >= 40.1 && bme.readHumidity() <= 50.0) {
    HumJewel.fill(bluish, 0, 7);
    HumJewel.show();
  } else if (bme.readHumidity() >= 50.1 && bme.readHumidity() <= 60.0) {
    HumJewel.fill(moreBlue, 0, 7);
    HumJewel.show();
  } else if (bme.readHumidity() >= 60.1 && bme.readHumidity() <= 100.0) {
    HumJewel.fill(pureBlue, 0, 7);
    HumJewel.show();
  } else {
    humidRainbow(10);
    HumJewel.show();
    HumJewel.clear();
  }
}

void PressureReadings() {
  if (bme.readPressure() >= 97000 && bme.readPressure() <= 98400) {
    PresJewel.fill(stormy, 0, 7);
    PresJewel.show();
  } else if (bme.readPressure() >= 98401 && bme.readPressure() <= 99800) {
    PresJewel.fill(rainy, 0, 7);
    PresJewel.show();
  } else if (bme.readPressure() >= 998001 && bme.readPressure() <= 101200) {
    PresJewel.fill(change, 0, 7);
    PresJewel.show();
  } else if (bme.readPressure() >= 101201 && bme.readPressure() <= 102600) {
    PresJewel.fill(fair, 0, 7);
    PresJewel.show();
  } else if (bme.readPressure() >= 102601 && bme.readPressure() <= 105000) {
    PresJewel.fill(dry, 0 ,7);
    PresJewel.show();
  } else if (press < previousPress && bme.readPressure() < 100000) {
    pulseWhite(10);
    PresJewel.show();
    delay(10);
    PresJewel.clear();
    pulseRed(10);
    PresJewel.show();
  } else {
    pressureRainbow(10);
    PresJewel.show();
    delay(20);
  }
}

void pulseWhite(uint8_t wait) {
  for (int j = 0; j < 256; j++) { // Ramp up from 0 to 255
    // Fill entire strip with white at gamma-corrected brightness level 'j':
    PresJewel.fill(PresJewel.Color(0, 0, 0, PresJewel.gamma8(j)));
    PresJewel.show();
    delay(wait);
  }
  for (int j = 255; j >= 0; j--) { // Ramp down from 255 to 0
    PresJewel.fill(PresJewel.Color(0, 0, 0, PresJewel.gamma8(j)));
    PresJewel.show();
    delay(wait);
  }
}

void pulseRed(uint8_t wait) {
  for (int j = 0; j < 256; j++) { // Ramp up from 0 to 255
    // Fill entire strip with white at gamma-corrected brightness level 'j':
    PresJewel.fill(PresJewel.Color(255, 1, 2, PresJewel.gamma8(j)));
    PresJewel.show();
    delay(wait);
  }
  for (int j = 255; j >= 0; j--) { // Ramp down from 255 to 0
    PresJewel.fill(PresJewel.Color(255, 1, 2, PresJewel.gamma8(j)));
    PresJewel.show();
    delay(wait);
  }
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < TempJewel.numPixels(); i++) { 
    TempJewel.setPixelColor(i, color);
    TempJewel.show(); 
    delay(wait); 
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void pressureRainbow(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 3 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < PresJewel.numPixels(); i++) { // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / PresJewel.numPixels());
      PresJewel.setPixelColor(i, PresJewel.gamma32(PresJewel.ColorHSV(pixelHue)));
    }
    PresJewel.show();
    delay(wait);
  }
}

void tempRainbow(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 3 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < TempJewel.numPixels(); i++) { // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / TempJewel.numPixels());
      TempJewel.setPixelColor(i, TempJewel.gamma32(TempJewel.ColorHSV(pixelHue)));
    }
    TempJewel.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

void humidRainbow(int wait) {
  int firstPixelHue = 0; 
  for (int a = 0; a < 30; a++) {
    for (int b = 0; b < 3; b++) { 
      HumJewel.clear(); 
      for (int c = b; c < HumJewel.numPixels(); c += 3) {  
        int      hue   = firstPixelHue + c * 65536L / HumJewel.numPixels();
        uint32_t color = HumJewel.gamma32(HumJewel.ColorHSV(hue)); 
        HumJewel.setPixelColor(c, color); 
      }
      HumJewel.show(); 
      delay(wait);
      firstPixelHue += 65536 / 90;
    }
  }
}
