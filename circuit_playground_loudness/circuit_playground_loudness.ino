//----------------------------------------------------------------------------------------------------
//  circuit_playground_loudness displays the surrounding loudness level using the neopixels
//  using increasing brightness
//
//  author frank morton
//  copyright 2017 base2 incorporated
//  mit license (https://opensource.org/licenses/MIT)
//----------------------------------------------------------------------------------------------------
#include <Adafruit_CircuitPlayground.h>

const int minimum_noise_level = 100;
const int maximum_noise_level = 999;
const int average_noise_level_sample_count = 16;
const int debugging = true;

int average_noise_level_stack[average_noise_level_sample_count];

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();

  for(int k=0;k<average_noise_level_sample_count;++k) average_noise_level_stack[k] = 333;

  if(debugging) {
    print_stack("init ", true);
  }
}

void push_noise_level(int noise_level) {
  if(noise_level < minimum_noise_level) noise_level = minimum_noise_level;
  if(noise_level > maximum_noise_level) noise_level = maximum_noise_level;

  for(int k=(average_noise_level_sample_count-1);k>0;--k) average_noise_level_stack[k] = average_noise_level_stack[k-1];
  average_noise_level_stack[0] = noise_level;
  print_stack("stack", false);
}

int average_noise_level() {
  int calculated_average = 0;

  for(int k=0;k<average_noise_level_sample_count;++k) calculated_average = calculated_average + average_noise_level_stack[k];

  return(calculated_average / average_noise_level_sample_count);
}

//----------------------------------------------------------------------------------------------------
//  listen for the noise level and display the noise level using neopixel brightness
//----------------------------------------------------------------------------------------------------
void loop() {
  push_noise_level(analogRead(A4));

  int brightness = (int) map(average_noise_level(), 320.0, 500.0, 0.0, 35.0);

  CircuitPlayground.setBrightness(brightness);

  for(int pixel=0;pixel<10;++pixel) {
    CircuitPlayground.setPixelColor(pixel, 255, 80, 80);
  }

  delay(100);
}

//----------------------------------------------------------------------------------------------------
//  print the current noise level stack with average
//----------------------------------------------------------------------------------------------------
void print_stack(char *identifier, int wait_for_serial) {
  if(wait_for_serial) {
    Serial.begin(9600); while (!Serial);
  }
  
  Serial.print(identifier);
  Serial.print(" ");

  for(int k=0;k<average_noise_level_sample_count;++k) {
    Serial.print(average_noise_level_stack[k]);
    Serial.print(" ");
  }

  Serial.print("average: ");
  Serial.println(average_noise_level());
}

