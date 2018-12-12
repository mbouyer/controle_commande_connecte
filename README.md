# controle_commande_connecte
Une interface controle-commande pilotable par wifi


Le but du projet est de r�aliser une interface de commande et contr�le
d'un �quipement �lectrique, avec arr�t automatique lorsque une valeur de
consigne est atteinte, et surveillance � distance par wifi.

L'interface utilisateur est consitu�e de quatre bouttons poussoir (marche,
arr�t, d�finition de la consigne par +/-) et un �cran LCD pour l'affichage.

Le capteur peut-�tre un capteur de temp�rature (r�sistance CTN), ou un
capteur de pression avec sortie diff�rentielle.

Le mat�riel dispose �galement d'un transormateur de courant permettant de
mesurer l'intensit� consom�e par la charge. La charge est pilot�e � travers
un relais.

* un microchip pic18f25q10,
  auquel sont connect�s les capteurs de temp�rature et de courant,
  aunsi que les 4 interrupteurs
* un module ESP8266, qui commandera l'affichage et contient un module
  wifi.

Le relais peut �tre command� par l'un ou l'autre microcontrolleur.
Les deux microcontrolleurs communiquent par un bus i2c et une GPIO.
