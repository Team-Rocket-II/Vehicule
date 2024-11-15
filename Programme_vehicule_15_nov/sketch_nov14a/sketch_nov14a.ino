
#include <Wire.h>

// Définir l'adresse I2C du capteur de suivi de ligne (changer selon le capteur)
#define LINE_SENSOR_ADDR 0x3A  // Adresse I2C du capteur (à adapter selon votre capteur)

// Pins GPIO pour contrôler les moteurs ou autres actions
#define MOTOR_LEFT_PIN 14
#define MOTOR_RIGHT_PIN 15
#define MOTOR_LEFT_DIR_PIN 27
#define MOTOR_RIGHT_DIR_PIN 17

void setup() {
  // Initialiser la communication série pour le débogage
  Serial.begin(115200);

  // Initialiser le bus I2C
  Wire.begin(23, 22);  // SDA (23), SCL (22)



  
}



void loop() {
  uint8_t line_data = readLineSensor();  // Lire les données du capteur I2C

  // Afficher les données du capteur sur le moniteur série
  Serial.print("Données lues du capteur I2C : ");
  Serial.println(line_data, BIN);

  // Contrôler les moteurs en fonction des données lues
  controlMotors(line_data);

  delay(100);  // Petite pause pour éviter une boucle trop rapide
}

// Fonction pour lire les données du capteur de ligne via I2C
uint8_t readLineSensor() {
  Wire.beginTransmission(LINE_SENSOR_ADDR);  // Démarrer la communication avec le capteur
  Wire.write(0x00);  // Lire les données à partir du registre (à ajuster selon votre capteur)
  Wire.endTransmission();
  
  Wire.requestFrom(LINE_SENSOR_ADDR, 1);  // Demander 1 octet de données
  if (Wire.available()) {
    return Wire.read();  // Retourner l'octet des données lues
  }
  return 0;  // Si aucune donnée n'est lue, retourner 0
}


