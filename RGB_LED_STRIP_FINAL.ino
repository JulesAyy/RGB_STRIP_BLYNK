/*
* Name: Jules A. Beszant
* Date: 09/09/20
* 
* This project is a continuation for RGB_LED_FINAL. 
* The extra lines of code will result in the same function as the previous project,
* but will be controlling the WS2812B RGB LED Strip through the Blynk app.
* 
*   PCB Design: https://i.imgur.com/pe9A32Ch.jpg
*/

#include <FastLED.h>
#define DATA_PIN 6
#define NUM_LEDS 60

CRGB leds[NUM_LEDS];

#define BLYNK_USE_DIRECT_CONNECT

#include <SoftwareSerial.h>
SoftwareSerial hc05(0,1); // RX, TX

#define BLYNK_PRINT hc05
#include <BlynkSimpleSerialBLE.h>

char auth[] = "UJ1ORPc18mMN8LkkBIfNVA4lODvB2hDI";

int r,g,b;

void setup() 
{
  // Setup bluetooth connection
  // HC05 uses a baud rate of 9600, not 38400
  Serial.begin(9600);
  Blynk.begin(Serial, auth);

  FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);
}

void loop() 
{  
  Blynk.run();
}


BLYNK_WRITE(V3) // zeRGBa
{
  r = param[0].asInt();
  g = param[1].asInt();
  b = param[2].asInt();

  static1(r, g, b);
}

void static1(int r, int g, int b)
{
  for (int led = 0; led < NUM_LEDS; led++)
  {
    leds[led] = CRGB(g, r, b);
  }
  FastLED.show();
}
