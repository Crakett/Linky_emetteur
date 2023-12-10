#include <SPI.h>
#include <RF24.h>

#define pinCE   9             // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  10             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel  "LINKY"       // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre

RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

const byte adresse[6] = tunnel;               // Mise au format "byte array" du nom du tunnel
const char message[] = "1234567890\n";     // Message à transmettre à l'autre NRF24 (32 caractères maxi, avec cette librairie)

void setup() {
  delay(3000);
  Serial.begin(9600,SERIAL_7E1);
  radio.begin();                      // Initialisation du module NRF24
  radio.setDataRate(RF24_1MBPS);    // en remplaçant « xxx » par RF24_250KBPS, RF24_1MBPS, ou encore, RF24_2MBPS
  radio.setChannel(100);              // en remplaçant « x » par une valeur comprise entre 0 et 125
  radio.openWritingPipe(adresse);     // Ouverture du tunnel en ÉCRITURE, avec le "nom" qu'on lui a donné
  radio.setPALevel(RF24_PA_LOW);      // en remplaçant « xxx » par RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, ou RF24_PA_MAX
  radio.stopListening();              // Arrêt de l'écoute du NRF24 (signifiant qu'on va émettre, et non recevoir, ici)
  Serial.println("OK !");
}

void loop()
{
//byte in;
  
 // if (Serial.available()>0)
 // {
 //   in = Serial.read();  
 //   radio.write(&in, 1);     // Envoi de notre message
 // }

  byte data[16];
  
  // Lit un message de maximum 32 caractères depuis le port série
  int len = Serial.readBytes((byte*)data, 15);
  if (!len) {
    return; // Pas de message
  }
  data[len] = '\0'; // Ferme la chaine de caractères
  radio.write(&data, sizeof(data));     // Envoi de notre message

/*
  unsigned long myTime = micros();
  radio.write(&message, sizeof(message));     // Envoi de notre message  
  unsigned long myTime2 = micros();
  Serial.println(myTime2-myTime);
  delay(500);
*/

  
}
