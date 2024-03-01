#include <Adafruit_NeoPixel.h>

// CONFIG /////////////////////////////////////////////////////////////////////////////////
#define LED_PIN        6
#define LED_COUNT      232
#define WAKE_DELAY_MIN 15
#define MAX_BRIGHTNESS 230
///////////////////////////////////////////////////////////////////////////////////////////

const unsigned long WAKE_DELAY_MS          = long(WAKE_DELAY_MIN) * 60 * 1000;
const unsigned long INCREASE_BLUE_MS       =     WAKE_DELAY_MS / 4;
const unsigned long INCREASE_WARM_WHITE_MS = 2 * WAKE_DELAY_MS / 4;
const unsigned long INCREASE_COOL_WHITE_MS =     WAKE_DELAY_MS / 4;
const int MAX_WARM_WHITE = MAX_BRIGHTNESS;
const int MAX_BLUE       = MAX_BRIGHTNESS / 5;
const int MAX_COOL_WHITE = MAX_BRIGHTNESS;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800);
float red, green, blue, white = 0;
uint32_t color = strip.Color(int(red), int(green), int(blue), int(white));
int steps_count;

void setup() {
  // Serial.begin(9600);
  // Serial.println();

  strip.begin();
  strip.show();

  // unsigned long start = millis();

  steps_count = MAX_BLUE - blue;
  for(blue; blue < MAX_BLUE; blue++)
  { 
    red   = blue / 2;
    green = red / 10;

    color = strip.Color(int(red), int(green), int(blue), int(white));
    strip.fill(color);
    strip.show();

    delay(INCREASE_BLUE_MS / steps_count);
  }

  steps_count = MAX_WARM_WHITE - white;
  for(white; white < MAX_WARM_WHITE; white++)
  {
    red   += 0.5;
    green = red / 10;

    color = strip.Color(int(red), int(green), int(blue), int(white));
    strip.fill(color);
    strip.show();

    delay(INCREASE_WARM_WHITE_MS / steps_count);
  }

  int cool_white = min(red, min(green, blue));
  steps_count = MAX_COOL_WHITE - cool_white;  
  for(cool_white; cool_white < MAX_COOL_WHITE; cool_white++)
  {
    if(red   < cool_white) red   = cool_white;
    if(green < cool_white) green = cool_white;
    if(blue  < cool_white) blue  = cool_white;

    color = strip.Color(int(red), int(green), int(blue), int(white));
    strip.fill(color);
    strip.show();

    delay(INCREASE_COOL_WHITE_MS / steps_count);
  }

  // unsigned long delay = millis() - start;
  // Serial.println(delay / 1000);
}
 
void loop() {

}