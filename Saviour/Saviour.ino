#include <avr/pgmspace.h>
#include <Arduino.h>
#include <U8x8lib.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define led 7
#define buzz 5

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(SCL, SDA, U8X8_PIN_NONE);   // OLEDs without Reset of the Display


SoftwareSerial ss(4, 3);
TinyGPSPlus gps;

int fran = 233;

int dit = 80;
int dah = 200;


char l = ' ';
String sent = "";
int x = 0, y = 0, ch=0, lch=-1;
boolean f = false, cursor = false, goMenu = true;
long ps = 0, out;

static const String morse[] PROGMEM = {"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "---...", "---...", "-...-", "-...-", "-...-", "..--..", ".--.-.", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

String lati="",lngt="";


void setup() {
  pinMode(2, INPUT);
  pinMode(buzz, OUTPUT);
  pinMode(led, OUTPUT);

  u8x8.begin();
  u8x8.setFlipMode(0);
  u8x8.setBusClock(100000);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  ss.begin(9600);
  Serial.begin(115200);
}



void loop()
{

  while (!goMenu)
  {
      if(ch==0)
        Morse();
        
      else if(ch==2)
      GPS();
     
  }
      
    
    

  selectMenu();

    
  
}




void selectMenu()
{
  ch=map(analogRead(A0), 0,1020,0,3);
  Serial.println(ch);
  x=0;
  y=0;
  
if(lch!=ch)
{
  if(ch==0)
  {
   u8x8.clearDisplay();
   u8x8.setCursor(4,3);
   u8x8.print("Morse");
   u8x8.setCursor(4,4);
   u8x8.print("Code");
   u8x8.setCursor(3,6);
   u8x8.print("-.-.-.-");
  }

  else if(ch==1)
  {
   u8x8.clearDisplay();
   u8x8.setCursor(4,3);
   u8x8.print("Compass");
  }

  else if(ch==2)
  {
   u8x8.clearDisplay();
   u8x8.setCursor(4,3);
   u8x8.print("GPS");
  }

  else if(ch==3)
  {
   u8x8.clearDisplay();
   u8x8.setCursor(4,3);
   u8x8.print("Altitude");
  }
  
  lch=ch;
}


if(digitalRead(2)==1)
{
  u8x8.clearDisplay();
  goMenu=false;
  delay(100);  
}


out=millis();
}




boolean Morse()
{
  l = (char)(90 - map(analogRead(A0), 0, 1021, 0, 26));

    if (l == 64)
      l = ' ';

    u8x8.setCursor(x, y);
  
  if (digitalRead(2))
  {
    if (f)
    {
      sent += l;
      x++;
      f = false;
      u8x8.print(l);
      if (x == 16)
      {
        y++;
        x = 0;
        u8x8.setCursor(x, y);
      }
      Serial.println(sent);
    }

    if (millis() - out > 3000)
    {
      String z = morseTranslate(sent);
      Serial.println(z);
      out = millis();
      printMorse(z);
      spitMorse(z);
      goMenu = true;
      while(true)
      {
        if(digitalRead(2))
        {
          delay(100);
          return !f;  
        }          
      }
      
    }
  }

  else
  {
    f = true;
    out = millis();
  }

  if (millis() - ps >= 500)
    {
      cursor = !cursor;
      ps = millis();
    }

    if (cursor)
      u8x8.print(l);
    else
      u8x8.print('_');

  return !f;
}


String morseTranslate(String line)
{

  String res = "";

  for (int i = 0; i < line.length() - 1; i++)
  {
    char x = line.charAt(i);
    if (x == ' ')
      res += '|';
    else if (x == '.')
      res += ".-.-.-";

    else
      res += morse[x - 48] + ' ';

  }

  return res;
}

void printMorse(String line)
{
  u8x8.clearDisplay();
  for (int i = 0; i < line.length(); i++)
  {
    u8x8.setCursor(i % 16, i / 16);
    u8x8.print(line.charAt(i));
    x = i % 16 + 1;
    y = i / 16;
  }
  sent = "";
}


void spitMorse(String s)
{
  for (int i = 0; i < s.length(); i++)
  {

    char x = s.charAt(i);

    if (x == ' ')
    {
      digitalWrite(led, 0);
      analogWrite(buzz, 0);
      delay(200);
    }

    else if (x == '.')
    {
      analogWrite(buzz, fran);
      digitalWrite(led, 1);
      delay(dit);
      analogWrite(buzz, 0);
      digitalWrite(led, 0);
    }

    else if (x == '-')
    {
      analogWrite(buzz, fran);
      digitalWrite(led, 1);
      delay(dah);
      analogWrite(buzz, 0);
      digitalWrite(led, 0);
    }

    else
    {
      analogWrite(buzz, 0);
      digitalWrite(led, 0);
      delay(500);
    }

    delay(50);
  }
}


void GPS()
{
   while (ss.available() > 0)
  {
    if (gps.encode(ss.read()))
      displayGpsData();

      long cs=millis();
      while(digitalRead(2))
      {
        Serial.println(millis()-cs);
        if(millis()-cs>3000)
        {
          String li=morseTranslate(lati);
          String lg=morseTranslate(lngt);
          printMorse(li);
          spitMorse(li);
          printMorse(lg);
          spitMorse(lg);

          while(true)
          {
            if(digitalRead(2))
            {
              goMenu=true;
              delay(100);
              return;
            }
          }
        }
      }
      
  }
}


void displayGpsData()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    lati = "lat:"+String(gps.location.lat(), 6);
    lngt = "lng:"+String(gps.location.lng(), 6);

    u8x8.refreshDisplay();
    
    u8x8.setCursor(0,1);
    u8x8.print(lati);
    u8x8.setCursor(0,3);
    u8x8.print(lngt);
    
    Serial.print(lati);
    Serial.print(F(","));
    Serial.print(lngt);
    
  }
  else
  {
    Serial.print(F("INVALID"));
    
    u8x8.setCursor(0,1);
    u8x8.print("NO FIX");
    
    u8x8.refreshDisplay();
  }

  Serial.println();
}
