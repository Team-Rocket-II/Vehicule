
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>

#define PCF8574_INITIAL_VALUE 0x7F
#include "PCF8574.h"

// Definitions Arduino pins connected to input H Bridge
int GAV1 = 14;  //gauche av in1
int GAV2 = 32;  //gauche av in2
int DAV1 = 15;  //droit av  in3
int DAV2 = 33;  // droit av in4

int GAR1 = 27;  //gauche ar in1
int GAR2 = 12;  //gauche ar in2
int DAR1 = 17;  //droit ar  in3
int DAR2 = 21;  //droit ar  in4
//14 - 32 / 15 - 33 / 27 - 12 / 21 - 17
// bourgo gris blanc noir blanc gris // mauve orange COULEUR DES FILS

/*
Différentes fonctions :

initUDP()
ReceptionMessage() 
  SystemeOperation()
    PositionPostedePesage()
    TransmissionPosition() 

  ChoixDuMode() 
    ModeSuiveur()
      AttenteBlocOrangeEtMetal()

      LectureI2C()
      CorrectionPosition()
      TournerADroite()
      TournerAGauche()

      AttenteBalance()
      AttenteAscenseur()

      LectureDistance()
      TransmissionPosition() 
        CompteurDistance()
          DemiTour()

    ModeTest()
      AvanceBeaucoup()
      AvanceUnPeu()
      TournerADroiteUnPeu()
      TournerAGaucheUnPeu()
      TournerADroiteBeaucoup()
      TournerAGaucheBeaucoup()
      DemiTour()

    ModeAbort()

*/

#define TRUE 1
#define FALSE 0

const char* cSsidAP = "192,168,1,117";  //IP du 2ieme ESP?
const char* cPasswordAP = "CoucouFred";
IPAddress SubnetAP(255, 255, 255, 0);
IPAddress GatewayAP(192, 168, 69, 1);
IPAddress LocalIpAP(192, 168, 69, 1);

PCF8574 PCF_01(0x22);
int mode = 1;

/*void LectureI2C() {
  int x = PCF_01.read8();
  Serial.print("Read ");
  Serial.println(x, HEX);
  delay(100);
}*/
/* void initUDP(){
 WiFi.mode(WIFI_AP);
 WiFi.softAP(cSsidAP, cPasswordAP);
 WiFi.softAPConfig(LocalIpAP, GatewayAP, SubnetAP);
 Serial.print("Soft-AP IP address =");
 Serial.println(WiFi.softAPIP());
// }*/

/*void TransmissionPosition(){


}*/

/*void ReceptionMessage(){
  if(SystemeOperation == TRUE){
    POSITION == StationDePesage;
    TransmissionPosition(POSITION); 
  }
  switch(mode){
    case 1:
    mode = ModeAbort();
    break;
    case 2:
    mode = ModeTest();
    breal;
    case 3:
    mode = ModeSuiveur();

  }
}*/

void ModeAbort() {
  digitalWrite(GAV1, LOW);
  digitalWrite(GAV2, LOW);
  digitalWrite(DAV1, LOW);
  digitalWrite(DAV2, LOW);
  digitalWrite(GAR1, LOW);
  digitalWrite(GAR2, LOW);
  digitalWrite(DAR1, LOW);
  digitalWrite(DAR2, LOW);
}


void setup() {
 
  Serial.begin(115200);
  Wire.begin();
  PCF_01.begin();
  //initUDP();

  // Set the output pins
  //Drive #1 AVANT
  pinMode(GAV1, OUTPUT);
  pinMode(GAV2, OUTPUT);
  pinMode(DAV1, OUTPUT);
  pinMode(DAV2, OUTPUT);
  //Drive #2 APRÈS
  pinMode(GAR1, OUTPUT);
  pinMode(GAR2, OUTPUT);
  pinMode(DAR1, OUTPUT);
  pinMode(DAR2, OUTPUT);

  ModeTest();
}

void ModeTest(){
  AvanceBeaucoup();
    ALLHIGH();
    delay(5000);
  ReculeBeaucoup();
    ALLHIGH();
    delay(5000);
  AvanceUnPeu();
    ALLHIGH();
    delay(5000);
  ReculeUnPeu();
    ALLHIGH();
    delay(5000);

  TournerADroiteUnPeu();
    delay(2000);
  TournerAGaucheUnPeu();
    delay(2000);
  TournerADroiteBeaucoup();
    delay(2000);
  TournerAGaucheBeaucoup();
    delay(2000);
  DemiTour();
    delay(2000);
}

void loop() {
  //void Vehicule();
  //LectureI2C();
  //ModeTest();
}



/*void Vehicule() {
  static unsigned char ucX = 0;
  static unsigned char ucY = 0;

   if (MessageAbort == TRUE) {
      //ModeAbort
   } else if (MessageTest == TRUE) {
      //ModeTest
    } else {
     //ModeSuiveur
    if (ucErr == -9) {
       ucX++;
      ucY = 0;
       if (ucX >= 53) {
         ucValsGD = uiNeutre;
         eMode = CALME;
      }
     }
   else(suivre la ligne et avancer)
  }
 }*/



// void ModeSuiveur() {
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


void AvanceBeaucoup(){
  // Rotate the Motor A clockwise
  digitalWrite(GAV1, HIGH);
  digitalWrite(GAV2, LOW);
  //Rotate the Motor B clockwise
  digitalWrite(DAV1, HIGH);
  digitalWrite(DAV2, LOW);
  // Rotate the Motor C clockwise
  digitalWrite(GAR1, HIGH);
  digitalWrite(GAR2, LOW);
  // Rotate the Motor D clockwise
  digitalWrite(DAR1, HIGH);
  digitalWrite(DAR2, LOW);
}
void AvanceUnPeu(){
  // Rotate the Motor A clockwise
  digitalWrite(GAV1, HIGH);
  digitalWrite(GAV2, LOW);
  //Rotate the Motor B clockwise
  digitalWrite(DAV1, HIGH);
  digitalWrite(DAV2, LOW);
  // molle?
  digitalWrite(GAR1, HIGH);
  digitalWrite(GAR2, HIGH);
  // molle?
  digitalWrite(DAR1, HIGH);
  digitalWrite(DAR2, HIGH);
}
void ReculeBeaucoup(){
  //Rotates the Motor A counter-clockwise
  digitalWrite(GAV1, LOW);
  digitalWrite(GAV2, HIGH);
  //Rotate the Motor B counter-clockwise
  digitalWrite(DAV1, LOW);
  digitalWrite(DAV2, HIGH);
  // Rotate the Motor C counter-clockwise
  digitalWrite(GAR1, LOW);
  digitalWrite(GAR2, HIGH);
  // Rotate the Motor D counter-clockwise
  digitalWrite(DAR1, LOW);
  digitalWrite(DAR2, HIGH);
}
void ReculeUnPeu(){
  //Rotates the Motor A counter-clockwise
  digitalWrite(GAV1, LOW);
  digitalWrite(GAV2, HIGH);
  //Rotate the Motor B counter-clockwise
  digitalWrite(DAV1, LOW);
  digitalWrite(DAV2, HIGH);
  // molle?
  digitalWrite(GAR1, HIGH);
  digitalWrite(GAR2, HIGH);
  // molle?
  digitalWrite(DAR1, HIGH);
  digitalWrite(DAR2, HIGH);
}
void TournerADroiteUnPeu(){
  //Rotates the Motor A counter-clockwise
  digitalWrite(GAV1, LOW);
  digitalWrite(GAV2, HIGH);
  //Rotate the Motor B clockwise
  digitalWrite(DAV1, HIGH);
  digitalWrite(DAV2, LOW);
  // molle?
  digitalWrite(GAR1, HIGH);
  digitalWrite(GAR2, HIGH);
  // molle?
  digitalWrite(DAR1, HIGH);
  digitalWrite(DAR2, HIGH);
}
void TournerAGaucheUnPeu(){
  // Rotate the Motor A clockwise
  digitalWrite(GAV1, HIGH);
  digitalWrite(GAV2, LOW);
  //Rotate the Motor B counter-clockwise
  digitalWrite(DAV1, LOW);
  digitalWrite(DAV2, HIGH);
  // molle?
  digitalWrite(GAR1, HIGH);
  digitalWrite(GAR2, HIGH);
  // molle?
  digitalWrite(DAR1, HIGH);
  digitalWrite(DAR2, HIGH);
}
void TournerADroiteBeaucoup(){
  //Rotates the Motor A counter-clockwise
  digitalWrite(GAV1, LOW);
  digitalWrite(GAV2, HIGH);
  //Rotate the Motor B clockwise
  digitalWrite(DAV1, HIGH);
  digitalWrite(DAV2, LOW);
  // Rotate the Motor C counter-clockwise
  digitalWrite(GAR1, LOW);
  digitalWrite(GAR2, HIGH);
  // Rotate the Motor D clockwise
  digitalWrite(DAR1, HIGH);
  digitalWrite(DAR2, LOW);
}
void TournerAGaucheBeaucoup(){
  // Rotate the Motor A clockwise
  digitalWrite(GAV1, HIGH);
  digitalWrite(GAV2, LOW);
  //Rotate the Motor B counter-clockwise
  digitalWrite(DAV1, LOW);
  digitalWrite(DAV2, HIGH);
  // Rotate the Motor C clockwise
  digitalWrite(GAR1, HIGH);
  digitalWrite(GAR2, LOW);
  // Rotate the Motor D counter-clockwise
  digitalWrite(DAR1, LOW);
  digitalWrite(DAR2, HIGH);
}
void DemiTour(){
  //Rotates the Motor A counter-clockwise
  digitalWrite(GAV1, LOW);
  digitalWrite(GAV2, HIGH);
  //Rotate the Motor B clockwise
  digitalWrite(DAV1, HIGH);
  digitalWrite(DAV2, LOW);
  // Rotate the Motor C counter-clockwise
  digitalWrite(GAR1, LOW);
  digitalWrite(GAR2, HIGH);
  // Rotate the Motor D clockwise
  digitalWrite(DAR1, HIGH);
  digitalWrite(DAR2, LOW);
  //Trouver délai pour 180*
}
void ALLHIGH(){
  digitalWrite(GAV1, HIGH);
  digitalWrite(GAV2, HIGH);
  digitalWrite(DAV1, HIGH);
  digitalWrite(DAV2, HIGH);
  digitalWrite(GAR1, HIGH);
  digitalWrite(GAR2, HIGH);
  digitalWrite(DAR1, HIGH);
  digitalWrite(DAR2, HIGH);
}
void ALLLOW(){
  digitalWrite(GAV1, LOW);
  digitalWrite(GAV2, LOW);
  digitalWrite(DAV1, LOW);
  digitalWrite(DAV2, LOW);
  digitalWrite(GAR1, LOW);
  digitalWrite(GAR2, LOW);
  digitalWrite(DAR1, LOW);
  digitalWrite(DAR2, LOW);
}



/*
void ModeTest() {
  // Rotate the Motor A clockwise
  digitalWrite(GAV1, HIGH);
  digitalWrite(GAV2, LOW);
  //Rotate the Motor B clockwise
  digitalWrite(DAV1, HIGH);
  digitalWrite(DAV2, LOW);
  // Rotate the Motor C clockwise
  digitalWrite(GAR1, HIGH);
  digitalWrite(GAR2, LOW);
  // Rotate the Motor D clockwise
  digitalWrite(DAR1, HIGH);
  digitalWrite(DAR2, LOW);
  delay(5000);
  // Motor A
  digitalWrite(GAV1, HIGH);
  digitalWrite(GAV2, HIGH);
  digitalWrite(DAV1, HIGH);
  digitalWrite(DAV2, HIGH);
  digitalWrite(GAR1, HIGH);
  digitalWrite(GAR2, HIGH);
  digitalWrite(DAR1, HIGH);
  digitalWrite(DAR2, HIGH);
  delay(500);
  ///////////////////////////////////////////////////
  //Rotates the Motor A counter-clockwise
  digitalWrite(GAV1, LOW);
  digitalWrite(GAV2, HIGH);
  //Rotate the Motor B counter-clockwise
  digitalWrite(DAV1, LOW);
  digitalWrite(DAV2, HIGH);
  // Rotate the Motor C counter-clockwise
  digitalWrite(GAR1, LOW);
  digitalWrite(GAR2, HIGH);
  // Rotate the Motor D counter-clockwise
  digitalWrite(DAR1, LOW);
  digitalWrite(DAR2, HIGH);
  delay(5000);
  // Motor A
  digitalWrite(GAV1, HIGH);
  digitalWrite(GAV2, HIGH);
  digitalWrite(DAV1, HIGH);
  digitalWrite(DAV2, HIGH);
  digitalWrite(GAR1, HIGH);
  digitalWrite(GAR2, HIGH);
  digitalWrite(DAR1, HIGH);
  digitalWrite(DAR2, HIGH);
  delay(500);
 }*/
