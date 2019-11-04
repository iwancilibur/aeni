#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial Serial1(11, 10);
//SoftwareSerial serial_gps(8, 9); 
TinyGPSPlus gps;
String latitude, longitude;
char c = ' ';

void setup() {
    Serial.begin(9600);
    Serial.begin(9600);
    //Serial.println("GPS Mulai");
    //while(!Serial);
   Serial.println("Arduino with Serial1 is ready");
 
    // start communication with the Serial1 in 9600
    Serial1.begin(115200);  
    Serial.println("Serial1 started at 9600");
    Serial1.println("AT+CMGF=1");
    delay(2000);
    Serial.println("Setup Complete! Serial1 is Ready!");
    Serial1.println("AT+CNMI=1,2,0,0,0"); // AT Command to recieve a live SMS
    delay(3000);
    SendMessagex();
    delay(3000); 
    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
}

void loop() {
  
  if (Serial1.available())
    { c = Serial1.read();
      Serial.write(c);
    }
    if (c=='z'){
      Serial.println("KIRIMBOSS");
      delay(1000); 
      SendMessage(); 
      //delay(5000);
    }else if (c=='x'){
      //HIDUPKAN KONTAK KEMBALI
      digitalWrite(12,HIGH);
    }else if (c=='y'){
      //MATIKAN KONTAK JARAK JAUH
      digitalWrite(12,LOW);
    }else if (c=='w'){
      //AKTIFKAN SYSTEM KEAMANAN
      SendMessageaktifkan();
    }else if (c=='v'){
      //MATIKAN SYSTEM KEAMANAN
      digitalWrite(13,LOW);
    }
  int data=analogRead(A0);
  int cekled=digitalRead(13);
    if(data<500 && cekled==HIGH){//KEADAAN MOTOR ON / KONTAK DINYALAKAN
    SendMessagekontak();
    delay(1000);
    digitalWrite(13,LOW);
  }

  while(Serial.available()) {
    gps.encode(Serial.read());
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
  
  Serial1.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial1.println("AT+CMGS=\"+6281299004884\"\r"); // Replace x with mobile number
  delay(1000);
  Serial1.println("INFORMASI!!!");
  Serial1.println("-----------");
  Serial1.println("PERMINTAAN LOKASI MOTOR");// The SMS text you want to send
  Serial1.println("Ada Pada Koordinat:");
  Serial1.println(link);
  delay(100);
   Serial1.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


void SendMessagekontak()
{
  gps.location.isUpdated();
    latitude = String(gps.location.lat(),6);
    longitude = String(gps.location.lng(),6);
    String link = "www.google.com/maps/place/" + String(latitude) + "," + String(longitude) ;
  
  Serial1.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial1.println("AT+CMGS=\"+6281299004884\"\r"); // Replace x with mobile number
  delay(1000);
  Serial1.println("PERINGATAN!!!");
  Serial1.println("-------------");
  Serial1.println("MOTOR ANDA TELAH DINYALAKAN");// The SMS text you want to send
  Serial1.println("Pada Koordinat:");
  Serial1.println(link);
  delay(100);
   Serial1.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void SendMessagex()
{
  Serial1.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial1.println("AT+CMGS=\"+6281299004884\"\r"); // Replace x with mobile number
  delay(1000);
  Serial1.println("INFORMASI!!!");
  Serial1.println("-----------");
  Serial1.println("SYSTEM KEAMANAN KENDARAAN PADA SEPEDA MOTOR");// The SMS text you want to send
  Serial1.println("TELAH DIAKTIFKAN");
  Serial1.println("-----------");
  Serial1.println("Created By:");
  Serial1.println("NURAENI PUJI ASTUTI");
  Serial1.println("131105150400");
  delay(100);
   Serial1.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void SendMessageaktifkan()
{
  Serial1.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial1.println("AT+CMGS=\"+6281299004884\"\r"); // Replace x with mobile number
  delay(1000);
  Serial1.println("INFORMASI!!!");
  Serial1.println("-----------");
  Serial1.println("SYSTEM KEAMANAN");// The SMS text you want to send
  Serial1.println("TELAH DIAKTIFKAN");
  Serial1.println("-----------");
  delay(100);
   Serial1.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  digitalWrite(13,HIGH);
}
