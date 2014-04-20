#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 16
#define INPUT_PORT 6
#define BLINK_DELAY 5
#define NUM_COLORS 10

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, INPUT_PORT, NEO_GRB + NEO_KHZ800);

int currentPixel = 0;
int direction;
int colorIndex = 0;

// Here is where you can put in your favorite colors that will appear!
// just add new {nnn, nnn, nnn}, lines. They will be picked out randomly
//                                  R   G   B
uint8_t colorList[][NUM_COLORS] = {
  {0, 255, 0},
  {255, 0, 255},
  {0, 255, 0},
  {255, 0, 255},
  {0, 255, 0},
  {255, 0, 255},
  {0, 255, 0},
  {255, 0, 255},
  {0, 255, 0},
  {255, 0, 255}
};

#define FAVCOLORS sizeof(colorList) / NUM_COLORS

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  lightUp();
}

void lightUp() {
  if (++colorIndex == NUM_COLORS) {
    colorIndex = 0;
  }

  int red = colorList[colorIndex][0];
  int green = colorList[colorIndex][1];
  int blue = colorList[colorIndex][2];

  // Bounds detection
  if (currentPixel == 0) {
    direction = 1;
  } else if (currentPixel == NUM_PIXELS) {
    direction = -1;
  }

  // Advancing the pixel
  currentPixel = currentPixel + (1 * direction);

  // now we will 'fade' it in 5 steps
  for (int x = 0; x < 5; x++) {
    int r = red * (x+1); r /= 5;
    int g = green * (x+1); g /= 5;
    int b = blue * (x+1); b /= 5;

    strip.setPixelColor(currentPixel, strip.Color(r, g, b));
    strip.show();
    delay(BLINK_DELAY);
  }

  // & fade out in 5 steps
  for (int x = 5; x >= 0; x--) {
    int r = red * x; r /= 5;
    int g = green * x; g /= 5;
    int b = blue * x; b /= 5;

    strip.setPixelColor(currentPixel, strip.Color(r, g, b));
    strip.show();
    delay(BLINK_DELAY);
  }
}