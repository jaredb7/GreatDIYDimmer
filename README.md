# GreatDIYDimmer
I had a Great idea the other night, an since been jotting down notes everyware.

Picture This "DMX Controller, Midi Controller, Pixel Controller, Live Pattern/sequence Player"

- 3.5" Touch Screen LCD, (or Bigger)
- 4x Access buttons with Led's,
- 4x4 Silicone Touch Pixel Matrix (with RGB Pixels in each),
- 8x 10mm Sliders,
- 4x JoySticks,
- USD Stick Storage,
- RFID Scanner,
- Onboard Clock.
- Mic Sensor,

-= Rear Panel =-

- 2x DMX In/Out,
- 1x MIDI In/Out,
- 2x Pixel Out (ws2811),
- {maybe E1.31 Out Ethernet}
- {maybe Esp8266 Module for Remote control Via Phone}

-= The following is a Discription of the Folders for the different Arduino Images =-

- dimmer_colour_buttons = arduino mini pro {serial}, controlling 4x4 button matrix an rgb ws2811 pixel for each button
- dimmer_sliders = arduino mini pro {serial}- using I2C to 4 ---- enabling 1 joystick an 2 fader sliders per ----
- dimmer_usb = arduino uno + USB Host Shield {serial+I2C}, Enable's USB storage an playback of sequences
- dimmer_lcd = arduino mega + 3.5" TouchScreen + (SD LCD Graphix) + RFID {Serial buttons}{Serial sliders}{Serial+I2C usb}{Serial+I2C Output) - Main Controler
- dimmer_output = arduino mega {serial+I2C}, Enabling 2x DMX In/Out, 1x Midi In/Out, 2x Ws2811 Pixel Output of 500pixels


The output being a arduino mega could be replace with a Raspberry Pi to do the Outputs

This same project could be programed using a raspberry pi as a output to be a live music sequencer


There are many possabilities

I only have a basic level of arduino programming,

But i hope with the Above project an the different levels of coding needed, this could turn out great

- Faders, Joystick's, Buttons could be colour changers, wipe's, scene setups/playbacks, mainly due to the arduino mini pro sending its raw data to the main LCD Brain to interpret what that data should realy be used for
- the Output board could be programmed to play directly from the USB Stick sequence, or to be a normal dimmer board
- The Touch LCD -Main Brain-, can be the heart/thinker for everything, directing what information goes where an what that information means, via a touch screen panel, menu's for light settings,for sequences, for info off the usb, to programming everything to do different things when needed
- The {Serial+I2C} for the Output, USB & LCD. I was thinking the I2C could be like the control word or future instructions, while the serial communications could continue un-interupted
- Reason for Seperate Arduino Mini Pro's, for the fader/joy an Buttons/pixels, was just incause your doing a nice fade of one thing, an you wanted to load another effect via the touch button pad
- Reason for pixels under the buttons, 1, they look great, 2. different colour for different effects or rec/play back modes
- RFID scanner - For Security, and to allow different people different levels of access an functions
- Joysticks could control 4 or more Moving Head Lights, Setup for Moving head lights in Menu system an saved.
- LCD to show a Picture of the Moving Head Light in Graphical Colour, while displaying its programmed X/Y Location
- Programmed Dmx Channel output order, allowing different patchings for different things
- Midi In/Out - to trigger sequences(midi in) or to control other Midi gear(midi out)
- DMX Modules to include, DMX Snow/fog/Ice/Bubble Machines, dif MovingHead Lights, RGB, RGBW, X ch controllers (eg lor16, 27ch)
- {maybe esp-wifi to trigger sequences or effects via phone_app}
- {Be super great if it could use Xlights Sequences to play in it}
- {E1.31 would be great, even better if it used the latest sync check}
- RDM DMX is possable via hardware, just software is needed for it

This is How your directory should look

```
your_sketchbook
 |
 +--libraries
 |   |
 |   +--Adafruit_GFX_Library
 |   |
 |   +--Adafruit_TFTLCD
 |   |
 |   +--Adafruit_NeoPixel
 |   |
 |   +--MFRC522
 |   |
 |   +--MCUFRIEND_kbv
 |   |
 |   +--SdFat
 |   |
 |   +--UsbFat
 |   |
 |   +--Conceptinetics
 |
 +--
     |
     +--
     +--
```
