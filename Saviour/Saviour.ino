#include <avr/pgmspace.h>
#include <Arduino.h>
#include <U8x8lib.h>

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(SCL, SDA, U8X8_PIN_NONE);   // OLEDs without Reset of the Display

char l = ' ';
String sent = "";
int x = 0, y = 0;
boolean f = false, cursor = false, goMenu = false;
long ps = 0, out;

static const String morse[] PROGMEM = {"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "---...", "---...", "-...-", "-...-", "-...-", "..--..", ".--.-.", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

void setup() {
  pinMode(2, INPUT);

  u8x8.begin();
  u8x8.setFlipMode(0);
  u8x8.setBusClock(100000);
  u8x8.setFont(u8x8_font_chroma48medium8_r);

  Serial.begin(9600);


  // Serial.println(morseTranslate(sent));


}





void loop()
{

  l = (char)(90 - map(analogRead(A0), 0, 1021, 0, 26));


  if (l == 64)
    l = ' ';


  u8x8.setCursor(x, y);
  click();

  if (!goMenu)
  {
    if (millis() - ps >= 500)
    {
      cursor = !cursor;
      ps = millis();
    }

    if (cursor)
      u8x8.print(l);
    else
      u8x8.print('_');
  }
}


boolean click()
{
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
      goMenu=true;
    }
  }

  else
  {
    f = true;
    out = millis();
  }

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
