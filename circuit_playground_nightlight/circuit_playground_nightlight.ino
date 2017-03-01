#include <Adafruit_CircuitPlayground.h>

const int min_brightness = 3;
const int max_brightness = 35;
const int brightness_delay = 80;
const int transition_delay = 5;
const int active_nightlight_light_level = 10;
const int inactive_nightlight_delay = 2000;

int current_color = 0;
int colors[][3] = { { 255, 0, 0 }, { 0, 0, 223 }, { 0, 223, 0 }, { 169, 223, 20 }, { 20, 217, 223 }, { 20, 33, 223 } };
int colors_count = sizeof(colors[0]) - 1;

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.clearPixels();
}

void set_color(int red, int green, int blue, int brightness, int brightness_interval) {
  CircuitPlayground.setBrightness(brightness);

  for(int pixel=0;pixel<10;++pixel) {
    CircuitPlayground.setPixelColor(pixel, red, green, blue);
  }

  delay(brightness_interval);
}

int next_transition_color(int from, int to) {
  if (from < to) return(++from);
  if (from > to) return(--from);
  return(from);
}

void transition_colors(int *from_rgb_colors, int *to_rgb_colors) {
  int red = from_rgb_colors[0];
  int green = from_rgb_colors[1];
  int blue = from_rgb_colors[2];

  while ((red != to_rgb_colors[0]) || (green != to_rgb_colors[1]) || (blue != to_rgb_colors[2])) {
    red = next_transition_color(red, to_rgb_colors[0]);
    green = next_transition_color(green, to_rgb_colors[1]);
    blue = next_transition_color(blue, to_rgb_colors[2]);

    set_color(red, green, blue, min_brightness, transition_delay);
  }
}

int change_colors(int color) {
  int *rgb_colors = colors[color];

  int red = rgb_colors[0];
  int green = rgb_colors[1];
  int blue = rgb_colors[2];

  for(int brightness=min_brightness;brightness<=max_brightness;++brightness) set_color(red, green, blue, brightness, brightness_delay);
  for(int brightness=max_brightness;brightness>=min_brightness;--brightness) set_color(red, green, blue, brightness, brightness_delay);

  if(++color > colors_count) color = 0;

  if((min_brightness > 0) && active_nightlight()) {
    int *to_rgb_colors = colors[color];

    transition_colors(rgb_colors, to_rgb_colors);
  }

  return(color);
}

void deactive_nightlight() {
  CircuitPlayground.clearPixels();

  current_color = 0;
}

boolean active_nightlight() {
  if(CircuitPlayground.slideSwitch()) return(true);
  if(analogRead(A5) <= active_nightlight_light_level) return(true);

  deactive_nightlight();

  delay(inactive_nightlight_delay);

  return(false);
}

void loop() {
  if(active_nightlight()) {
    current_color = change_colors(current_color);
  }
}
