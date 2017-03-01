#include <Adafruit_CircuitPlayground.h>

const int min_brightness = 0;
const int max_brightness = 35;
const int brightness_delay = 80;

int current_color = 0;
int colors[][3] = { { 255, 0, 0 }, { 0, 0, 223 }, { 0, 223, 0 }, { 169, 223, 20 }, { 20, 217, 223 }, { 20, 33, 223 } };
int colors_count = sizeof(colors[0]) - 1;

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
}

void set_color(int *rgb_colors, int brightness, int brightness_interval) {
  int red = rgb_colors[0];
  int green = rgb_colors[1];
  int blue = rgb_colors[2];

  CircuitPlayground.setBrightness(brightness);

  for(int pixel=0;pixel<10;++pixel) {
    CircuitPlayground.setPixelColor(pixel, red, green, blue);
  }

  delay(brightness_interval);
}

int change_colors(int color) {
  int *rgb_colors = colors[color];

  for(int brightness=min_brightness;brightness<=max_brightness;++brightness) set_color(rgb_colors, brightness, brightness_delay);
  for(int brightness=max_brightness;brightness>=min_brightness;--brightness) set_color(rgb_colors, brightness, brightness_delay);

  if(++color > colors_count) color = 0;

  int *to_rgb_colors = colors[color];

  return(color);
}

void loop() {
  current_color = change_colors(current_color);
}
