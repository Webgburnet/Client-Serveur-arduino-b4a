
#include <Wire.h> 
#include <rgb_lcd.h>


#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>

rgb_lcd lcd;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

byte mac[]={0x90, 0xA2, 0xDA, 0x0D, 0x32, 0x82};
IPAddress ip_shield(192,168,1,205);
unsigned int port_local=5500;
EthernetUDP UDP;
int envoi=0;

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
  UDP.begin(port_local);
}

void loop()
{
  int Size=UDP.parsePacket();
  lcd.setCursor(0,0);
  lcd.print("Attente");
  if (Size>0)
    {
      envoi=envoi+1;
      lcd.clear();
      lcd.print("Taille du paquet : ");
      lcd.setCursor(0,1);
      lcd.print(Size);
      delay(3000);
      
      lcd.clear ();
      lcd.print("depuis : ");
      lcd.setCursor(0,1);
      IPAddress remote=UDP.remoteIP();
      lcd.print(remote[0],DEC);
      lcd.print(".");
      lcd.print(remote[1],DEC);
      lcd.print(".");
      lcd.print(remote[2],DEC);
      lcd.print(".");
      lcd.print(remote[3],DEC);
      delay(3000);
      lcd.clear();
      lcd.print("Port : ");
      lcd.print(UDP.remotePort(),DEC);
      delay(3000);
      char packetBuffer[Size];
      UDP.read(packetBuffer,Size);
      lcd.clear();
      lcd.print("Contenu : ");
      lcd.setCursor(0,1);
      lcd.print(packetBuffer);
      delay(3000);
      lcd.clear();
      UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
      UDP.print(envoi);
      UDP.print(" envoi(s)");
      UDP.endPacket();
  }
 }

