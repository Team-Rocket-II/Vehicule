
#define PCF8574_INITIAL_VALUE       0x7F

#include "PCF8574.h"



PCF8574 PCF_01(0x22);

void setup() {
  Serial.begin(115200);

  Wire.begin();
  PCF_01.begin();
  

  //uint8_t line_data = readLineSensor();  // Lire les données du capteur I2C
  //Serial.print("Données lues du capteur I2C : ");
  //Serial.println(line_data, BIN);
    //PCF_01.write(0, LOW);

}
 
void loop() {

  int x = PCF_01.read8();
  Serial.print("Read ");
  Serial.println(x, HEX);
  delay(100);
      
}

// uint8_t readLineSensor() {
//   Wire.beginTransmission(LINE_SENSOR_ADDR_READ);  // Démarrer la communication avec le capteur
//   Wire.write(0x00);  // Lire les données à partir du registre (à ajuster selon votre capteur)
//   Wire.endTransmission();
  
//   Wire.requestFrom(LINE_SENSOR_ADDR_READ, 1);  // Demander 1 octet de données
//   if (Wire.available()) {
//     return Wire.read();  // Retourner l'octet des données lues
//   }
//   return 0;  // Si aucune donnée n'est lue, retourner 0
// }

