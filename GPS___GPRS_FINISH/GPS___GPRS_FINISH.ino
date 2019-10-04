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
    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
}

void loop() {
  if (mySerial.available())
    { c = mySerial.read();
      //Serial.write(c);
      
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
  
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+6281299004884\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("INFORMASI!!!");
  mySerial.println("-----------");
  mySerial.println("PERMINTAAN LOKASI MOTOR");// The SMS text you want to send
  mySerial.println("Ada Pada Koordinat:");
  mySerial.println(link);
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


void SendMessagekontak()
{
  gps.location.isUpdated();
    latitude = String(gps.location.lat(),6);
    longitude = String(gps.location.lng(),6);
    String link = "www.google.com/maps/place/" + String(latitude) + "," + String(longitude) ;
  
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+6281299004884\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("PERINGATAN!!!");
  mySerial.println("-------------");
  mySerial.println("MOTOR ANDA TELAH DINYALAKAN");// The SMS text you want to send
  mySerial.println("Pada Koordinat:");
  mySerial.println(link);
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void SendMessagex()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+6281299004884\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("INFORMASI!!!");
  mySerial.println("-----------");
  mySerial.println("SYSTEM KEAMANAN KENDARAAN PADA SEPEDA MOTOR");// The SMS text you want to send
  mySerial.println("TELAH DIAKTIFKAN");
  mySerial.println("-----------");
  mySerial.println("Created By:");
  mySerial.println("NURAENI PUJI ASTUTI");
  mySerial.println("131105150400");
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void SendMessageaktifkan()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+6281299004884\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("INFORMASI!!!");
  mySerial.println("-----------");
  mySerial.println("SYSTEM KEAMANAN");// The SMS text you want to send
  mySerial.println("TELAH DIAKTIFKAN");
  mySerial.println("-----------");
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  digitalWrite(13,HIGH);
}
