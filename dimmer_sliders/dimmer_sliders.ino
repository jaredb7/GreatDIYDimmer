// --- setup of slider paramters
// >left <right <up >down
int aa=145, bb=115, cc=120, dd=146;

// ----- Version 1.1 -----
#include "FastLED.h"
// How many leds in your strip?
#define NUM_LEDS 64
#define DATA_PIN 3
#define COLOR_ORDER GRB
#define BRIGHTNESS 96
#define FRAMES_PER_SECOND  120
// Define the array of leds
CRGB leds[NUM_LEDS];
int stick=1,j1hc=0,j1vc=0,j2hc=0,j2vc=0,j3hc=0,j3vc=0,j4hc=0,j4vc=0;
#include <Wire.h>
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads0(0x48);     /* Dimming Module #1 x48 */
Adafruit_ADS1115 ads1(0x49);     /* Dimming Module #2 x49 */
Adafruit_ADS1115 ads2(0x4A);     /* Dimming Module #3 x4A */
Adafruit_ADS1115 ads3(0x4B);     /* Dimming Module #4 x4B */
int16_t slid1=0, slidold1=0, slid2=0, slidold2=0, slid3=0, slidold3=0, slid4=0, slidold4=0, slid5=0, slidold5=0, slid6=0, slidold6=0, slid7=0, slidold7=0, slid8=0, slidold8=0;
int but1=0, butold1=0, but2=0, butold2=0, but3=0, butold3=0, but4=0, butold4=0,but5=0, butold5=0, but6=0, butold6=0, but7=0, butold7=0, but8=0, butold8=0, joyold1=0, joyold2=0, joyold3=0, joyold4=0, joyold5=0, joyold6=0, joyold7=0, joyold8=0; 
int16_t joy0, joy1, joy2, joy3, joy4, joy5, joy6, joy7, x=0;
String inputString = "", RFID="loading";
boolean stringComplete = false;
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void setup() 
{      uint8_t i;  int x=200; // delay in startup scroll of leds (fake loading - Delay)
  //Serial.begin(115200);
  Serial.begin(2000000);
  inputString.reserve(200);
  ads0.begin();  //ads0.setGain(GAIN_TWOTHIRDS);
  ads1.begin();  //ads1.setGain(GAIN_TWOTHIRDS);
  ads2.begin();  //ads2.setGain(GAIN_TWOTHIRDS);
  ads3.begin();  //ads3.setGain(GAIN_TWOTHIRDS);
  pinMode(6, INPUT);  pinMode(7, INPUT);  pinMode(8, INPUT);  pinMode(9, INPUT);  // joystick buttons
  pinMode(6, INPUT_PULLUP); pinMode(7, INPUT_PULLUP); pinMode(8, INPUT_PULLUP); pinMode(9, INPUT_PULLUP); 
  FastLED.addLeds<WS2811, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);  FastLED.setBrightness(BRIGHTNESS);
  pinMode(2, OUTPUT);  pinMode(4, OUTPUT);  pinMode(5, OUTPUT);
  digitalWrite(2, HIGH);  digitalWrite(4, HIGH);  digitalWrite(5, HIGH);
//rfid_fail();
}

void slid_start() 
{
  slid1 = ads0.readADC_SingleEnded(0)/100;  Serial.print("SL_1:"); Serial.println(slid1);
  slid2 = ads0.readADC_SingleEnded(1)/100;  Serial.print("SL_2:"); Serial.println(slid2);
  slid3 = ads1.readADC_SingleEnded(0)/100;  Serial.print("SL_3:"); Serial.println(slid3);
  slid4 = ads1.readADC_SingleEnded(1)/100;  Serial.print("SL_4:"); Serial.println(slid4);
  slid5 = ads2.readADC_SingleEnded(0)/100;  Serial.print("SL_5:"); Serial.println(slid5);
  slid6 = ads2.readADC_SingleEnded(1)/100;  Serial.print("SL_6:"); Serial.println(slid6);
  slid7 = ads3.readADC_SingleEnded(0)/100;  Serial.print("SL_7:"); Serial.println(slid7);
  slid8 = ads3.readADC_SingleEnded(1)/100;  Serial.print("SL_8:"); Serial.println(slid8);
  but1 = digitalRead(6);  Serial.print("JB_1:"); Serial.println(but1);  but2 = digitalRead(7);  Serial.print("JB_2:"); Serial.println(but2);
  but3 = digitalRead(8);  Serial.print("JB_3:"); Serial.println(but3);  but4 = digitalRead(9);  Serial.print("JB_4:"); Serial.println(but4);
}

void serial_output() 
{
  slid1 = ads0.readADC_SingleEnded(0)/100;  if (slid1!=slidold1) { slidold1=slid1; Serial.print("SL_1:"); Serial.println(slidold1); }
  slid2 = ads0.readADC_SingleEnded(1)/100;  if (slid2!=slidold2) { slidold2=slid2; Serial.print("SL_2:"); Serial.println(slidold2); }
  slid3 = ads1.readADC_SingleEnded(0)/100;  if (slid3!=slidold3) { slidold3=slid3; Serial.print("SL_3:"); Serial.println(slidold3); }
  slid4 = ads1.readADC_SingleEnded(1)/100;  if (slid4!=slidold4) { slidold4=slid4; Serial.print("SL_4:"); Serial.println(slidold4); }
  slid5 = ads2.readADC_SingleEnded(0)/100;  if (slid5!=slidold5) { slidold5=slid5; Serial.print("SL_5:"); Serial.println(slidold5); }
  slid6 = ads2.readADC_SingleEnded(1)/100;  if (slid6!=slidold6) { slidold6=slid6; Serial.print("SL_6:"); Serial.println(slidold6); }
  slid7 = ads3.readADC_SingleEnded(0)/100;  if (slid7!=slidold7) { slidold7=slid7; Serial.print("SL_7:"); Serial.println(slidold7); }
  slid8 = ads3.readADC_SingleEnded(1)/100;  if (slid8!=slidold8) { slidold8=slid8; Serial.print("SL_8:"); Serial.println(slidold8); }
  but1 = digitalRead(6);  if (but1!=butold1) { butold1=but1; Serial.print("JB_1:"); Serial.println(butold1); }
  but2 = digitalRead(7);  if (but2!=butold2) { butold2=but2; Serial.print("JB_2:"); Serial.println(butold2); }
  but3 = digitalRead(8);  if (but3!=butold3) { butold3=but3; Serial.print("JB_3:"); Serial.println(butold3); }
  but4 = digitalRead(9);  if (but4!=butold4) { butold4=but4; Serial.print("JB_4:"); Serial.println(butold4); }
  joy0 = map(ads0.readADC_SingleEnded(3), 0, 24600, 0, 255);  if (joy0!=joyold1) { joyold1=joy0;
    if (stick==1) {  if (joy0>=aa) { Serial.println("JS_1:LL"); j1hc=0; } else if (joy0<=bb) { Serial.println("JS_1:RR"); j1hc=0; }
    if ((joy0>=bb+2) && (joy0<=aa-2) && (j1hc==0)){ Serial.println("JS_1:HC"); j1hc=1; }  }else{ Serial.print("JH_1:");  Serial.println(joy0);  }  }
  joy1 = map(ads0.readADC_SingleEnded(2), 0, 24600, 0, 255);  if (joy1!=joyold2) { joyold2=joy1;
    if (stick==1) {  if (joy1<=cc-1) { Serial.println("JS_1:UU"); j1vc=0; } else if (joy1>=dd) { Serial.println("JS_1:DD"); j1vc=0; }
    if ((joy1>=cc+2) && (joy1<=dd-2) && (j1vc==0)){ Serial.println("JS_1:VC");  j1vc=1;}  }else{ Serial.print("JV_1:");  Serial.println(joy1);  }  }  
  joy2 = map(ads1.readADC_SingleEnded(2), 0, 24600, 0, 255);  if (joy2!=joyold3) { joyold3=joy2;
    if (stick==1) {  if (joy2>=aa) { Serial.println("JS_2:LL"); j2hc=0; } else if (joy2<=bb) { Serial.println("JS_2:RR"); j2hc=0; }
    if ((joy2>=bb+2) && (joy2<=aa-2) && (j2hc==0)){ Serial.println("JS_2:HC"); j2hc=1; }  }else{ Serial.print("JH_2:");  Serial.println(joy2);  }  }
  joy3 = map(ads1.readADC_SingleEnded(3), 0, 24600, 0, 255);  if (joy3!=joyold4) { joyold4=joy3;
    if (stick==1) {  if (joy3<=cc-1) { Serial.println("JS_2:UU"); j2vc=0; } else if (joy3>=dd) { Serial.println("JS_2:DD"); j2vc=0; }
    if ((joy3>=cc+2) && (joy3<=dd-2) && (j2vc==0)){ Serial.println("JS_2:VC"); j2vc=1; }  }else{ Serial.print("JV_2:");  Serial.println(joy3);  }  }  
  joy4 = map(ads2.readADC_SingleEnded(3), 0, 24600, 0, 255);  if (joy4!=joyold5) { joyold5=joy4;
    if (stick==1) {  if (joy4>=aa) { Serial.println("JS_3:LL"); j3hc=0; } else if (joy4<=bb) { Serial.println("JS_3:RR"); j3hc=0; }
    if ((joy4>=bb+2) && (joy4<=aa-2) && (j3hc==0)){ Serial.println("JS_3:HC"); j3hc=1; }  }else{ Serial.print("JH_3:");  Serial.println(joy4);  }  }
  joy5 = map(ads2.readADC_SingleEnded(2), 0, 24600, 0, 255);  if (joy5!=joyold6) { joyold6=joy5;
    if (stick==1) {  if (joy5<=cc-1) { Serial.println("JS_3:UU"); j3vc=0; } else if (joy5>=dd) { Serial.println("JS_3:DD"); j3vc=0; }
    if ((joy5>=cc+2) && (joy5<=dd-2) && (j3vc==0)){ Serial.println("JS_3:VC"); j3vc=1; }  }else{ Serial.print("JV_3:");  Serial.println(joy5);  }  }  
  joy6 = map(ads3.readADC_SingleEnded(2), 0, 24600, 0, 255);  if (joy6!=joyold7) { joyold7=joy6;
    if (stick==1) {  if (joy6>=aa) { Serial.println("JS_4:LL"); j4hc=0; } else if (joy6<=bb) { Serial.println("JS_4:RR"); j4hc=0; }
    if ((joy6>=bb+2) && (joy6<=aa-2) && (j4hc==0)){ Serial.println("JS_4:HC"); j4hc=1; }  }else{ Serial.print("JH_4:");  Serial.println(joy6);  }  }
  joy7 = map(ads3.readADC_SingleEnded(3), 0, 24600, 0, 255);  if (joy7!=joyold8) { joyold8=joy7; 
    if (stick==1) {  if (joy7<=cc-1) { Serial.println("JS_4:UU"); j4vc=0; } else if (joy7>=dd) { Serial.println("JS_4:DD"); j4vc=0; } 
    if ((joy7>=cc+2) && (joy7<=dd-2) && (j4vc==0)){ Serial.println("JS_4:VC"); j4vc=1; }  }else{ Serial.print("JV_4:");  Serial.println(joy7);  }  }  
}

void loop() 
{
 serialEvent();
 if (stringComplete) {   inputString.trim();
  if (inputString=="RFID_PASS") { RFID="pass"; rfid_pass(); slid_start(); inputString = "";    stringComplete = false;}
  if (inputString=="RFID_FAIL") { RFID="fail"; rfid_fail();  inputString = "";    stringComplete = false;}
  if (inputString=="RFID_ADMIN") { RFID="admin"; rfid_admin();  inputString = "";    stringComplete = false;}
  if (inputString=="Stick") { if (stick==1) stick=0; else if (stick==0) stick=1;  inputString = "";    stringComplete = false;  }
 }
 if (RFID=="fail") rfid_fail();
 if (RFID=="pass") serial_output();
}

void serialEvent(){ if (Serial.available() > 0) {  while (Serial.available()) {  char inChar = (char)Serial.read(); inputString += inChar;    if (inChar == '\n') {  stringComplete = true;  }  } } }

void rfid_fail()
{
digitalWrite(2, LOW);
digitalWrite(4, HIGH);
digitalWrite(5, HIGH);
  // a colored dot sweeping back and forth, with fading trails
//  fadeToBlackBy( leds, NUM_LEDS, 20);
//  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
//  leds[pos] += CHSV( 0, 255, 192);
//  FastLED.show();  
//  EVERY_N_MILLISECONDS( 10 ) { gHue++;  /* Serial.println("."); */ } // slowly cycle the "base color" through the rainbow
}
void rfid_admin()
{
digitalWrite(2, HIGH);
digitalWrite(4, LOW);
digitalWrite(5, HIGH);
  // a colored dot sweeping back and forth, with fading trails
//  fadeToBlackBy( leds, NUM_LEDS, 20);
//  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
//  leds[pos] += CHSV( 160, 255, 128); //// CHSV( colour_wheel, rich, bright);
//  FastLED.show();  
}
void rfid_pass()
{
digitalWrite(2, HIGH);
digitalWrite(4, HIGH);
digitalWrite(5, LOW);
  // a colored dot sweeping back and forth, with fading trails
//  fadeToBlackBy( leds, NUM_LEDS, 20);
//  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
//  leds[pos] += CHSV( 96, 255, 128); //// CHSV( colour_wheel, rich, bright);
//  FastLED.show();  
}
