#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "Team_Rocket_II";
const char* password = "Elisabeth_II";
const int udpPort = 22222;

WiFiUDP udp;
char incomingPacket[255];  // Pour stocker les paquets reçus


bool FonctionFlag = true;
bool BlocOrangeFlag = false;
bool MouvementFlag = false;


// Configuration IP statique pour le serveur
IPAddress local_IP(192,168,15,2);
IPAddress gateway(192,168,15,1);  // Gateway (facultatif)
IPAddress subnet(255, 255, 255, 0);  // Masque de sous-réseau

// Buffers pour la gestion de la trame série
#define MAX_DATA_LENGTH 255
uint8_t serialBuffer[MAX_DATA_LENGTH];
uint8_t checksum = 0;
uint8_t checksumReceived = 0;
int dataLength = 0;
int dataIndex  = 0;
bool receiving = false;


void sendDataOverUART(const char* data, int length) {
  uint8_t checksum = 0;

  // Étape 1 : Envoyer le préfixe `$`
  Serial2.write('$');

  // Étape 2 : Envoyer la longueur des données (inclut 0x34 comme premier byte de données)
  uint8_t totalLength = length + 1; // +1 pour inclure `0x34`
  Serial2.write(totalLength);

  // Étape 3 : Envoyer le byte fixe `0x34` comme premier byte de données
  Serial2.write(0x34);
  checksum += 0x34; // Ajouter `0x34` au checksum

  // Étape 4 : Envoyer les données, en échappant `$` si nécessaire
  for (int i = 0; i < length; i++) {
    if (data[i] == '$') {
      Serial2.write('$');  // Échapper le caractère `$`
      Serial2.write(0x00); // Ajouter 0x00 après `$`
      checksum += '$' + 0x00;
    } else {
      Serial2.write(data[i]);
      checksum += data[i];
    }
  }

  // Étape 5 : Envoyer le checksum (somme de tous les bytes de données)
  Serial2.write(checksum);
}

void setup() {
  Serial.begin(115200);
   Serial2.begin(9600, SERIAL_8N1, 16, 17); // UART pour TX sur la pin 17

  // Configurer le mode point d'accès avec une IP statique
  if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
    Serial.println("Échec de la configuration IP !");
    return;
  }
  // Configurer le mode point d'accès
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Point d'accès configuré. IP: ");
  Serial.println(IP);

  // Démarrer le serveur UDP
  udp.begin(udpPort);
  Serial.printf("Serveur UDP en écoute sur le port %d\n", udpPort);

  
  
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) 
  {
    // Lire les données entrantes
    int len = udp.read(incomingPacket, 255);

    if (len > 0) 
    {
      incomingPacket[len] = 0;  // Terminer la chaîne
    }
      //Serial.printf("Reçu depuis %s, port %d : %s\n", udp.remoteIP().toString().c_str(), udp.remotePort(), incomingPacket);
      sendDataOverUART(incomingPacket, len);
   
    
    
    // Répondre au client
    if(FonctionFlag == true){
       udp.beginPacket(udp.remoteIP(), udp.remotePort());
       udp.printf("TestDemiTour");
       udp.endPacket(); 
       FonctionFlag = false;
       }

    // Lecture des données série
    while (Serial2.available()) {
      uint8_t byteReceived = Serial2.read();

      // Affichage de la réception des données série pour diagnostic
      Serial.printf("Donnée reçue : %02X\n", byteReceived);

      if (!receiving) {
        if (byteReceived == '$') {
          // Détection du début d'une nouvelle trame
          receiving = true;
          dataIndex = 0;
          checksum = 0;
          Serial.println("Début de la nouvelle trame");
        }
      } else {
        if (dataIndex == 0) {
          // Lire la longueur des données
          dataLength = byteReceived;
          Serial.printf("Longueur des données : %d\n", dataLength);
          dataIndex++;
        } else if (dataIndex <= dataLength) {
          // Lire les données
          if (byteReceived == '$') {
            // Si un $ est reçu, attendre 0x00
            byteReceived = Serial2.read();
            if (byteReceived == 0x00) {
              checksum += '$' + 0x00;
              dataIndex++;
              Serial.println("Échappement de '$' suivi de 0x00");
            } else {
              // Si ce n'est pas 0x00, ignorer la trame
              receiving = false;
              Serial.println("Trame invalide, retour à l'état initial.");
              return;
            }
          } else {
            // Ajouter les données au buffer et au checksum
            serialBuffer[dataIndex - 1] = byteReceived;
            checksum += byteReceived;
            Serial.printf("Donnée reçue : %02X, checksum calculé : %02X\n", byteReceived, checksum);
            dataIndex++;
          }
        } else if (dataIndex == dataLength + 1) {
          // Vérification du checksum
          
          checksumReceived = byteReceived;
          Serial.printf("Checksum reçu : %02X, checksum calculé : %02X\n", checksumReceived, checksum);

          if (checksumReceived == checksum) {
            // Si le checksum est valide, envoyer les données sur UDP
            Serial.println("Trame valide, envoi via UDP.");
            udp.beginPacket(udp.remoteIP(), udp.remotePort());
            udp.write(serialBuffer, dataLength);
            udp.endPacket();
          } else {
            // Si le checksum est incorrect, ignorer la trame
            Serial.println("Checksum invalide !");
            Serial.printf("Reçu: %02X, Calculé: %02X\n", checksumReceived, checksum);
          }
          receiving = false;
        }
      }
    }
  
  
       
    // if(FonctionFlag == true){
    //    udp.beginPacket(udp.remoteIP(), udp.remotePort());
    //    udp.printf("EnFonction");
    //    BlocOrangeFlag = true;
    //    FonctionFlag = false;
    //   udp.endPacket();
    //}
    // if(BlocOrangeFlag == true){
    //   udp.beginPacket(udp.remoteIP(), udp.remotePort());
    //   udp.printf("BlocOrange");
    //   BlocOrangeFlag = false;
    //    udp.endPacket();
    //   //  MouvementFlag = true;
    //  }
    //if(MouvementFlag == true)
    // {
    //   Serial.printf("Reçu depuis %s, port %d : %s\n", udp.remoteIP().toString().c_str(), udp.remotePort(), incomingPacket);
    // }
    // if(strstr(incomingPacket, "TRI") != NULL){
    // udp.beginPacket(udp.remoteIP(), udp.remotePort());
    // udp.printf("Charger");
    // udp.endPacket();
    // }else if(strstr(incomingPacket, "PESAGE") != NULL){
    // udp.beginPacket(udp.remoteIP(), udp.remotePort());
    // udp.printf("Decharger");
    // udp.endPacket();
    // }

   
    //udp.endPacket();
  }
}
