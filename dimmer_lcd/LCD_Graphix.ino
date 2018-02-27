// all the fancy graphical Lcd pictures, referanced from other areas of code
// can load graphic's an stuff from SD Card
// should dmx modules be stored on the sd card?
// should USB data be able to be backed up to sd card

void introscreen1()
{
  // Clear the screen and draw the frame
  myGLCD.setColor(255,255,255);
  myGLCD.fillRect(1,15,478,304);

// Draw some lines in a pattern
  myGLCD.setColor (255,0,0);
  for (int i=15; i<304; i+=5)  {    myGLCD.drawLine(1, i, (i*1.6)-10, 304);  }
  myGLCD.setColor (255,0,0);
  for (int i=304; i>15; i-=5)  {    myGLCD.drawLine(478, i, (i*1.6)-11, 15);  }
  myGLCD.setColor (0,255,255);
  for (int i=304; i>15; i-=5)  {    myGLCD.drawLine(1, i, 491-(i*1.6), 15);  }
  myGLCD.setColor (0,255,255);
  for (int i=15; i<304; i+=5)  {    myGLCD.drawLine(478, i, 490-(i*1.6), 304);  }
  delay (5000);  myGLCD.clrScr();
}

void ScanRFID() {
      myGLCD.setBackColor(255,255,255); // Sets the background color to black
      myGLCD.setColor(0, 0, 0); myGLCD.setTextSize(4);   myGLCD.print("Scan RFID", LEFT, 100); // Prints the string on the screen
 }

void menu() {
      myGLCD.setBackColor(255,255,255); // Sets the background color to black
      myGLCD.setColor(0, 0, 0); myGLCD.setTextSize(2);   myGLCD.print("        Delux DMX Dimmer", LEFT, 10); // Prints the string on the screen
      myGLCD.setColor(255, 0, 0);    myGLCD.drawLine(25,32,440,32); // Header line
      myGLCD.setColor(255, 0, 0);    myGLCD.fillRect(25,290,440,316); // Footer Button Menu Box
      myGLCD.setColor(255, 255, 255); myGLCD.setTextSize(1); myGLCD.setBackColor(255,0,0);  myGLCD.print("Button No. 1  |  Button No. 2  |  Button No. 3  |  Button No. 4 ", CENTER, 300); // Prints the string on the screen
      myGLCD.setBackColor(255,255,255); // Sets the background color to black
 }
void slider_update() {
      myGLCD.setBackColor(255,255,255); myGLCD.setColor(0, 0, 0); myGLCD.setTextSize(2);   myGLCD.print("Dimmer Monitor", 150, 40); // Prints the string on the screen
      myGLCD.setColor(255, 0, 0);    myGLCD.drawLine(25,32,440,32); // Header line
      myGLCD.setColor(255, 0, 0);    myGLCD.fillRect(25,290,440,316); // Footer Button Menu Box
      myGLCD.setColor(255, 255, 255); myGLCD.setTextSize(1); myGLCD.setBackColor(255,0,0);  myGLCD.print("Button No. 1  |  Button No. 2  |  Button No. 3  |  Button No. 4 ", CENTER, 300); // Prints the footer bar buttons
      myGLCD.setBackColor(255,255,255); // Sets the background color to black
}
void showtimer(int x) {
  DateTime now = RTC.now();
  if (oldtime!=now.minute()) {  
//    myGLCD.setBackColor(255,255,255); // Sets the background color to black
    timer="Time "+String(now.hour())+":"+String(now.minute())+" ";
    dater="Date "+String(now.day())+"/"+String(now.month())+"/"+String(now.year())+" ";
    if (x==1) {  myGLCD.setTextSize(2);  myGLCD.setColor(0, 0, 255);  myGLCD.print(timer, 50, 5);  myGLCD.setColor(0, 0, 255);  myGLCD.print(dater, 240, 5);    }   // top of screen time display
    if (x==2) {  myGLCD.setTextSize(3);  myGLCD.setColor(0, 0, 255);  myGLCD.print(timer, 5, 300);   myGLCD.setColor(0, 0, 255);  myGLCD.print(dater, 205, 300);    }   // rfid + time update display
//    Serial.println(timer);
//    Serial.println(dater);
    oldtime=now.minute();
  }
}

void recvJoysticks(int aw_new,int ax_new,int ay_new,int az_new,int bw_new,int bx_new,int by_new,int bz_new,int cw_new,int cx_new,int cy_new,int cz_new,int dw_new,int dx_new,int dy_new,int dz_new){
 // graphical picture of moving head light with X Y Z an W=Colour
 myGLCD.setColor(255, 0, 0);
      myGLCD.drawRoundRect(51,72,103,124); // JoyStick 1
      myGLCD.drawRoundRect(151,72,203,124); // JoyStick 2
      myGLCD.drawRoundRect(251,72,303,124); // JoyStick 3
      myGLCD.drawRoundRect(351,72,403,124); // JoyStick 4
      myGLCD.setColor(0, 255, 255);  myGLCD.fillCircle((57+aw),(78+ax),3); 
      myGLCD.setColor(0, 255, 255);  myGLCD.fillCircle((157+bw),(78+bx),3);
      myGLCD.setColor(0, 255, 255);  myGLCD.fillCircle((257+cw),(78+cx),3);
      myGLCD.setColor(0, 255, 255);  myGLCD.fillCircle((357+dw),(78+dx),3);

      myGLCD.setColor(0, 0, 0);  myGLCD.fillCircle((57+aw_new),(78+ax_new),3);
      myGLCD.setColor(0, 0, 0);  myGLCD.fillCircle((157+bw_new),(78+bx_new),3);
      myGLCD.setColor(0, 0, 0);  myGLCD.fillCircle((257+cw_new),(78+cx_new),3);
      myGLCD.setColor(0, 0, 0);  myGLCD.fillCircle((357+dw_new),(78+dx_new),3);
     //myGLCD.setColor(0, 0, 0);  myGLCD.fillCircle(15,15,10);
      aw=aw_new; ax=ax_new; ay=ay_new; az=az_new; bw=bw_new; bx=bx_new; by=by_new; bz=bz_new; cw=cw_new; cx=cx_new; cy=cy_new; cz=cz_new; dw=dw_new; dx=dx_new; dy=dy_new; dz=dz_new;
  }

void vu_meter(int a) {
  
 }
 
 void recvdimmer(int S1,int S2,int S3,int S4,int S5,int S6,int S7,int S8) {
     int xR=0,LoC=0;
      xR=map(S1, 0, 255, 0, 110);
      if (xR!=S1old) {  myGLCD.setColor(255, 255, 255);  myGLCD.fillRect((40+LoC), (261-S1old+5), (65+LoC), (260-S1old)); S1old=xR; }
      myGLCD.setBackColor(0,0,0);  myGLCD.setColor(255, 255, 255); myGLCD.setTextSize(1);  myGLCD.print(" 001 ",38+LoC,273); myGLCD.setBackColor(255,255,255);
      myGLCD.setColor(255, 0, 0);  myGLCD.fillRect((52+LoC), 160, (53+LoC), (259-xR+4)); // start Positioner #1
      myGLCD.setColor(0, 0, 0);   myGLCD.fillRect((40+LoC), (261-xR+5), (65+LoC), (260-xR));  myGLCD.fillRect(50+LoC, (260-xR+5), 55+LoC, 260); // end Positioner #1
      LoC=50;  xR=map(S2, 0, 255, 0, 110);
      if (xR!=S2old) {  myGLCD.setColor(255, 255, 255);  myGLCD.fillRect((40+LoC), (261-S2old+5), (65+LoC), (260-S2old)); S2old=xR; }
      myGLCD.setBackColor(0,0,0);  myGLCD.setColor(255, 255, 255); myGLCD.setTextSize(1);  myGLCD.print(" 002 ",38+LoC,273); myGLCD.setBackColor(255,255,255);
      myGLCD.setColor(255, 0, 0);  myGLCD.fillRect((52+LoC), 160, (53+LoC), (259-xR+4)); // start Positioner #2
      myGLCD.setColor(0, 0, 0);   myGLCD.fillRect((40+LoC), (261-xR+5), (65+LoC), (260-xR));  myGLCD.fillRect(50+LoC, (260-xR+5), 55+LoC, 260); // end Positioner #2
      LoC=100; xR=map(S3, 0, 255, 0, 110);
      if (xR!=S3old) {  myGLCD.setColor(255, 255, 255);  myGLCD.fillRect((40+LoC), (261-S3old+5), (65+LoC), (260-S3old)); S3old=xR; }
      myGLCD.setBackColor(0,0,0);  myGLCD.setColor(255, 255, 255); myGLCD.setTextSize(1);  myGLCD.print(" 003 ",38+LoC,273); myGLCD.setBackColor(255,255,255);
      myGLCD.setColor(255, 0, 0);  myGLCD.fillRect((52+LoC), 160, (53+LoC), (259-xR+4)); // start Positioner #3
      myGLCD.setColor(0, 0, 0);   myGLCD.fillRect((40+LoC), (261-xR+5), (65+LoC), (260-xR));  myGLCD.fillRect(50+LoC, (260-xR+5), 55+LoC, 260); // end Positioner #3
      LoC=150;  xR=map(S4, 0, 255, 0, 110);
      if (xR!=S4old) {  myGLCD.setColor(255, 255, 255);  myGLCD.fillRect((40+LoC), (261-S4old+5), (65+LoC), (260-S4old)); S4old=xR; }
      myGLCD.setBackColor(0,0,0);  myGLCD.setColor(255, 255, 255); myGLCD.setTextSize(1);  myGLCD.print(" 004 ",38+LoC,273); myGLCD.setBackColor(255,255,255);
      myGLCD.setColor(255, 0, 0);  myGLCD.fillRect((52+LoC), 160, (53+LoC), (259-xR+4)); // start Positioner #4
      myGLCD.setColor(0, 0, 0);   myGLCD.fillRect((40+LoC), (261-xR+5), (65+LoC), (260-xR));  myGLCD.fillRect(50+LoC, (260-xR+5), 55+LoC, 260); // end Positioner #4
      LoC=200;   xR=map(S5, 0, 255, 0, 110);
      if (xR!=S5old) {  myGLCD.setColor(255, 255, 255);  myGLCD.fillRect((40+LoC), (261-S5old+5), (65+LoC), (260-S5old)); S5old=xR; }
      myGLCD.setBackColor(0,0,0);  myGLCD.setColor(255, 255, 255); myGLCD.setTextSize(1);  myGLCD.print(" 005 ",38+LoC,273); myGLCD.setBackColor(255,255,255);
      myGLCD.setColor(255, 0, 0);  myGLCD.fillRect((52+LoC), 160, (53+LoC), (259-xR+4)); // start Positioner #5
      myGLCD.setColor(0, 0, 0);   myGLCD.fillRect((40+LoC), (261-xR+5), (65+LoC), (260-xR));  myGLCD.fillRect(50+LoC, (260-xR+5), 55+LoC, 260); // end Positioner #5
      LoC=250;   xR=map(S6, 0, 255, 0, 110);
      if (xR!=S6old) {  myGLCD.setColor(255, 255, 255);  myGLCD.fillRect((40+LoC), (261-S6old+5), (65+LoC), (260-S6old)); S6old=xR; }
      myGLCD.setBackColor(0,0,0);  myGLCD.setColor(255, 255, 255); myGLCD.setTextSize(1);  myGLCD.print(" 006 ",38+LoC,273); myGLCD.setBackColor(255,255,255);
      myGLCD.setColor(255, 0, 0);  myGLCD.fillRect((52+LoC), 160, (53+LoC), (259-xR+4)); // start Positioner #6
      myGLCD.setColor(0, 0, 0);   myGLCD.fillRect((40+LoC), (261-xR+5), (65+LoC), (260-xR));  myGLCD.fillRect(50+LoC, (260-xR+5), 55+LoC, 260); // end Positioner #6
      LoC=300;   xR=map(S7, 0, 255, 0, 110);
      if (xR!=S7old) {  myGLCD.setColor(255, 255, 255);  myGLCD.fillRect((40+LoC), (261-S7old+5), (65+LoC), (260-S7old)); S7old=xR; }
      myGLCD.setBackColor(0,0,0);  myGLCD.setColor(255, 255, 255); myGLCD.setTextSize(1);  myGLCD.print(" 007 ",38+LoC,273); myGLCD.setBackColor(255,255,255);
      myGLCD.setColor(255, 0, 0);  myGLCD.fillRect((52+LoC), 160, (53+LoC), (259-xR+4)); // start Positioner #7
      myGLCD.setColor(0, 0, 0);   myGLCD.fillRect((40+LoC), (261-xR+5), (65+LoC), (260-xR));  myGLCD.fillRect(50+LoC, (260-xR+5), 55+LoC, 260); // end Positioner #7
      LoC=350;  xR=map(S8, 0, 255, 0, 110);
      if (xR!=S8old) {  myGLCD.setColor(255, 255, 255);  myGLCD.fillRect((40+LoC), (261-S8old+5), (65+LoC), (260-S8old)); S8old=xR; }
      myGLCD.setBackColor(0,0,0);  myGLCD.setColor(255, 255, 255); myGLCD.setTextSize(1);  myGLCD.print(" 008 ",38+LoC,273); myGLCD.setBackColor(255,255,255);
      myGLCD.setColor(255, 0, 0);  myGLCD.fillRect((52+LoC), 160, (53+LoC), (259-xR+4)); // start Positioner #8
      myGLCD.setColor(0, 0, 0);   myGLCD.fillRect((40+LoC), (261-xR+5), (65+LoC), (261-xR));  myGLCD.fillRect(50+LoC, (260-xR+5), 55+LoC, 260); // end Positioner #8
   refresh=0;
}
    
 void introscreen() {
      // Title
      myGLCD.setBackColor(255,255,255); // Sets the background color of the area where the text will be printed to black
      myGLCD.setColor(0, 0, 0); // Sets color to white
      myGLCD.setTextSize(2);
      myGLCD.print("Dimming Board", CENTER, 10); // Prints the string on the screen
      myGLCD.setColor(255, 0, 255); // Sets color to red
      myGLCD.drawLine(100,32,419,32); // Draws the red line
      myGLCD.setColor(0, 0, 0); // Sets color to white
      myGLCD.setTextSize(1);
      myGLCD.print("by SmartAlecLights.com", CENTER, 41); // Prints the string
      myGLCD.setTextSize(2);
      myGLCD.print("Select Function", CENTER, 64);

      // Button - Distance Sensor
      myGLCD.setColor(16, 167, 103); // Sets green color
      myGLCD.fillRoundRect (150, 90, 350, 130); // Draws filled rounded rectangle
      myGLCD.setColor(255, 255, 255); // Sets color to white
      myGLCD.drawRoundRect (150, 90, 350, 130); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
      myGLCD.setTextSize(2);
      myGLCD.setBackColor(16, 167, 103); // Sets the background color of the area where the text will be printed to green, same as the button
      myGLCD.print("Button 1", CENTER, 102); // Prints the string
      
      // Button - RGB LED Control
      myGLCD.setColor(16, 167, 103);
      myGLCD.fillRoundRect (150, 140, 350, 180);
      myGLCD.setColor(255, 255, 255);
      myGLCD.drawRoundRect (150, 140, 350, 180);
      myGLCD.setTextSize(2);
      myGLCD.setBackColor(16, 167, 103);
      myGLCD.print("RGB LED CONTROL", CENTER, 152);

      // Button - Birduino
      myGLCD.setColor(16, 167, 103);
      myGLCD.fillRoundRect (150, 190, 350, 230);
      myGLCD.setColor(255, 255, 255);
      myGLCD.drawRoundRect (150, 190, 350, 230);
      myGLCD.setTextSize(2);
      myGLCD.setBackColor(16, 167, 103);
      myGLCD.print("Button 3", CENTER, 202);
      refresh=0;
  }

void TOUCHED(int currentPage) { 
  int y;
   if (currentPage == 1) {
// Serial.print("currentPage "); Serial.println(currentPage); 
     TSPoint p = ts.getPoint();
//   Serial.print("x line : ");   Serial.print(p.x);   Serial.print(" : y line : ");   Serial.print(p.y);   Serial.print(" | Pressure line : ");   Serial.println(p.z);
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
   x=p.x;
   y=p.y;
   Serial.print("x line : ");   Serial.print(p.x);   Serial.print(" : y line : ");   Serial.print(p.y);   Serial.print(" | Pressure line : ");   Serial.println(p.z);
   // If we press the RGB LED Control Button 
          if ((x>=35) && (x<=700) && (y>=500) && (y<=600)) {
            drawFrame(35, 140, 285, 180);
 //           currentPage = '2';
           // myGLCD.clrScr();
 //          myGLCD.fillScreen(BLACK); drawLedControl();
         }
    }
  }
      // RGB LED Control 
  if (currentPage == 2) {
//    setLedColor();
       TSPoint p = ts.getPoint();
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        x=p.x;
        y=p.y;        
         //Back button
            if ((x>=10) && (x<=60) &&(y>=10) && (y<=36)) {
              drawFrame(10, 10, 60, 36);
              currentPage = '0';
              myGLCD.fillScreen(BLACK); refresh=1; introscreen();
           }
        }
   }
    //==== This section of the code, for the game example, is explained in my next tutorial
    TSPoint p = ts.getPoint();
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        x=p.x;
        y=p.y;        
            if ((x>=10) && (x<=60) &&(y>=10) && (y<=36)) {
              drawFrame(10, 10, 60, 36);
              currentPage = '0';
              myGLCD.fillScreen(BLACK);  refresh=1; introscreen();
          }
      }
}

    
    // ====== Custom Funtions ======
     void drawFrame(int x1, int y1, int x2, int y2) {
      myGLCD.setColor(255, 0, 0);
      myGLCD.drawRoundRect (x1, y1, x2, y2);
     TSPoint p = ts.getPoint();
 //   while (p.z > MINPRESSURE && p.z < MAXPRESSURE)
        x=p.x;
        y=p.y;        
        myGLCD.setColor(255, 255, 255);
        myGLCD.drawRoundRect (x1, y1, x2, y2);
    }

    //====================================================
 /*
    void drawLedControl() {
   myGLCD.fillScreen(BLACK);

     myGLCD.setColor(100, 155, 203);
      myGLCD.fillRoundRect (10, 10, 60, 36);
      myGLCD.setColor(255, 255, 255);
      myGLCD.drawRoundRect (10, 10, 60, 36);
      myGLCD.setFont(BigFont);
      myGLCD.setBackColor(100, 155, 203);
      myGLCD.print("<-", 18, 15);
      myGLCD.setBackColor(0, 0, 0);
      myGLCD.setFont(SmallFont);
      myGLCD.print("Back to Main Menu", 70, 18);
      myGLCD.setFont(BigFont);
      myGLCD.print("RGB LED Control", CENTER, 50);
      myGLCD.print("LED Color:", 10, 95);
      myGLCD.print("R", 10, 135);
      myGLCD.print("G", 10, 175);
      myGLCD.print("B", 10, 215);
      myGLCD.setColor(255, 0, 0);
      myGLCD.drawLine(0,75,319,75); 
      myGLCD.setColor(255, 255, 255);
      myGLCD.drawRect(30, 138, 310, 148); // R - Slider
      myGLCD.drawRect(30, 178, 310, 188);
      myGLCD.drawRect(30, 218, 310, 228);  
    }
    //====================================================

void setLedColor() {
     TSPoint p = ts.getPoint();
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        x=p.x;
        y=p.y;        
        // Area of the Red color slider
    Serial.print("x line : ");   Serial.print(p.x);   Serial.print(" : y line : ");   Serial.print(p.y);   Serial.print(" | Pressure line : ");   Serial.println(p.z);
       if( (y>=400) && (y<=490)) {
          xR=x; // Stores the X value where the screen has been pressed in to variable xR
          if (xR<=38) { // Confines the area of the slider to be above 38 pixels
            xR=38;
          }
          if (xR>=303){ /// Confines the area of the slider to be under 310 pixels
            xR=303;
          }
        }
        // Area of the Green color slider
        if( (y>=500) && (y<=590)) {    xG=x;
          if (xG<=200) {  xG=200;    }
          if (xG>=600){  xG=600;   }
        }
        // Area of the Blue color slider
        if( (y>=600) && (y<=690)) {    xB=x;
          if (xB<=200) {  xB=200;    }
          if (xB>=600){  xB=600;   }
        }    
     }
      // Maps the values of the X - Axis from 38 to 0 and 310 to 255, because we need values from 0 to 255 for turning on the led
      int xRC = map(xR,38,310,0,255);
      int xGC = map(xG,38,310,0,255);
      int xBC = map(xB,38,310,0,255);
      
      // Sends PWM signal to the pins of the led
//      analogWrite(redLed, xRC);
//Serial.print("RedLed : ");   Serial.print(xRC);
//      analogWrite(greenLed, xGC);
//Serial.print("GreenLed : ");   Serial.print(xGC);
//      analogWrite(blueLed, xBC);
//Serial.print("BlueLed : ");   Serial.print(xBC);
      
      // Draws a rectangle with the latest color combination 
      myGLCD.setColor(xRC, xGC, xBC);
      myGLCD.fillRoundRect(175, 87, 310, 119);
      
      // Draws the positioners
      myGLCD.setColor(255, 255, 255);
      myGLCD.fillRect(xR,139,(xR+4),147); // Positioner
      myGLCD.setColor(xRC, 0, 0);
      myGLCD.fillRect(31, 139, (xR-1), 147);
//      myGLCD.setColor(0, 0, 0);
      myGLCD.fillRect((xR+5), 139, 309, 147);
      
      myGLCD.setColor(255, 255, 255);
      myGLCD.fillRect(xG,179,(xG+4),187);
      myGLCD.setColor(0, xGC, 0);
      myGLCD.fillRect(31, 179, (xG-1), 187);
//      myGLCD.setColor(0, 0, 0);
      myGLCD.fillRect((xG+5), 179, 309, 187);
      
      myGLCD.setColor(255, 255, 255);
      myGLCD.fillRect(xB,219,(xB+4),227);
      myGLCD.setColor(0, 0, xBC);
      myGLCD.fillRect(31, 219, (xB-1), 227);
//      myGLCD.setColor(0, 0, 0);
      myGLCD.fillRect((xB+5), 219, 309, 227);
    }
 */
    //====================================================
 
