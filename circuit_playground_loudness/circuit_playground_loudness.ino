//----------------------------------------------------------------------------------------------------
//  circuit_playground_loudness displays the surrounding loudness level using the neopixels
//  using increasing brightness
//
//  author frank morton
//  copyright 2017 base2 incorporated
//  mit license (https://opensource.org/licenses/MIT)
//----------------------------------------------------------------------------------------------------
#include <Adafruit_CircuitPlayground.h>

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
}

//----------------------------------------------------------------------------------------------------
//  listen for the noise level and display the noise level using neopixel brightness
//----------------------------------------------------------------------------------------------------
void loop() {
  uint16_t noise_level = analogRead(A4);

  int brightness = (int) map(noise_level, 320.0, 500.0, 0.0, 35.0);

  CircuitPlayground.setBrightness(brightness);

  for(int pixel=0;pixel<10;++pixel) {
    CircuitPlayground.setPixelColor(pixel, 255, 80, 80);
  }

  delay(250);
}

