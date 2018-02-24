#include "FastLED.h"
// How many leds in your strip?
#define NUM_LEDS 16
#define DATA_PIN 11
// Define the array of leds
CRGB leds[NUM_LEDS];


//config variables
#define NUM_BTN_COLUMNS (4)
#define NUM_BTN_ROWS (4)
#define MAX_DEBOUNCE (1)

// Global variables
static int32_t next_scan;
static const uint8_t btnselpins[4]   = {6,7,8,9}; // Gnd select pins
static const uint8_t btnreadpins[4] = {2,3,4,5};  // Switch select pins
static int8_t debounce_count[NUM_BTN_COLUMNS][NUM_BTN_ROWS];

static void setuppins()
{
    uint8_t i;
    // initialize
    // select lines
//    for(i = 0; i < NUM_LED_COLUMNS; i++)
//    {
//        pinMode(ledselpins[i], OUTPUT);
        // with nothing selected by default
//        digitalWrite(ledselpins[i], HIGH);
//    }
    for(i = 0; i < NUM_BTN_COLUMNS; i++)
    {
        pinMode(btnselpins[i], OUTPUT);
        // with nothing selected by default
        digitalWrite(btnselpins[i], HIGH);
    }
    // key return lines
    for(i = 0; i < 4; i++)
    {
        pinMode(btnreadpins[i], INPUT_PULLUP);
    }

    for(uint8_t i = 0; i < NUM_BTN_COLUMNS; i++)
    {
        for(uint8_t j = 0; j < NUM_BTN_ROWS; j++)
        {
            debounce_count[i][j] = 0;
        }
    }
}

static void scan()
{
  static uint8_t current = 0;
  uint8_t val;
  uint8_t i, j;

    //run
    digitalWrite(btnselpins[current], LOW);
//    digitalWrite(ledselpins[current], LOW);

//    for(i = 0; i < NUM_LED_ROWS; i++)
//    {
//        uint8_t val = (LED_outputs[current][i] & 0x03);
//        if(val)
//        {
//            digitalWrite(colorpins[i][val-1], HIGH);
//        }
//  }

  delay(1);

  for( j = 0; j < NUM_BTN_ROWS; j++)
  {
    val = digitalRead(btnreadpins[j]);

    if(val == LOW)
    {
      // active low: val is low when btn is pressed
      if( debounce_count[current][j] < MAX_DEBOUNCE)
      {
        debounce_count[current][j]++;
        if( debounce_count[current][j] == MAX_DEBOUNCE )
        {
          Serial.print("Key_Down_");
          Serial.println((current * NUM_BTN_ROWS) + j);
  leds[(current * NUM_BTN_ROWS) + j] = CRGB::Blue;
  FastLED.show();
        }
      }
    }
    else
    {
      // otherwise, button is released
      if( debounce_count[current][j] > 0)
      {
        debounce_count[current][j]--;
        if( debounce_count[current][j] == 0 )
        {
          Serial.print("Key_Up_");
          Serial.println((current * NUM_BTN_ROWS) + j);
  leds[(current * NUM_BTN_ROWS) + j] = CRGB::Black;
  FastLED.show();
//  delay(500);
        }
      }
    }
  }
// for j = 0 to 3;

  delay(1);

  digitalWrite(btnselpins[current], HIGH);
//  digitalWrite(ledselpins[current], HIGH);

//  for(i = 0; i < NUM_LED_ROWS; i++)
//  {
//    for(j = 0; j < NUM_COLORS; j++)
//    {
 //     digitalWrite(colorpins[i][j], LOW);
//    }
//  }

  current++;
  if (current >= NUM_BTN_COLUMNS)
  {
    current = 0;
  }
}

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  // setup hardware
  setuppins();

  // init global variables
  next_scan = millis() + 1;

  Serial.println("Button Matrix Loaded...");

      // Uncomment/edit one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
      // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
  //for(uint8_t i = 0; i < NUM_LEDS; i++)  {  leds[i] = CRGB::Red; } FastLED.show();  // fill all leds red

}

void loop() {
  // put your main code here, to run repeatedly:

  if(millis() >= next_scan)
  {
    next_scan = millis()+1;
    scan();
  }
}

