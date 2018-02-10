int bootmode=1; // what mode to start up with at boot time

#include <Wire.h>
#include <SPI.h>  
#include <MFRC522.h>    // Library for Mifare RC522 Devices
#include "SdFat.h"
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h> // Hardware-specific library
//#include <UTFT.h>
#include <UTFTGLUE.h>
UTFTGLUE myGLCD(0x9488,A2,A1,A3,A4,A0);
//Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

int mic=A6;
int linein=A7;
int sensorvalue=0,lastsensorvalue=0,lastminsensorvalue=1024,oldsensorvalue=0;
int i;
int led[]={22,24,26,28,30,32};
int val;


#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       
#include <TouchScreen.h>
#if ENABLE_SOFTWARE_SPI_CLASS  // Must be set in SdFat/SdFatConfig.h
//*****************************************************************************8
const uint8_t SOFT_MISO_PIN = 12;
const uint8_t SOFT_MOSI_PIN = 11;
const uint8_t SOFT_SCK_PIN  = 13;

// Chip select may be constant or RAM variable.
const uint8_t SD_CHIP_SELECT_PIN = 10;

// SdFat software SPI template
SdFatSoftSpi<SOFT_MISO_PIN, SOFT_MOSI_PIN, SOFT_SCK_PIN> sd;

MFRC522 mfrc522(53, 49);  // Create MFRC522 instance.
//MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
SdFile file;
File myFile;

//Sd2Card card;
//SdFile root;
String inputString = "", inputString1 = "", inputString2 = "", inputString3 = "", timer = "", dater = "";         // a String to hold incoming data
boolean stringComplete = false,stringComplete1 = false,stringComplete2 = false,stringComplete3 = false;  // whether the string is complete

    int xR=38;
    int xG=38;
    int xB=38;

int S1old=0,S2old=0,S3old=0,S4old=0,S5old=0,S6old=0,S7old=0,S8old=0, oldtime, rfidaccess=0;
String cardid;
boolean match = false;          // initialize card match to false
boolean programMode = false;  // initialize programming mode to false
int successRead=0,refresh=1,RFIDPASS=0,menusel=0;    // Variable integer to keep if we have Successful Read from Reader
byte readCard[4];   // Stores scanned ID read from RFID Module
byte masterCard[4];   // Stores master card's ID
char filename[] = "XXXXXXXXXXXXXXX.DAT";  // Stores variable filename
char extension[] = "DAT";          // sometimes the extension gets modified
char dir[] = "/PICCS/";
char dirdata[] = "/PICCS/";
//char dirdata[] = "/SHOWS/";
char currentPage, selectedUnit;

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

// TouchScreen ts = TouchScreen(7, A2, A1, 6, 300);
 TouchScreen ts = TouchScreen(6, A1, A2, 7, 300);
//TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define SWAP(a, b) {uint16_t tmp = a; a = b; b = tmp;}

int16_t BOXSIZE;
int16_t PENRADIUS = 3;
uint16_t identifier, oldcolor, currentcolor;
uint8_t Orientation = 1;    //PORTRAIT
byte x = 0;
int y = 0;

#include "DS3231.h"
RTClib RTC;

//#define BLACK   0x0000  //white
//#define BLUE    0x001F  //yellow
//#define RED     0xF800  /light blue
//#define GREEN   0x07E0  //purple
//#define CYAN    0x07FF
//#define MAGENTA 0xF81F
//#define YELLOW  0xFFE0  //blue
//#define WHITE   0xFFFF  //black
//
#define BLACK   0xFFFF  //black
#define BLUE    0x001F  //yellow
#define RED     0xF800  //light blue
#define GREEN   0x07E0  //purple
#define CYAN    0x07FF  //
#define MAGENTA 0xF81F  //
#define YELLOW  0xFFE0  //blue
#define WHITE   0x0000  //white

//*****************************************************************************8

void setup()
{
SPI.begin();
Serial.begin(115200);  inputString.reserve(200);  // Initialize serial communications with Sliders Board
Serial1.begin(115200);  inputString1.reserve(200);  // Initialize serial communications with Buttons Board
Serial2.begin(115200);  inputString2.reserve(200);  // Initialize serial communications with USB Stick Recorder
Serial3.begin(115200);  inputString3.reserve(200);  // Initialize serial communications with { 2x DMX, Pixel, Midi in/out } - Output Board
Wire.begin();        // join i2c bus ( as Master ) Arduino 2560 - Touch LCD
//  Wire.begin(1);   // join i2c bus ( as Master ) Arduino Uno  - USB Stick Recorder
//  Wire.begin(2);   // join i2c bus ( as Master ) Arduino 2560 - { 2x DMX, Pixel, Midi in/out } - Output Board
Wire.onReceive(receiveI2C); // register event

 if (!sd.begin(SD_CHIP_SELECT_PIN)) {    Serial.println("initialization failed!");    sd.initErrorHalt();  }

   mfrc522.PCD_Init();    // Initialize MFRC522 Hardware
   mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);
   ShowReaderDetails();   // Show details of PCD - MFRC522 Card Reader details

   DateTime now = RTC.now();

//   while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
//  }
  randomSeed(analogRead(5));   //.kbv Due does not like A0
    pinMode(A0, OUTPUT);       //.kbv mcufriend have RD on A0
    digitalWrite(A0, HIGH);
  
// Setup the LCD
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.setRotation(3);
//  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.fillScreen(BLACK);
//rfid_startup();
//introscreen();

  currentPage = '9'; RFID(); currentPage = rfidaccess;  //rfid - locks system till Correct RFID card is scanned  then loads in our access level  -- RFID
//  sdcard_startup();  // loads up sd card info
}

void serialEvent(){ 
  if (Serial.available() > 0) {
  while (Serial.available()) {  
   char DataS=Serial.read();
 //   if (bootmode==1) {  Serial3.write(DataS);  }   // Direct sliders to outputs
    char inChar = DataS; inputString += inChar;    if (inChar == '\n') {      stringComplete = true;    } }
}
}

void serialEvent1(){  // Slidders Input
  if (Serial1.available() > 0) {
  while (Serial1.available()) {    char inChar1 = (char)Serial1.read();    inputString1 += inChar1;    if (inChar1 == '\n') {      stringComplete1 = true;    } }
}
}

void serialEvent2(){  // Buttons Input
  if (Serial2.available() > 0) {
  while (Serial2.available()) {    char inChar2 = (char)Serial2.read();    inputString2 += inChar2;    if (inChar2 == '\n') {      stringComplete2 = true;    } }
} 
}

void serialEvent3(){  // Storage Input
  if (Serial3.available() > 0) {
  while (Serial3.available()) {    char inChar3 = (char)Serial3.read();    inputString3 += inChar3;    if (inChar3 == '\n') {      stringComplete3 = true;    } }
} 
}

void receiveI2C(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}

void loop()
{
showtimer(1); //lcd graphics
//Serial.println("test point 1 ");
//Serial.println("test point 2 ");
serialEvent1();
serialEvent2();
serialEvent3();
if (stringComplete) {   Serial.print("Input USB- ");  Serial.println(inputString);    inputString = "";    stringComplete = false;  }
  if (stringComplete1) {  Serial.print("Input Sliders- ");  Serial.println(inputString1);  if (inputString1=="Sliders_Ready") Serial1.print("RFID_FAIL");  inputString1 = "";    stringComplete1 = false;  }
  if (stringComplete2) {  Serial.print("Input Buttons- ");  Serial.println(inputString2);  if (inputString2=="Buttons_Ready") Serial1.print("RFID_FAIL");  inputString2 = "";    stringComplete2 = false;  }
  if (stringComplete3) {  Serial.print("Input Storage- ");  Serial.println(inputString3);  if (inputString3=="Storage_Ready") Serial1.print("RFID_FAIL");  inputString3 = "";    stringComplete3 = false;  }
  if (refresh==1) {
menusel=bootmode;
    if (menusel==0) introscreen(); // - Main Menu - Lcd graphics
    if (menusel==1) {  slider_update(); showtimer(1); // - Displays Sliders
    }
    if (menusel==2) {  menu();  // - Show / Set Time
    }
    if (menusel==3) {  introscreen1();  // - OutPut Settings - dmx universe numbers, midi channel number
    }
    if (menusel==4) {  // - Light Fixture Settings
    }
    if (menusel==5) {  // - Record effects
    }
    if (menusel==6) {  // - Play effects
    }
    if (menusel==7) {  menu();   sdcard_startup();   // - Manage Files SD/USB
    }
  }
//TOUCHED(1);  //Sense if screen been touched - lcd graphics
//    TSPoint p = ts.getPoint();
//    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {     x=p.x;     y=p.y;
//     Serial.print("x line : ");   Serial.print(p.x);   Serial.print(" : y line : ");   Serial.print(p.y);   Serial.print(" | Pressure line : ");   Serial.println(p.z);
//   }

//Beat_Detect(); //audio mic beat detection
}
 // ENABLE_SOFTWARE_SPI_CLASS
#else
#error ENABLE_SOFTWARE_SPI_CLASS must be set non-zero in SdFat/SdFatConfig.h
#endif

