#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <BlynkSimpleEsp8266.h>

char token[] = "XXX";
char agAdi[] = "XXX";
char agSifre[] = "XXX";
#define sensor A0
#define motor 5

const int kuru = 1024;
const int islak = 916;
int deger;
int donusum;
int sondonusum;
int saat;
int dakika;
int saniye;

const long utcOffsetInSeconds = 10800;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "1.tr.pool.ntp.org", utcOffsetInSeconds);

void setup() {

digitalWrite(motor, HIGH);
Serial.begin(9600);
Blynk.begin(token, agAdi, agSifre);

}

void loop() {

deger = analogRead(sensor);
donusum=map(deger, islak, kuru, 100, 0);

Blynk.virtualWrite (V1, donusum);
Blynk.run();

timeClient.update();
saat = timeClient.getHours(); 
dakika = timeClient.getMinutes();
saniye = timeClient.getSeconds();

if(saat == 11 && dakika == 00 && saniye == 54)
{
 Blynk.notify("Çiçek sulama başladı.");
 digitalWrite(motor, LOW);
 delay ( 6000 );
 digitalWrite(motor, HIGH);
  }


}
