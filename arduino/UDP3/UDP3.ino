//Shield Ethernet sans le POE
 #include <Ethernet.h>
 #include <EthernetUdp.h>

//Shield Ethernet avec le POE (module en plus)
//#include <Ethernet2.h>
//#include <EthernetUdp2.h>

#include <SPI.h>         // needed for Arduino versions later than 0018

byte mac[]={0x90,0xA2,0xDA,0x10,0xE8,0x9B};
IPAddress ip_shield(192,168,1,205);
int ports = 5500;
EthernetUDP UDP;

int vitesse_transmission=9600;
int envoi=0;

void setup()
{
  Serial.begin(vitesse_transmission);
  Ethernet.begin(mac,ip_shield);
  UDP.begin(ports);
  Serial.println("Activite UDP arduino - b4a");
  Serial.print("Adresse IP : ");
  Serial.print(Ethernet.localIP());
  Serial.print(" Adresse MAC : ");
  byte macBuffer[6];
  Ethernet.MACAddress(macBuffer);
  for (byte octet = 0; octet < 6; octet++) 
  {
    Serial.print(macBuffer[octet], HEX);
    if (octet < 5) 
    {
      Serial.print(':');
    }
  }
}

void loop()
{
  int Size=UDP.parsePacket();
  Serial.setCursor(0,0);
  Serial.println("Attente");
  if (Size>0)
    {
      envoi=envoi+1;
      Serial.print("Taille du paquet : ");
      Serial.print(Size);
      delay(3000);
      Serial.print(" depuis : ");
      IPAddress remote=UDP.remoteIP();
      Serial.print(remote[0],DEC);
      Serial.print(".");
      Serial.print(remote[1],DEC);
      Serial.print(".");
      Serial.print(remote[2],DEC);
      Serial.print(".");
      Serial.print(remote[3],DEC);
      delay(3000);
      Serial.print(" Port : ");
      Serial.println(UDP.remotePort(),DEC);
      delay(3000);
      char packetBuffer[Size];
      UDP.read(packetBuffer,Size);
      Serial.print("Contenu : ");
      Serial.print(packetBuffer);
      delay(3000);
      UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
      UDP.print(envoi);
      UDP.print(" envoi(s)");
      UDP.endPacket();
  }
 }
