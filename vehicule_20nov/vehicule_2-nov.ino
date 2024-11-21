
#include <WiFi.h>
#include <WiFiUdp.h>

#define PCF8574_INITIAL_VALUE 0x7F
#include "PCF8574.h"


// Definitions Arduino pins connected to input H Bridge
int GAV1 = 14;
int GAV2 = 27;
// Moteur 2 (L298N 1)
int DAV1 = 12;
int DAV2 = 13;
// Moteur 3 (L298N 2)
int DAR1 = 25;
int DAR2 = 26;
// Moteur 4 (L298N 2)
int GAR1 = 18;
int GAR2 = 19;


int PWMDRIVE1A = 32;  // Utiliser GPIO 32
int PWMDRIVE1B = 33;  // Utiliser GPIO 33
int PWMDRIVE2A = 15;  // Utiliser GPIO 15
int PWMDRIVE2B = 16;  // Utiliser GPIO 16


int x;
int err;
int  result;
int compteur = 0;

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

// #define TRUE 1
// #define FALSE 0

const char* cSsidAP = "192,168,1,117";  //IP du 2ieme ESP?
const char* cPasswordAP = "CoucouFred";
IPAddress SubnetAP(255, 255, 255, 0);
IPAddress GatewayAP(192, 168, 69, 1);
IPAddress LocalIpAP(192, 168, 69, 1);

PCF8574 PCF_01(0x22);
//int mode = 1;

void LectureI2C() {
  x = PCF_01.read8();
  // Serial.print("Read ");
  // Serial.println(x, HEX);
  // Serial.println(result);
}

int checkValue(){
  switch (x) {
    case 0x70:
    case 0x78:
    case 0x7C:
    case 0x7E:
      err = -7;
      break;
    case 0x40:
      err = -6;
      break;
    case 0x60:
      err = -5;
      break;
    case 0x20:
      err = -4;
      break;
    case 0x30:
      err = -3;
      break;
    case 0x10:

      err = -2;
      break;
    case 0x18:

      err = -1;
      break;

    case 0x08:
      err = 0;
      break;

    case 0x0c:

      err = 1;
      break;
    case 0x04:

      err = 2;
      break;
    case 0x06:
      err = 3;
      break;
    case 0x02:
      err = 4;
      break;
    case 0x03:
      err = 5;
      break;
    case 0x01:
      err = 6;
      break;
    case 0x07:
    case 0x0F:
    case 0x1F:
    case 0x3F:
      err = 7;
      break;

    case 0x00:  //Hors Piste

      err = 10;
      break;
    default:

      err = -9;
      break;
  }
  return err;
}

//////////////////////////////////////////////////////////////////////////////setup//////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
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

  pinMode(PWMDRIVE1A, OUTPUT);
  pinMode(PWMDRIVE1B, OUTPUT);
  pinMode(PWMDRIVE2A, OUTPUT);
  pinMode(PWMDRIVE2B, OUTPUT);


  analogWrite(PWMDRIVE1A, 128); // 50% de vitesse
  analogWrite(PWMDRIVE1B, 128); // 50% de vitesse
  analogWrite(PWMDRIVE2A, 128); // 50% de vitesse
  analogWrite(PWMDRIVE2B, 128); // 50% de vitesse

  Serial.begin(115200);
  Wire.begin();
  PCF_01.begin();
}

//////////////////////////////////////////////////////////////////////////////loop///////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {

  LectureI2C();

  result = checkValue();

    // digitalWrite(GAV1, HIGH); //recule
    // digitalWrite(GAV2, LOW);
    // digitalWrite(DAV1, LOW); //avance
    // digitalWrite(DAV2, HIGH);
    // digitalWrite(GAR1, HIGH); //droite et recule
    // digitalWrite(GAR2, LOW);
    // digitalWrite(DAR1, LOW); //gauche et avance
    // digitalWrite(DAR2, HIGH);



   if ((result == 6)||(result == -6)) {
    digitalWrite(GAV1, LOW);
    digitalWrite(GAV2, HIGH);
    digitalWrite(DAV1, LOW);
    digitalWrite(DAV2, HIGH);
    digitalWrite(GAR1, LOW);
    digitalWrite(GAR2, HIGH);
    digitalWrite(DAR1, LOW);
    digitalWrite(DAR2, HIGH);
    
    delay(250); 
    compteur ++;
    Serial.println(compteur);
   }
   else if ((result == 3)||(result == 2)||(result == 1)) { // Capteur de ligne à droite actif
    // Tourner à droite (exemple : avancer à droite et reculer à gauche)
    digitalWrite(GAV1, HIGH);
    digitalWrite(GAV2, LOW);
    digitalWrite(DAV1, LOW);
    digitalWrite(DAV2, HIGH);
    digitalWrite(GAR1, HIGH);
    digitalWrite(GAR2, LOW);
    digitalWrite(DAR1, LOW);
    digitalWrite(DAR2, HIGH);
  }
  else if (result == 0){ // Capteur de ligne à droite actif
    // Tout droit
    digitalWrite(GAV1, LOW);
    digitalWrite(GAV2, HIGH);
    digitalWrite(DAV1, LOW);
    digitalWrite(DAV2, HIGH);
    digitalWrite(GAR1, LOW);
    digitalWrite(GAR2, HIGH);
    digitalWrite(DAR1, LOW);
    digitalWrite(DAR2, HIGH);
  }
    else if ((result == -1)||(result == -2)||(result == -3)){ // Capteur de ligne à droite actif
    // Tourner à droite 
    digitalWrite(GAV1, LOW);
    digitalWrite(GAV2, HIGH);
    digitalWrite(DAV1, HIGH);
    digitalWrite(DAV2, LOW);
    digitalWrite(GAR1, LOW);
    digitalWrite(GAR2, HIGH);
    digitalWrite(DAR1, HIGH);
    digitalWrite(DAR2, LOW);
  }

  //   else if ((result == -4)||(result == -5)||(result == -6)||(result == -7)) { // Capteur de ligne à droite actif
  //   // Tourner à droite beaucoup
  //   digitalWrite(GAV1, LOW);
  //   digitalWrite(GAV2, HIGH);
  //   digitalWrite(DAV1, HIGH);
  //   digitalWrite(DAV2, LOW);
  //   digitalWrite(GAR1, LOW);
  //   digitalWrite(GAR2, HIGH);
  //   digitalWrite(DAR1, HIGH);
  //   digitalWrite(DAR2, LOW);
  // }

  else if((result == -9)||(result == 10)){ // Pas de capteur activé (on avance arrête)
    // Arrêter
    digitalWrite(GAV1, LOW);
    digitalWrite(GAV2, LOW);
    digitalWrite(DAV1, LOW);
    digitalWrite(DAV2, LOW);
    digitalWrite(GAR1, LOW);
    digitalWrite(GAR2, LOW);
    digitalWrite(DAR1, LOW);
    digitalWrite(DAR2, LOW);
  }


  if(compteur == 3){
      // compteur = 0;
          digitalWrite(GAV1, LOW);
    digitalWrite(GAV2, LOW);
    digitalWrite(DAV1, LOW);
    digitalWrite(DAV2, LOW);
    digitalWrite(GAR1, LOW);
    digitalWrite(GAR2, LOW);
    digitalWrite(DAR1, LOW);
    digitalWrite(DAR2, LOW);
      delay(5000);
    digitalWrite(GAV1, HIGH);
    digitalWrite(GAV2, LOW);
    digitalWrite(DAV1, LOW);
    digitalWrite(DAV2, HIGH);
    digitalWrite(GAR1, HIGH);
    digitalWrite(GAR2, LOW);
    digitalWrite(DAR1, LOW);
    digitalWrite(DAR2, HIGH);
    delay(2500);
     compteur = 0;
    }
 
    delay(100);
}







