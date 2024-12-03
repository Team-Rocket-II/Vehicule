

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

// Définition des états du véhicule
enum EtatVehicule {
  EN_ATTENTE,        // Le véhicule attend un bloc ou une commande
  SE_DIRIGE_TRI,     // Le véhicule va vers l'usine de tri
  DEMI_TOUR_TRI,     // Le véhicule effectue un demi-tour à l'usine
  CHARGEMENT,        // Le véhicule attend d'être chargé
  SE_DIRIGE_PESAGE,  // Le véhicule retourne vers la station de pesage
  DEMI_TOUR_PESAGE,  // Le véhicule effectue un demi-tour à la station de pesage
  EN_ARRET,          // Le véhicule est en arrêt total (Abort)
  DECHARGEMENT_ORANGE,// Le véhicule attend que le bloc orange soit déchargé
  DECHARGEMENT_METAL, // Le véhicule attend que le bloc métal soit déchargé
  PESER_METAL,        // Le véhicule attend que le bloc orange soit pesé
  DEMI_TOUR_ORANGE,   // Le véhicule fait un demitour après que le poids orange soit déchargé 
  TEST,
};

// Définition des types de blocs
enum TypeBloc {
  AUCUN,   // Aucun bloc détecté ou pris en charge
  NOIR,    // Bloc de couleur noire
  ORANGE,  // Bloc de couleur orange
  METAL    // Bloc de couleur métal
};

EtatVehicule etatVehicule = EN_ATTENTE;  // État initial
TypeBloc blocEnCours = AUCUN;            // Aucun bloc au départ


bool ModeManuel = false;
bool ModeSuiveurflag = true;
bool demitourflag = false;
bool DemiTourloop = false;
bool ModeAbort = false;
bool EnFonction = false;

bool ModeSuiveurOrange = false;
bool ModeSuiveurMetal = false;
bool BlocOrange = false;
bool BlocMetal = false;

bool Vehicule = false;
bool Poids = false;
bool Arriver = false;

int x;
int err;
int Position;
int compteur = 0;

// Valeur PWM par défaut (0 à 255)
int vitesseMoteur = 115;  
int vitesseMoteurTourne = 105;
int vitesseMoteurTourneUnPeu = 100;

const char *ssid2 = "Momo Et Mapi";
const char *password2 = "Fl0t1ll0n808";
const char *ssidEcole = "Routeur627";
const char *passwordEcole = "Routeur627";
const char *ssidRaph = "Le Manoir";
const char *passwordRaph = "Fredy6066";
const char *ssid1 = "Chabot-Vallieres";
const char *password1 = "NicPic641230";

const int port = 8080;
char incomingPacket[50];
char Avancement[10];
WiFiUDP udp;

const char *adresse = "192.168.1.126";  // Adresse de l'ordinateur                                 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!A CHANGER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

PCF8574 PCF_01(0x22);

void LectureI2C() {
  x = PCF_01.read8();
}
int checkValue() {
  switch (x) {
    case 0x70:
    case 0x78:
    case 0x7C:
    case 0x7E: err = -7; break;
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
    case 0x07:
    case 0x0F:
    case 0x1F:
    case 0x3F: err = 7; break;
    case 0x00: err = 10; break;
    default: err = -9; break;
  }
  return err;
}
//////////////////////////////////////////////////////////////////////////  void setup  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {

  pinMode(ciledPin, OUTPUT);

  // Les pins raccorder aux drives sont initialisé en output
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

  // Begin
  Serial.begin(115200);
  Wire.begin();
  PCF_01.begin();
  WiFi.begin(ssid2, password2);

  // Connexion au WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au Wi-Fi...");
  }
  Serial.println("Connecté au Wi-Fi !");

  // Démarrer le serveur
  udp.begin(port);
  Serial.println("Serveur UDP démarré.");
  Serial.print("Adresse IP de l'ESP32 : ");
  Serial.println(WiFi.localIP());  // Affiche l'adresse IP
}
//////////////////////////////////////////////////////////////////////////////////////////  void loop  ////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {

 // Serial.println(Position);
  udpReceiveData();
  udpSend();

 
  if (ModeSuiveurflag == true) {
    ModeSuiveur();
    // Serial.println("Mode Suiveur!");
    // Serial.println(Position);
    //  Serial.println(compteur);
  }
  if (DemiTourloop == true) {
    DemiTour();
    Serial.println(Position);
  }


  if (ModeAbort == true) {
    Arreter();
    EnFonction = false;
  }

  switch (etatVehicule) {
    Serial.println("En Attente");
    case EN_ATTENTE:
      // if (ModeAbort) {
      //   etatVehicule = EN_ARRET;
      // } else
      if ((ModeSuiveurOrange || ModeSuiveurMetal) && (EnFonction)) {  // Ajouter en fonction

        ModeSuiveurflag = true;
        etatVehicule = SE_DIRIGE_TRI;
        Serial.println("Se dirige tri");
      }
      break;

    case SE_DIRIGE_TRI:
      if (Arriver) {  // Ligne transverse détectée
        Serial.println("Arrivé centre de tri");
        ModeSuiveurflag = false;
        Arriver = false;
        DemiTourloop = true;
        etatVehicule = DEMI_TOUR_TRI;

        // Appelle la fonction DemiTour()
      }
      break;

    case DEMI_TOUR_TRI:
      if (demitourflag) {
        //DemiTourloop = false;
        demitourflag = false;  // Demi tour termine

        Serial.println("Demi tour tri");
      }
      etatVehicule = CHARGEMENT;
      Serial.println("Chargement");
      break;

    case CHARGEMENT:
      if (Vehicule) {  // Vérifie si le bloc a été chargé
        if (ModeSuiveurOrange) {
          blocEnCours = ORANGE;
          Serial.println("Orange");
        } else if (ModeSuiveurMetal) {
          blocEnCours = METAL;
          Serial.println("Metal");
        }
        etatVehicule = SE_DIRIGE_PESAGE;
        Serial.println("se dirige pesage");
      }
      break;

    case SE_DIRIGE_PESAGE:
      ModeSuiveurflag = true;  // Suivre la ligne

      if (Arriver) {  // Arrivé à la station de pesage
        Serial.println("Arrivé station de pesage");
        ModeSuiveurflag = false;
        Arriver = false;
        if (blocEnCours == METAL) {
          Arreter();
          etatVehicule = DECHARGEMENT_METAL;

        } else if (blocEnCours == ORANGE) {
          DemiTourloop = true;
          etatVehicule = DEMI_TOUR_ORANGE;
        }
      }
      break;

    case DECHARGEMENT_METAL:
      if (Vehicule == false) {  // Simulation de la pesée
        Serial.println("Poids Metal décharger");
        etatVehicule = PESER_METAL;
        Serial.println("En attente de la peser");
        break;

        case PESER_METAL:
          if (Poids) {
            Serial.println("Poids Metal pesé");
            Poids = false;
            DemiTourloop = true;  // Appelle la fonction DemiTour()
            etatVehicule = DEMI_TOUR_PESAGE;
          }
          break;
        case DEMI_TOUR_PESAGE:
          if (demitourflag) {
            // DemiTourloop = false;
            demitourflag = false;  // Demi tour terminé
            etatVehicule = EN_ATTENTE;
            Serial.println("Demi tour station de pesage");
            ModeSuiveurMetal = false;
            Serial.println("En attente prochain bloc");
          }
      }
      break;
    case DEMI_TOUR_ORANGE:

      Serial.println("Demi tour station de pesage");

      if (demitourflag) {  // Demi tour terminé
                           // DemiTourloop = false;
        demitourflag = false;
        Serial.println("En attente du dechargement orange");
        etatVehicule = DECHARGEMENT_ORANGE;
      }
      break;

    case DECHARGEMENT_ORANGE:
      if (Vehicule == false) {  // Simulation de la pesée
        Serial.println("Poids orange décharger");
        etatVehicule = EN_ATTENTE;
        ModeSuiveurOrange = false;
        Serial.println("En attente prochain bloc");
      }

      break;

      // case EN_ARRET:
      //   Arreter();
      //   break;

    default:
      Serial.println("État inconnu !");
      etatVehicule = TEST;
      break;
  }
  delay(100);  // Petit délai pour éviter de saturer la boucle
}

void DemiTour() {
  LectureI2C();
  Position = checkValue();
  analogWrite(GAV1, vitesseMoteur);// Contrôle de vitesse via PWM
  analogWrite(GAV2, LOW);  
  analogWrite(DAV1, LOW);  
  analogWrite(DAV2, vitesseMoteur);// Contrôle de vitesse via PWM
  analogWrite(GAR1, vitesseMoteurTourne);// Contrôle de vitesse via PWM
  analogWrite(GAR2, LOW);  
  analogWrite(DAR1, LOW);  
  analogWrite(DAR2, vitesseMoteurTourne);// Contrôle de vitesse via PWM

  if (Position == 0) {
    Arreter();
    demitourflag = true;
    Serial.println("Demi-tour complété");
    DemiTourloop = false;
  }
  // Serial.println("Retour loop");
  delay(100);
}

void ModeSuiveur() {
  // Bouger pour lire seulement lorsque mouvement / ModeSuiveur actif
  LectureI2C();
  // Changer la variable Position dans la loop pour toujours vérifier ou on est rendu.
  Position = checkValue();
  if (Position == -2) {  // Capteur de ligne à droite actif
    tournerBeaucoupDroite();
  } else if (Position == -1) {  // Capteur de ligne à droite et milieu actif
    tournerDroite();
  } else if (Position == 0) {  // Capteur de ligne au milieu actif
    allerToutDroit();
  } else if (Position == 1) {  // Capteur de ligne à gauche et milieu actif
    tournerGauche();
  } else if (Position == 2) {  // Capteur de ligne à gauche actif
    tournerBeaucoupGauche();
  } else if ((Position == 10) || (Position == -9)) {  // Pas de capteur activé (on arrête)
    Arreter();
  }

  // Si une ligne transversale est détectée
  if (Position == 6 || Position == -6 || Position == 7 || Position == -7 || Position == 5 || Position == -5) {
    activerLigneTransversale();
  }
  delay(100);
}

void allerToutDroit() {// Fonction pour avancer tout droit
  analogWrite(GAV1, LOW);
  analogWrite(GAV2, vitesseMoteur);  // Contrôle de vitesse via PWM
  analogWrite(DAV1, LOW);
  analogWrite(DAV2, vitesseMoteur);  // Contrôle de vitesse via PWM
  analogWrite(GAR1, LOW);
  analogWrite(GAR2, vitesseMoteur);  // Contrôle de vitesse via PWM
  analogWrite(DAR1, LOW);
  analogWrite(DAR2, vitesseMoteur);  // Contrôle de vitesse via PWM
}
void ReculeLigneDroite() {// Fonction pour reculer
  analogWrite(GAV1, vitesseMoteur);  // Contrôle de vitesse via PWM
  analogWrite(GAV2, LOW);
  analogWrite(DAV1, vitesseMoteur);  // Contrôle de vitesse via PWM
  analogWrite(DAV2, LOW);
  analogWrite(GAR1, vitesseMoteur);  // Contrôle de vitesse via PWM
  analogWrite(GAR2, LOW);
  analogWrite(DAR1, vitesseMoteur);  // Contrôle de vitesse via PWM
  analogWrite(DAR2, LOW);
}
void tournerGauche() {// Fonction pour tourner à gauche
  analogWrite(GAV1, LOW);
  analogWrite(GAV2, 100);  // Contrôle de vitesse via PWM
  analogWrite(DAV1, LOW);
  analogWrite(DAV2, 95);  // Contrôle de vitesse via PWM

  analogWrite(GAR1, vitesseMoteurTourne);  // Contrôle de vitesse via PWM
  analogWrite(GAR2, LOW);
  analogWrite(DAR1, LOW);
  analogWrite(DAR2, vitesseMoteurTourne);  // Contrôle de vitesse via PWM
}

void tournerBeaucoupGauche() {// Fonction pour tourner à gauche beaucoup
  analogWrite(GAV1, LOW);
  analogWrite(GAV2, 100);  // Contrôle de vitesse via PWM
  analogWrite(DAV1, LOW);
  analogWrite(DAV2, 95);  // Contrôle de vitesse via PWM

  analogWrite(GAR1, vitesseMoteurTourne);  // Contrôle de vitesse via PWM
  analogWrite(GAR2, LOW);
  analogWrite(DAR1, LOW);
  analogWrite(DAR2, vitesseMoteurTourne);  // Contrôle de vitesse via PWM
}

void tournerDroite() {// Fonction pour tourner à droite
  analogWrite(GAV1, LOW);
  analogWrite(GAV2, 100);  // Contrôle de vitesse via PWM
  analogWrite(DAV1, LOW);
  analogWrite(DAV2, 95);  // Contrôle de vitesse via PWM

  analogWrite(GAR1, LOW);
  analogWrite(GAR2, vitesseMoteurTourne);  // Contrôle de vitesse via PWM
  analogWrite(DAR1, vitesseMoteurTourne);  // Contrôle de vitesse via PWM
  analogWrite(DAR2, LOW);
}

void tournerBeaucoupDroite() {// Fonction pour tourner à droite beaucoup
  analogWrite(GAV1, LOW);
  analogWrite(GAV2, 100);  // Contrôle de vitesse via PWM
  analogWrite(DAV1, LOW);
  analogWrite(DAV2, 95);  // Contrôle de vitesse via PWM

  analogWrite(GAR1, LOW);
  analogWrite(GAR2, vitesseMoteurTourne);  // Contrôle de vitesse via PWM
  analogWrite(DAR1, vitesseMoteurTourne);  // Contrôle de vitesse via PWM
  analogWrite(DAR2, LOW);
}

void Arreter() {// Fonction pour arrêter
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
  // Serial.println(compteur);
  if (compteur == 5) {
    compteur = 0;
    Arriver = true;
  }
  //  delay(500);
}

void udpReceiveData() {
  memset(incomingPacket, 0, 50);

  int packetSize = udp.parsePacket();  // Vérifie si des données arrivent
  if (packetSize) { // Lire les données reçues
    int len = udp.read(incomingPacket, 50);
    if (len > 0) {
      incomingPacket[len] = '\0';  // Terminer la chaîne
    }
    if (strstr(incomingPacket, "Abort") != NULL) {
      ModeAbort = true;
      EnFonction = false;
    } else if (strstr(incomingPacket, "EnFonction") != NULL) {
      ModeAbort = false;
      EnFonction = true;
    } else if (strstr(incomingPacket, "BlocNoir") != NULL) {
    } else if (strstr(incomingPacket, "BlocOrange") != NULL) {
      ModeSuiveurOrange = true;
    } else if (strstr(incomingPacket, "BlocMetal") != NULL) {
      ModeSuiveurMetal = true;
    } else if (strstr(incomingPacket, "Suiveur") != NULL) {
      ModeSuiveur();
    } else if (strstr(incomingPacket, "Charger") != NULL) {

      Vehicule = true;
    } else if (strstr(incomingPacket, "Decharger") != NULL) {

      Vehicule = false;
    } else if (strstr(incomingPacket, "PoidsPeser") != NULL) {

      Poids = true;
    }
    ////////////////////////////////////////////////////////////////////Mode Manuel pour tester la communication et le contrôle du véhicule////////////////////////////////////////////////////////////////////////////////////////////
    else if (strstr(incomingPacket, "Manuel") != NULL) {
      ModeManuel = true;
    } else if ((strstr(incomingPacket, "Droite") != NULL) && (ModeManuel == true)) {
      tournerDroite();

    } else if ((strstr(incomingPacket, "Gauche") != NULL) && (ModeManuel == true)) {
      tournerGauche();

    } else if ((strstr(incomingPacket, "Avance") != NULL) && (ModeManuel == true)) {
      allerToutDroit();

    } else if ((strstr(incomingPacket, "Recule") != NULL) && (ModeManuel == true)) {
      ReculeLigneDroite();

    } else if ((strstr(incomingPacket, "Stop") != NULL) && (ModeManuel == true)) {
      Arreter();
    } else {
      Serial.println("Commande inconnue !");
    }
    Serial.printf("Message reçu : %s\n", incomingPacket);
  }
}

void udpSend() {
  udp.beginPacket(adresse, port);
  udp.print(compteur);
  udp.endPacket();
}
