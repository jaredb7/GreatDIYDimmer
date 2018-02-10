#include <Conceptinetics.h>
#include <Wire.h>

#define DMX_MASTER_CHANNELS   6

//
// Pin number to change read or write mode on the shield
//
#define RXEN_PIN              6

// Configure a DMX master controller, the master controller
// will use the RXEN_PIN to control its write operation
// on the bus
DMX_Master        dmx_master ( DMX_MASTER_CHANNELS, RXEN_PIN );

int ch1_pot;
int ch2_pot;
int ch3_pot;
int ch4_pot;
int ch5_pot;
int ch6_pot;

int ch1_dmx;
int ch2_dmx;
int ch3_dmx;
int ch4_dmx;
int ch5_dmx;
int ch6_dmx;

void scene1 (void){
  // 10 seconds blue
  for (int i=0; i<10; i++){
    dmx_master.setChannelValue (1, 0);
    dmx_master.setChannelValue (2, 0);
    dmx_master.setChannelValue (3, 255);
    dmx_master.setChannelValue (4, 255);
    dmx_master.setChannelValue (5, 0);
    dmx_master.setChannelValue (6, 0);
    delay(1000);
  }
}

void scene2 (void){
  // 10 seconds blue
  for (int i=0; i<5; i++){
    dmx_master.setChannelValue (1, 255);
    dmx_master.setChannelValue (2, 255);
    dmx_master.setChannelValue (3, 255);
    dmx_master.setChannelValue (4, 255);
    dmx_master.setChannelValue (5, 0);
    dmx_master.setChannelValue (6, 0);
    delay(1000);
  }
}

void scene3 (void){
  // 10 seconds blue
  for (int i=0; i<5; i++){
    dmx_master.setChannelValue (1, 255);
    dmx_master.setChannelValue (2, 0);
    dmx_master.setChannelValue (3, 255);
    dmx_master.setChannelValue (4, 255);
    dmx_master.setChannelValue (5, 0);
    dmx_master.setChannelValue (6, 0);
    delay(1000);
  }
}

void scene4 (void){
  // 10 seconds blue
  for (int i=0; i<5; i++){
    dmx_master.setChannelValue (1, 0);
    dmx_master.setChannelValue (2, 0);
    dmx_master.setChannelValue (3, 255);
    dmx_master.setChannelValue (4, 255);
    dmx_master.setChannelValue (5, 255);
    dmx_master.setChannelValue (6, 0);
    delay(1000);
  }
}

void scene5 (void){
  // 10 seconds blue
  for (int i=0; i<5; i++){
    dmx_master.setChannelValue (1, 0);
    dmx_master.setChannelValue (2, 255);
    dmx_master.setChannelValue (3, 255);
    dmx_master.setChannelValue (4, 255);
    dmx_master.setChannelValue (5, 0);
    dmx_master.setChannelValue (6, 0);
    delay(1000);
  }
}

// the setup routine runs once when you press reset:
void setup() {
   Serial.begin(115200);  // Initialize serial communications with PC
//  Wire.begin();    // join i2c bus ( as Master ) Arduino 2560 - Touch LCD
//  Wire.begin(1);   // join i2c bus ( as Master )  Arduino Uno - USB Stick Recorder
    Wire.begin(2);   // join i2c bus ( as Master ) Arduino 2560 - { 2x DMX, Pixel, Midi in/out } - Output Board
//    Wire.onReceive(receiveI2C); // register event

  // Enable DMX master interface and start transmitting
  dmx_master.enable ();

  // turn off all channels
  dmx_master.setChannelValue (1, 0);
  dmx_master.setChannelValue (2, 0);
  dmx_master.setChannelValue (3, 0);
  dmx_master.setChannelValue (4, 0);
  dmx_master.setChannelValue (5, 0);
  dmx_master.setChannelValue (6, 0);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);

}

// the loop routine runs over and over again forever:
void loop()
{
 if (digitalRead(2)==0){
   scene1();
 }
 if (digitalRead(3)==0){
   scene2();
 }
 if (digitalRead(4)==0){
   scene3();
 }
 if (digitalRead(5)==0){
   scene4();
 }
 if (digitalRead(7)==0){
   scene5();
 }

// read apotentiometer position
ch1_pot = analogRead(A0);
ch2_pot = analogRead(A1);
ch3_pot = analogRead(A2);
ch4_pot = analogRead(A3);
ch5_pot = analogRead(A4);
ch6_pot = analogRead(A5);

// compute DMX values
ch1_dmx =  map(ch1_pot, 0, 1023, 0, 255);
ch2_dmx =  map(ch2_pot, 0, 1023, 0, 255);
ch3_dmx =  map(ch3_pot, 0, 1023, 0, 255);
ch4_dmx =  map(ch4_pot, 0, 1023, 0, 255);
ch5_dmx =  map(ch5_pot, 0, 1023, 0, 255);
ch6_dmx =  map(ch6_pot, 0, 1023, 0, 255);

// update dmx bus
dmx_master.setChannelValue ( 1, ch1_dmx);
dmx_master.setChannelValue ( 2, ch2_dmx);
dmx_master.setChannelValue ( 3, ch3_dmx);
dmx_master.setChannelValue ( 4, ch4_dmx);
dmx_master.setChannelValue ( 5, ch5_dmx);
dmx_master.setChannelValue ( 6, ch6_dmx);
//
delay(100);

}
