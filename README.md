# Linky_emetteur
émetteur 2.4 ghz pour compteur linky

Ce projet permet de relier la sortie TIC d'un compteur linky sur son système domotique, sans fil.
La transmission radio s'effectue avec des modules eByte E01 2G4M13S (NRF24L01).
L'émetteur est alimenté par le LINKY, il n'a donc pas besoin d'alimentation externe.

Principe de fonctionnement de l'émetteur :
Les octets reçus sur le port série de l'arduino pro mini sont mis en buffer de taille max 15 octets.
Ce buffer est ensuite transmis au module radio.

Voir aussi le projet Linky_recepteur.