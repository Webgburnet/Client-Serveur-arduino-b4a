//Shield Ethernet sans le POE
 #include <Ethernet.h>
 #include <EthernetUdp.h>
 #include <SPI.h>         // needed for Arduino versions later than 0018

byte mac[]={0x90,0xA2,0xDA,0x10,0xE8,0x9B};
IPAddress ip_shield(192,168,1,205);
int ports = 5500;
EthernetUDP UDP;

int vitesse_transmission=9600;

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
  if (Size>0)
  {
    char message[Size];
    String message2;
    UDP.read(message,Size);
    message2=message;
    Serial.print("Le message est :");
    Serial.println(message2);
  }
}
