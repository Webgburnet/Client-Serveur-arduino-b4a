#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>

byte mac[]={0x90,0xA2,0xDA,0x0D,0x81,0x40};
IPAddress ip_shield(192,168,1,205);
unsigned int port_local=5500;
EthernetServer server(port_local);
String message;
boolean change=false;

void setup()
{
  Ethernet.begin(mac, ip_shield);
  server.begin();
  Serial.println("Activite TCP arduino - b4a");
  delay(3000);
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
  Serial.println("Attente client");
  
  EthernetClient client = server.available();
  
  if (client) 
    {
     while (client.connected()==true) 
       {
          client.flush();
          message="";
          change=false;      
                while (client.available() > 0) 
                {
                  char c = client.read();
                  message+=c;
                  change=true;
                }
                        
              if (change == true) 
              {
                Serial.print("Client connecte");
                Serial.println(message);
                client.print("Message recu :"+message);
             }
      }
    }
}
