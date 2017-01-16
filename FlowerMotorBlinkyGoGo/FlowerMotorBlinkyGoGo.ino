#include <Adafruit_NeoPixel.h>
#ifdef __AVR_ATtiny85__ // Trinket, Gemma, etc.
#include <avr/power.h>
#endif
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
#define PIN 6
#define Pixels 15

Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pixels, PIN, NEO_GRB + NEO_KHZ800);

int fadeRate = 50;
int MaxBrightness = 255;
int TotalSteps = 2;
void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  strip.begin();
  for (int i = 0; i < Pixels; i++)
  {
    strip.setPixelColor(i, random(0, MaxBrightness), random(0, MaxBrightness), random(0, 50));
  }
  strip.show(); // Initialize all pixels to a Random Color.

}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    doittoit(int(random(0, Pixels+1)));
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    doittoit(int(random(0, Pixels+1)));
  }
}

void doittoit(int LEDNumber){

  uint8_t LED = LEDNumber;  // Pick a random pixel
  // Get the colors of the current pixel.
  uint32_t c = strip.getPixelColor(LED);
  uint8_t  redCur = (c >> 16) & 0xFF;
  uint8_t  greenCur = (c >>  8) & 0xFF;
  uint8_t  blueCur = c & 0xFF;
  //Pick a new random color
  uint8_t redNew = random(0, MaxBrightness);
  uint8_t greenNew = random(0, MaxBrightness);
  uint8_t blueNew = random(0, 100);
  // Start fade between the two colors
  for (int i = 1; i < TotalSteps; i++)
  {
    uint8_t red = (((redCur * (TotalSteps - i)) + (redNew * i)) / TotalSteps);
    uint8_t green = (((greenCur * (TotalSteps - i)) + (greenNew * i)) / TotalSteps);
    uint8_t blue = (((blueCur * (TotalSteps - i)) + (blueNew * i)) / TotalSteps);
    // Sets the pixel to the color adjusted in the fade
    strip.setPixelColor(LED, red, green, blue/2);
    strip.show();
    delay(fadeRate);
  }
  delay(10);
}


