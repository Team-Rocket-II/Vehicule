#include <WiFi.h>
#include <WiFiUdp.h>

#define PCF8574_INITIAL_VALUE 0x7F
#include "PCF8574.h"

// Definitions Arduino pins connected to input H Bridge
int GAV1 = 14;  // IN1 pour moteur 1
int GAV2 = 27;  // IN2 pour moteur 1
int DAV1 = 12;  // IN3 pour moteur 2
int DAV2 = 13;  // IN4 pour moteur 2
int DAR1 = 25;  // IN1 pour moteur 3
int DAR2 = 26;  // IN2 pour moteur 3
int GAR1 = 18;  // IN3 pour moteur 4
int GAR2 = 19;  // IN4 pour moteur 4



int x;
int err;
int result;
int compteur = 0;

int vitesseMoteur = 125;  // Valeur PWM par défaut (0 à 255)

// WiFi settings (non utilisés, mais gardés pour la structure)
// const char* cSsidAP = "192,168,1,117";  //IP du 2ieme ESP?
// const char* cPasswordAP = "CoucouFred";
// IPAddress SubnetAP(255, 255, 255, 0);
// IPAddress GatewayAP(192, 168, 69, 1);
// IPAddress LocalIpAP(192, 168, 69, 1);

PCF8574 PCF_01(0x22);

void LectureI2C() {
  x = PCF_01.read8();
}

int checkValue() {
  switch (x) {
    case 0x70: case 0x78: case 0x7C: case 0x7E: err = -7; break;
    case 0x40: err = -6; break;
    case 0x60: err = -5; break;
    case 0x20: err = -4; break;
    case 0x30: err = -3; break;
    case 0x10: err = -2; break;
    case 0x18: err = -1; break;
    case 0x08: err = 0; break;
    case 0x0c: err = 1; break;
    case 0x04: err = 2; break;
    case 0x06: err = 3; break;
    case 0x02: err = 4; break;
    case 0x03: err = 5; break;
    case 0x01: err = 6; break;
    case 0x07: case 0x0F: case 0x1F: case 0x3F: err = 7; break;
    case 0x00: err = 10; break;
    default: err = -9; break;
  }
  return err;
}

void setup() {
  // Set the output pins for motor control
  pinMode(GAV1, OUTPUT);  // IN1 moteur 1
  pinMode(GAV2, OUTPUT);  // IN2 moteur 1
  pinMode(DAV1, OUTPUT);  // IN3 moteur 2
  pinMode(DAV2, OUTPUT);  // IN4 moteur 2
  pinMode(GAR1, OUTPUT);  // IN1 moteur 3
  pinMode(GAR2, OUTPUT);  // IN2 moteur 3
  pinMode(DAR1, OUTPUT);  // IN3 moteur 4
  pinMode(DAR2, OUTPUT);  // IN4 moteur 4


  digitalWrite(GAV1, LOW);
  digitalWrite(GAV2, LOW);
  digitalWrite(DAV1, LOW);
  digitalWrite(DAV2, LOW);
  digitalWrite(GAR1, LOW);
  digitalWrite(GAR2, LOW);
  digitalWrite(DAR1, LOW);
  digitalWrite(DAR2, LOW);


  Serial.begin(115200);
  Wire.begin();
  PCF_01.begin();
}

void loop() {
  LectureI2C();
  result = checkValue();

  // Supposons que 'result' est la sortie de vos capteurs (peut être un nombre représentant la position)
  if (result == 3 || result == 2 || result == 1) {  // Capteur de ligne à droite actif
    tournerDroite();
  }
  else if (result == 0) {  // Capteur de ligne au milieu actif
    allerToutDroit();
  }
  else if (result == -1 || result == -2 || result == -3) {  // Capteur de ligne à gauche actif
    tournerGauche();
  }
  else if(result == 10){ // Pas de capteur activé (on arrête)
    Arreter();
  }

  // Si une ligne transversale est détectée
  if (result == 6 || result == -6 || result == 7 || result == -7 || result == 5 || result == -5) {
    activerLigneTransversale();
  }

  delay(100);  // Petit délai pour éviter de saturer la boucle
}

// Fonction pour avancer tout droit
void allerToutDroit() {
  analogWrite(GAV1, LOW);  // Contrôle de vitesse via PWM
  analogWrite(GAV2, vitesseMoteur);
  analogWrite(DAV1, LOW);  // Contrôle de vitesse via PWM
  analogWrite(DAV2, vitesseMoteur);
  analogWrite(GAR1, LOW);  // Contrôle de vitesse via PWM
  analogWrite(GAR2, vitesseMoteur);
  analogWrite(DAR1, LOW);  // Contrôle de vitesse via PWM
  analogWrite(DAR2, vitesseMoteur);
}

// Fonction pour tourner à droite
void tournerDroite() {
  analogWrite(GAV1, vitesseMoteur);
  analogWrite(GAV2, LOW);  // Contrôle de vitesse via PWM
  analogWrite(DAV1, LOW);  // Contrôle de vitesse via PWM
  analogWrite(DAV2, vitesseMoteur);
  analogWrite(GAR1, vitesseMoteur);
  analogWrite(GAR2, LOW);  // Contrôle de vitesse via PWM
  analogWrite(DAR1, LOW);  // Contrôle de vitesse via PWM
  analogWrite(DAR2, vitesseMoteur);
}

// Fonction pour tourner à gauche
void tournerGauche() {
  analogWrite(GAV1, LOW);  // Contrôle de vitesse via PWM
  analogWrite(GAV2, vitesseMoteur);
  analogWrite(DAV1, vitesseMoteur);
  analogWrite(DAV2, LOW);  // Contrôle de vitesse via PWM
  analogWrite(GAR1, LOW);
  analogWrite(GAR2, vitesseMoteur);  // Contrôle de vitesse via PWM
  analogWrite(DAR1, vitesseMoteur);
  analogWrite(DAR2, LOW);  // Contrôle de vitesse via PWM
}

void Arreter(){  
  analogWrite(GAV1, LOW);
  analogWrite(GAV2, LOW);
  analogWrite(DAV1, LOW);
  analogWrite(DAV2, LOW);
  analogWrite(GAR1, LOW);
  analogWrite(GAR2, LOW);
  analogWrite(DAR1, LOW);
  analogWrite(DAR2, LOW);
}

// Fonction pour gérer la détection d'une ligne transversale
void activerLigneTransversale() {
  // Avancer après avoir détecté une ligne transversale
  allerToutDroit();

  // Incrémenter le compteur et afficher le résultat
  delay(200);
  compteur++;
  Serial.println(compteur);

  // Ajouter un délai si nécessaire, mais sans bloquer l'exécution principale
  delay(500);
}
