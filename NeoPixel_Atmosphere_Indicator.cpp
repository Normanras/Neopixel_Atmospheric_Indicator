#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_NeoPixel.h>

#define SEALEVELPRESSURE_HPA (1028.25)

#define PIN 3 // Temperature Jewel
#define PIN2 2 // Humiditiy Jewel
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(40, PIN); // Temp
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(40, PIN2); // Humidity
Adafruit_BME280 bme; // I2C

// Colors for temperature
//-40.0 to -10.0
uint32_t iceBlue = strip.Color(0, 51, 255);
//-10.1 to 0.0
uint32_t lightBlue = strip.Color(0, 153, 255);
// 0.1 to 10.0
uint32_t babyBlue = strip.Color(51, 204, 255);
//10.1  to 19.9
uint32_t pineGreen = strip.Color(14, 170, 26);
//20.0  to 25.0
uint32_t yellow = strip.Color(255, 229, 0);
//25.1 to 30.0
uint32_t orange = strip.Color(255, 102, 0);
//30.1 to 35.0
uint32_t orgRed = strip.Color(255, 0, 51);
//35.1 to 40.0
uint32_t pureRed = strip.Color(255, 0, 0);

//Colors for humidity
// 0.0 to 10.0%
uint32_t lavender = strip.Color(102, 102, 204);
// 10.1 to 20.0%
uint32_t purpBlue = strip.Color(102, 102, 255);
// 20.1 to 30.0%
uint32_t plurble = strip.Color(102, 153, 255);
// 30.1 to 40.0%
uint32_t lightBlue2 = strip2.Color(0, 153, 255);
//40.1 to 50.0%
uint32_t bluish = strip.Color(51, 153, 255);
//50.1 to 60.0 %
uint32_t moreBlue = strip.Color(51, 0, 255);
// 60 to 100 %
uint32_t pureBlue = strip.Color(0, 0, 255);

void setup() {
  Serial.begin(9600);
//Initialization of the Temp Jewel
  strip.setBrightness(100);
  strip.begin();
  strip.show();
// Initialization of the Humidity Jewel
  strip2.setBrightness(100);
  strip2.begin();
  strip.show();
// Will add the initialization of the barometric pressure Jewel

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  delay(2000);
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println("*C");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println("hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println("m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println("%");

  Serial.println();
  delay(1000);

  if (bme.readTemperature() >= -40.0 && bme.readTemperature() <= -10.0) {
    strip.fill(iceBlue, 0, 7);
    strip.show();
  } else if (bme.readTemperature() >= 10.1 && bme.readTemperature() <= 0.0) {
      strip.fill(lightBlue, 0, 7);
  } else if (bme.readTemperature() >= 0.1 && bme.readTemperature() <= 10.0) {
      strip.fill(babyBlue, 0, 7);
      strip.show();
  } else if (bme.readTemperature() >= 10.1 && bme.readTemperature() <= 19.9) {
      strip.fill(pineGreen, 0, 7);
      strip.show();
  } else if (bme.readTemperature() >= 20.0 && bme.readTemperature() <= 25.0) {
      strip.fill(yellow, 0, 7);
      strip.show();
  } else if (bme.readTemperature() >= 25.1 && bme.readTemperature() <= 30.0) {
      strip.fill(orange, 0, 7);
      strip.show();
  } else if (bme.readTemperature() >= 30.1 && bme.readTemperature() <= 35.0) {
      strip.fill(orgRed, 0, 7);
      strip.show();
  } else if (bme.readTemperature() >= 35.1 && bme.readTemperature() <= 60.0) {
      strip.fill(pureRed, 0, 7);
      strip.show();
  } else {
      rainbow(50);
  }

  if (bme.readHumidity() >= 0.0 && bme.readHumidity() <= 10.0) {
    strip2.fill(lavender, 0, 7);
    strip2.show();
  } else if (bme.readHumidity() >= 10.1 && bme.readHumidity() <= 20.0) {
      strip2.fill(purpBlue, 0, 7);
      strip2.show();
  } else if (bme.readHumidity() >= 20.1 && bme.readHumidity() <= 30.0) {
      strip2.fill(plurble, 0, 7);
      strip2.show();
  } else if (bme.readHumidity() >= 30.1 && bme.readHumidity() <= 40.0) {
      strip2.fill(lightBlue, 0, 7);
      strip2.show();
  } else if (bme.readHumidity() >= 40.1 && bme.readHumidity() <= 50.0) {
      strip2.fill(bluish, 0, 7);
      strip2.show();
  } else if (bme.readHumidity() >= 50.1 && bme.readHumidity() <= 60.0) {
      strip2.fill(moreBlue, 0, 7);
      strip2.show();
  } else if (bme.readHumidity() >= 60.1 && bme.readHumidity() <= 100.0) {
      strip2.fill(pureBlue, 0, 7);
      strip2.show();
  } else {
      strip2.rainbow(10);
  }
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 3 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
  // means we'll make 3*65536/256 = 768 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}