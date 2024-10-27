#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// Define the pins for the TFT display, wire color from diagram in square brackets
#define TFT_BL 1    // Backlight control pin (GPIO1) [Orange wire]
#define TFT_DC 8    // Data/Command control pin (GPIO8) [Yellow wire]
#define TFT_RST 10  // Reset pin (GPIO10) [Green wire]

// The SPI pins are selected by Adafruit_ST7789
// TFT_SCLK 4  // SPI Clock pin (GPIO4) [Brown wire]
// TFT_MOSI 6  // SPI MOSI pin (GPIO6) [Gray wire]

// My display does not have a Chip Select pin, so I will use GPIO7 as a placeholder
#define TFT_CS 7    // Chip Select pin (GPIO7) [Unconnected, not available on display]

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

float p = 3.1415926;

void setup(void) {
  ledcAttach(TFT_BL, 1000, 7); // Attach the backlight pin to a PWM channel
  ledcWrite(TFT_BL, 250);      // Set the backlight brightness

  tft.init(240, 240, SPI_MODE3); // Initialize the display with a resolution of 240x240 pixels
  tft.setSPISpeed(40000000);     // Set the SPI speed to 40 MHz

  return;
}

void loop() {
  tft.fillScreen(ST77XX_BLACK); // Clear the screen
  for (int i = 0; i < 40; i++) { // Draw 40 flowers
    drawFlower();
    delay(200); // Delay between drawing each flower
  }
}

void drawFlower() {
  int x = random(tft.width()); // Random x position
  int y = random(tft.height()); // Random y position
  int radius = random(30, 61); // Random radius between 30 and 60
  uint16_t color = random(0xFFFF); // Random color for the petals

  // Draw the flower
  for (int j = 0; j < 360; j += 45) { // Each flower has 8 petals
    int petalX = x + 0.6 * radius * cos(j * PI / 180.0);
    int petalY = y + 0.6 * radius * sin(j * PI / 180.0);
    tft.fillCircle(petalX, petalY, radius / 4, color); // Petals are 1/4 the size of the flower radius
  }

  uint16_t centerColor = random(0xFFFF); // Random color for the center
  tft.fillCircle(x, y, radius / 2, centerColor); // Draw the center of the flower with a larger size and different color
}
