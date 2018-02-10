// for LCD graphix mainly
// for dmx modules
// for pixel effects
// Security rights of RFID Users
// backup of USB stick sequence
// default sequence/settings

void sdcard_startup() {
Serial.println("****************SD_Card_section**********************");  

// read SD file directory
sd.ls(LS_A | LS_DATE | LS_SIZE | LS_R);
Serial.println("***************************************************");  

sd.ls(LS_A | LS_SIZE );

Serial.println("***************************************************");  


//myFile = sd.open("/PICCS/2016cb80.DAT", O_CREAT | O_RDWR | O_AT_END); myFile.println("Sexy user,1"); myFile.close();

Serial.println("***************************************************");  

   // re-open the file for reading:
//  myFile = sd.open("SYS/master.dat", O_READ);
//  if (myFile) {    Serial.println("SYS/master.dat:");    while (myFile.available()) {      Serial.print(myFile.read(),HEX);    }    myFile.close();  } else {    Serial.println("error opening master.dat");  }
Serial.println("***************************************************");  
Serial.println(cardid);
  Serial.println("********************sd_dir_load*******************************");  
        File dir = sd.open(dirdata);
          while (true) {
            File entry =  dir.openNextFile();
            if (! entry) {   break;    }    // found the data file in the directory an loading contents
        Serial.print("Displaying ");   Serial.print(dirdata);  SDcardDisplay(dirdata);  Serial.println(" directory and Contents of each file in it");
            while (entry.available()) { 
              Serial.write(entry.read());
//              SDcardDisplay(entry.read());
             }
          entry.close();
 //       Serial.print("<**********>"); 
  }
 // dir.close();


/*
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

*/


Serial.println("***************************************************");  

//    for (int i = 0; i < 4; i++) {             // Loop 4 times to get 4 bytes
//      readCard[i] = masterfile.read();
//      Serial.print(String(readCard[i]));         // Actual serial printing of each byte
//      masterCard[i] = readCard[i];            // Prepare bytes for future comparing
//    }
//    Serial.println("");
//    masterfile.close();                       // Close file
}

void SDcardDisplay(String OutPut) {
      myGLCD.setColor(0, 0, 0); myGLCD.setTextSize(2);   myGLCD.print(OutPut, LEFT, 50); // Prints the string on the screen
//      myGLCD.setColor(255, 0, 0);    myGLCD.drawLine(25,32,440,32); // Header line
   refresh=1;
}



