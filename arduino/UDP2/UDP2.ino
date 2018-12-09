#include <Ethernet.h>
#include <EthernetUdp.h>

#include <Wire.h> 
#include <rgb_lcd.h>

#include <SPI.h>         // needed for Arduino versions later than 0018

rgb_lcd lcd;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
byte mac[]={0x90,0xA2,0xDA,0x0D,0x81,0x40};
IPAddress ip_shield(192,168,1,205);

EthernetUDP UDP;

void setup()
{
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);  
  lcd.print("Hello, world!");
  lcd.setCursor(0,1);
  lcd.print(ip_shield);
  delay(2000);
  lcd.clear();
  Ethernet.begin(mac,ip_shield);
  UDP.begin(5500);
}

void loop()
{
  int Size=UDP.parsePacket();
  if (Size>0)
  {
    lcd.clear();
    char message[Size];
    UDP.read(message,Size);
    
    lcd.setCursor(0,0);
    lcd.print("Le message est : ");
    lcd.setCursor(0,1);
    lcd.print(message);
    
    
    UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
    UDP.print(Size);
    UDP.print (" octet(s) transmis");
    UDP.endPacket();
    delay(5000);
   }
   
}


