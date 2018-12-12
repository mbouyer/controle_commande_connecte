# controle_commande_connecte
Une interface controle-commande pilotable par wifi


Le but du projet est de réaliser une interface de commande et contrôle
d'un équipement électrique, avec arrêt automatique lorsque une valeur de
consigne est atteinte, et surveillance à distance par wifi.

L'interface utilisateur est consituée de quatre bouttons poussoir (marche,
arrêt, définition de la consigne par +/-) et un écran LCD pour l'affichage.

Le capteur peut-être un capteur de température (résistance CTN), ou un
capteur de pression avec sortie différentielle.

Le matériel dispose également d'un transormateur de courant permettant de
mesurer l'intensité consomée par la charge. La charge est pilotée à travers
un relais.

* un microchip pic18f25q10,
  auquel sont connectés les capteurs de température et de courant,
  aunsi que les 4 interrupteurs
* un module ESP8266, qui commandera l'affichage et contient un module
  wifi.

Le relais peut être commandé par l'un ou l'autre microcontrolleur.
Les deux microcontrolleurs communiquent par un bus i2c et une GPIO.
