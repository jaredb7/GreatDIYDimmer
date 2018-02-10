//
//--- Detection of Pulse's Using Microphone Or Line input ---
//

/*
void setup()
{
//sg90.attach(9);
Serial.begin(115200);
for (int pin=0; pin < 6; pin++)  
{
  pinMode(led[pin], OUTPUT);      
}
for (int colu=2; colu < 6; colu++)  
{
  digitalWrite(led[colu], HIGH);      
}
digitalWrite(led[0], HIGH);
digitalWrite(led[1], HIGH);
}
*/
void Beat_Detect()
{
// val = sensibility
// this variable can be changed to potentiometer input
//
//val=130;
oldsensorvalue=sensorvalue;
sensorvalue=analogRead(mic);
//sensorvalue=sensorvalue/val;
//
// Get MAX
//
if (sensorvalue > lastsensorvalue)
{
  lastsensorvalue=sensorvalue;
}
//
// Get MIN
//
if( sensorvalue < lastminsensorvalue)
{
  lastminsensorvalue=sensorvalue;
}
//Serial.println(sensorvalue);
if (oldsensorvalue!=sensorvalue) {

Serial.print("MIN: ");
Serial.print(lastminsensorvalue);
Serial.print("  ");
Serial.print("MAX: ");
Serial.print(lastsensorvalue);
Serial.print("  ");
Serial.print("LAST: ");
Serial.print(sensorvalue);
Serial.print("  ");
Serial.print("Sensibility: ");
Serial.println(val);
//delay(1);
}
/*
if (sensorvalue == lastminsensorvalue)
{
  for(int i=6;i>1;i--)
  {
    digitalWrite(led[i], HIGH);
    delay(130);
  }
 
}

else
{
  for (i=2;i<sensorvalue; i++) // turn on the leds up to the volume level
    {
      digitalWrite(led[i], LOW);
      delay(1);
    }
  for(i=i;i<6;i++)  // turn off the leds above the voltage level
    {
      digitalWrite(led[i], HIGH);
    }
}
*/
}


//void setup()  {  for (i = 0; i < 11; i++)    pinMode(led[i], OUTPUT);  }


void beat_trigger() {

int led[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int input, i;
  input = analogRead(linein);
  input = input / 12;      //By changing the denomintor the sensitivity can be changed
  if (input < 12)
  {
    if (input == 0)
    {  for (i = 0; i < 11; i++)   {  digitalWrite(led[i], LOW);   }  }
    else
    {  for (i = 0; i < input; i++)   {  digitalWrite(led[i], HIGH);   delay(4);  }
       for (i = i; i < 11; i++)   {  digitalWrite(led[i], LOW);   }
    }
  }
}
