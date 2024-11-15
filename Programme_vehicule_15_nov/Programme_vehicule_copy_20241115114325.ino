//  #include <WiFi.h>
//  #include <WiFiUdp.h>

//  #define LED 13
// /**************************************************************************************************
// Nom du programme :
// Auteur : Marie-Pier Morin
// Date de création : 11 novembre 2024
// Modification : Marie-Pier Morin
// Date de modification : 11 novembre 2024
// Note :
// ***************************************************************************************************/

//  const char* ssid = "Routeur627";
//  const char* password = "Routeur627";
//  const char* cIP = "192,168,1,114";
//  const char* cSsidAP = "192,168,1,117";
//  const char* cPasswordAP = "CoucouFred";
//  IPAddress SubnetAP(255, 255, 255, 0);
//  IPAddress GatewayAP(192, 168, 23, 1);
//  IPAddress LocalIpAP(192, 168, 23, 1);
//  char cBuffer[7];
//  WiFiUDP udPaul;
// void setup() {
//    Serial.begin(115200);
//    pinMode(14, INPUT);
//    pinMode(13,OUTPUT);

//  // put your setup code here, to run once:
//    //Connection sur le réseau WiFi
//    if (digitalRead(14) == LOW) {
//      Serial.println("LOW");
//      Serial.print("Connection to ");
//      Serial.println(ssid);
//      WiFi.begin(ssid, password);
//      while (WiFi.status() != WL_CONNECTED) {
//        delay(500);
//        Serial.print(".");
//      }
//      //Envoie sur le port série, l'adresse IP
//      Serial.println("");
//      Serial.println("WiFi connected.");
//      Serial.println("IP address:");
//      Serial.println(WiFi.localIP());
//      digitalWrite(LED, LOW);
//    } else {
//      Serial.println("HIGH");
//      WiFi.mode(WIFI_AP);
//      WiFi.softAP(cSsidAP, cPasswordAP);
//      WiFi.softAPConfig(LocalIpAP, GatewayAP, SubnetAP);
//      Serial.print("Soft-AP IP address =");
//      Serial.println(WiFi.softAPIP());
//      digitalWrite(LED, HIGH);
//    }
//    udPaul.begin(10024);
//  }
//  void loop() {
//    if(udPaul.parsePacket()>0)
//    {
//      udPaul.read(cBuffer, 7);
//      Serial.println("AH!!");
//      Serial.println(cBuffer);

//      udPaul.beginPacket(udPaul.remoteIP(), 10025);
//    if(digitalRead(14) == LOW)
//    {
//      udPaul.write(0);
//    }
//    else
//    {
//    udPaul.write(1);
//    }
//    udPaul.endPacket();
//    }
//    // put your main code here, to run repeatedly:
//  }

/*==========================================================================
// Author : Handson Technology
// Project : Arduino Uno
// Description : L298N Motor Driver
// Source-Code : L298N_Motor.ino
// Program: Control 2 DC motors using L298N H Bridge Driver
//==========================================================================
*/

#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>

#define PCF8574_INITIAL_VALUE       0x7F
#include "PCF8574.h"

// Definitions Arduino pins connected to input H Bridge
// int GAV1 = 14;  //gauche av in1
// int GAV2 = 32;  //gauche av in2
// int DAV1 = 15;  //droit av  in3
// int DAV2 = 33;  // droit av in4

// int GAR1 = 27;  //gauche ar in1
// int GAR2 = 12;  //gauche ar in2
// int DAR1 = 17;  //droit ar  in3
// int DAR2 = 21;  //droit ar  in4
//14 - 32 / 15 - 33 / 27 - 12 / 21 - 17
// bourgo gris blanc noir blanc gris // mauve orange COULEUR DES FILS



#define TRUE 1
#define FALSE 0

const char* cSsidAP = "192,168,1,117";  //IP du 2ieme ESP?
const char* cPasswordAP = "CoucouFred";
IPAddress SubnetAP(255, 255, 255, 0);
IPAddress GatewayAP(192, 168, 69, 1);
IPAddress LocalIpAP(192, 168, 69, 1);

PCF8574 PCF_01(0x22);

void LectureI2C() {
  //

 char bob = Wire.read();
Serial.println("bob");
 Serial.print(bob);
  //digitalRead(SDA)
  //return PositionLigne
}



void setup() {
  //void UDP();
  Serial.begin(115200);
  Wire.begin();
  PCF_01.begin();



  // Set the output pins
  //Drive #1 AVANT
  // pinMode(GAV1, OUTPUT);
  // pinMode(GAV2, OUTPUT);
  // pinMode(DAV1, OUTPUT);
  // pinMode(DAV2, OUTPUT);
  // //Drive #2 APRÈS
  // pinMode(GAR1, OUTPUT);
  // pinMode(GAR2, OUTPUT);
  // pinMode(DAR1, OUTPUT);
  // pinMode(DAR2, OUTPUT);

  // void ModeTest();
}




void loop() {
  //void Vehicule();
  //LectureI2C();

  int x = PCF_01.read8();
  Serial.print("Read ");
  Serial.println(x, HEX);
  delay(100);
}

// void UDP(){
//     // WiFi.mode(WIFI_AP);
//     // WiFi.softAP(cSsidAP, cPasswordAP);
//     // WiFi.softAPConfig(LocalIpAP, GatewayAP, SubnetAP);
//     // Serial.print("Soft-AP IP address =");
//     // Serial.println(WiFi.softAPIP());


// }
// void Vehicule() {
//   static unsigned char ucX = 0;
//   static unsigned char ucY = 0;

//   // if (MessageAbort == TRUE) {
//   //   //ModeAbort
//   // } else if (MessageTest == TRUE) {
//   //   //ModeTest
//   // } else {
//     //ModeSuiveur
//     if (ucErr == -9) {
//       ucX++;
//       ucY = 0;
//       if (ucX >= 53) {
//         ucValsGD = uiNeutre;
//         eMode = CALME;
//       }
//     }
//    // else(suivre la ligne et avancer)
//   }
// }

//void ModeAbort() {
//digitalWrite(IN1A, LOW);
//digitalWrite(IN2A, LOW);
//digitalWrite(IN3A, LOW);
//digitalWrite(IN4A, LOW);
//digitalWrite(IN1B, LOW);
//digitalWrite(IN2B, LOW);
//digitalWrite(IN3B, LOW);
//digitalWrite(IN4B, LOW);
//Envoie Arrêter à la tour de contrôle?
//}

// void SuiveurDeLigne() {
//   LectureI2C();

//   switch (PositionLigne) {
//     case 0x70:
//     case 0x78:
//     case 0x7C:
//     case 0x7E:
//       err = -7;
//       break;
//     case 0x40:
//       err = -6;
//       break;
//     case 0x60:
//       err = -5;
//       break;
//     case 0x20:
//       err = -4;
//       break;
//     case 0x30:
//       err = -3;
//       break;
//     case 0x10:

//       err = -2;
//       break;
//     case 0x18:

//       err = -1;
//       break;

//     case 0x08:
//       err = 0;
//       break;

//     case 0x0c:

//       err = 1;
//       break;
//     case 0x04:

//       err = 2;
//       break;
//     case 0x06:
//       err = 3;
//       break;
//     case 0x02:
//       err = 4;
//       break;
//     case 0x03:
//       err = 5;
//       break;
//     case 0x01:
//       err = 6;
//       break;
//     case 0x07:
//     case 0x0F:
//     case 0x1F:
//     case 0x3F:
//       err = 7;
//       break;

//     case 0x00:  //Hors Piste

//       err = 10;
//       break;
//     default:

//       err = -9;
//       break;
//   }
//   return err;
// }
// }



//void TransmissionPosition();
//void ReceptionMessage();


// void ModeTest() {
//   // Rotate the Motor A clockwise
//   digitalWrite(IN1A, HIGH);
//   digitalWrite(IN2A, LOW);
//   //Rotate the Motor B clockwise
//   digitalWrite(IN3A, HIGH);
//   digitalWrite(IN4A, LOW);
//   // Rotate the Motor C clockwise
//   digitalWrite(IN1B, HIGH);
//   digitalWrite(IN2B, LOW);
//   // Rotate the Motor D clockwise
//   digitalWrite(IN3B, HIGH);
//   digitalWrite(IN4B, LOW);
//   delay(5000);
//   // Motor A
//   digitalWrite(IN1A, HIGH);
//   digitalWrite(IN2A, HIGH);
//   digitalWrite(IN3A, HIGH);
//   digitalWrite(IN4A, HIGH);
//   digitalWrite(IN1B, HIGH);
//   digitalWrite(IN2B, HIGH);
//   digitalWrite(IN3B, HIGH);
//   digitalWrite(IN4B, HIGH);
//   delay(500);
//   ///////////////////////////////////////////////////
//   //Rotates the Motor A counter-clockwise
//   digitalWrite(IN1A, LOW);
//   digitalWrite(IN2A, HIGH);
//   //Rotate the Motor B counter-clockwise
//   digitalWrite(IN3A, LOW);
//   digitalWrite(IN4A, HIGH);
//   // Rotate the Motor C counter-clockwise
//   digitalWrite(IN1B, LOW);
//   digitalWrite(IN2B, HIGH);
//   // Rotate the Motor D counter-clockwise
//   digitalWrite(IN3B, LOW);
//   digitalWrite(IN4B, HIGH);
//   delay(5000);
//   // Motor A
//   digitalWrite(IN1A, HIGH);
//   digitalWrite(IN2A, HIGH);
//   digitalWrite(IN3A, HIGH);
//   digitalWrite(IN4A, HIGH);
//   digitalWrite(IN1B, HIGH);
//   digitalWrite(IN2B, HIGH);
//   digitalWrite(IN3B, HIGH);
//   digitalWrite(IN4B, HIGH);
//   delay(500);
// }
