#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 10);
//SoftwareSerial serial_gps(8, 9); 
TinyGPSPlus gps;
String latitude, longitude;
char c = ' ';

void setup() {
  Serial.begin(9600);
  //serial_gps.begin(9600);
  //Serial.println("GPS Mulai");
  //while(!Serial);
   Serial.println("Arduino with mySerial is ready");
 
    // start communication with the mySerial in 9600
    mySerial.begin(9600);  
    Serial.println("mySerial started at 9600");
    delay(2000);
    Serial.println("Setup Complete! mySerial is Ready!");
    mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
    delay(3000);
    SendMessagex();
    delay(3000);
}

void loop() {
  //Serial.println("WOY");
  while(Serial.available()) {
    gps.encode(Serial.read());
  }
  if (mySerial.available())
    { c = mySerial.read();
      Serial.write(c);
      }
    if (c=='z'){
      Serial.println("KIRIMBOSS");
      delay(1000); 
      SendMessage(); 
      //delay(5000);
    }
    gps.location.isUpdated();
    latitude = String(gps.location.lat(),6);
    longitude = String(gps.location.lng(),6);
    String link = "www.google.com/maps/place/" + String(latitude) + "," + String(longitude) ;
    Serial.println(link);
    delay(100);
}

void SendMessage()
{
  gps.location.isUpdated();
    latitude = String(gps.location.lat(),6);
    longitude = String(gps.location.lng(),6);
    String link = "www.google.com/maps/place/" + String(latitude) + "," + String(longitude) ;
  
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+6287775593898\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("KOORDINAT");// The SMS text you want to send
  mySerial.println(link);
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void SendMessagex()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+6287775593898\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("INFORMASI");// The SMS text you want to send
  mySerial.println("MOTOR TELAH DINYALAKAN");
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
