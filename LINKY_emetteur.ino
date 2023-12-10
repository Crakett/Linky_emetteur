#include <SPI.h>
#include <RF24.h>

#define pinCE   9                     // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  10                    // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel  "LINKY"               // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre

RF24 radio(pinCE, pinCSN);            // Instanciation du NRF24L01

const byte adresse[6] = tunnel;       // Mise au format "byte array" du nom du tunnel

void setup() {
  delay(3000);
  Serial.begin(9600,SERIAL_7E1);
  radio.begin();                      // Initialisation du module NRF24
  radio.setDataRate(RF24_1MBPS);      // en remplaçant « xxx » par RF24_250KBPS, RF24_1MBPS, ou encore, RF24_2MBPS
  radio.setChannel(100);              // en remplaçant « x » par une valeur comprise entre 0 et 125
  radio.openWritingPipe(adresse);     // Ouverture du tunnel en ÉCRITURE, avec le "nom" qu'on lui a donné
  radio.setPALevel(RF24_PA_HIGH);     // en remplaçant « xxx » par RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, ou RF24_PA_MAX
  radio.stopListening();              // Arrêt de l'écoute du NRF24 (signifiant qu'on va émettre, et non recevoir, ici)
}

void loop()
{
  byte data[16];
  
  // Lit un message de 15 caractères depuis le port série
  int len = Serial.readBytes((byte*)data, 15);
  if (!len) {
    return;     // Pas de message
  }
  data[len] = '\0'; // Ferme la chaine de caractères
  radio.write(&data, sizeof(data));     // Envoi de notre message
}