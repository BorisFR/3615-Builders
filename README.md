# 3615 Builders

Le Q.C.M. des [R2-Builders](https://r2builders.fr) sur l'univers Star Wars !
Les données du QCM ont été entiérement réalisées par la communauté des Builders. Au 6/2/2018, nous en sommes à un peu plus de 250 questions réparties en 4 catégories.

## Détails

Ce jeu est fait pour fonctionner avec un ... Minitel !

Au démarrage, le jeu alterne antre un écran de présentation et le tableau des scores.
Dès qu'une touche du Minitel est appuyée, un écran de saisie du nom de joueur est affiché. On enchaine alors sur le choix du niveau de difficulté pour commencer le jeu.
Le jeu démarre alors et enchaîne la succession de questions.
Une fois terminé, le résultat est affiché, avec un calcul de points fonction du niveaux des questions et du délai de réponse. Le tableau des scores est ensuite affiché et le jeu attend un nouveau joueur.

Le niveau de difficulté évolue automatiquement pendant le jeu. Si le joueur enchaîne les bonnes réponses, le niveau augmente. Au contraire, s'il enchaîne les mauvaises réponses, le niveau diminue.
Il y a un temps maximum pour répondre à chaque question : 30 secondes.

## Technique

### Le coeur du moteur

La version actuelle est faire pour un [Teensy 3.5](https://www.pjrc.com/store/teensy35.html). Pourquoi ce choix ? 

- Car il tolère le 5V nécessaire pour causer en série avec le Minitel. On peut contourner cette problématique par un level shifter.
- Car il possède assez de mémoire pour contenir le QCM en mémoire. Il serait possible de charger dynamiquement les infos sur les questions depuis une carte SD.
- Car il a un RTC (Real Time Clock) intégré. On pourrait combler le manque par un DS1307 en I2C par exemple.

Le développement est réalisé en C++. J'utilise PlatformIO dans Visual Studio Code. Cependant j'ai fait en sorte que le projet soit directement utilisable dans l'IDE Arduino.

### Branchements

Une pile 3V connectée sur VBat et GND : rangée du milieu du Teensy. Cela permet de sauvegarder la date et l'heure.

Le port Série 5 (pin 33 & 34) connectée au Minitel. C'est configurable dans le fichier MyConfig.hpp.

Une carte SD est nécessaire pour la sauvegarde des données de jeu. Elle n'est cependant pas obligatoire.

### Minitel

Il faut dé-activer l'écho. Si vous ne le faites pas, lors de la saisie du nom de joueur, les caractères seront affichés deux fois à l'écran. Et tout appui sur le clavier apparaîtra également. Pour cela il faut faire la manipulation "Fnct T" E

De même, pour gagner en rapidité d'affichage, il faut faire "Fnct P" 4

C'est à faire à chaque allumage du Minitel !

### Complément

L'ensemble des questions posées ainsi que les réponses données par les joueurs est sauvegardé. Le but est d'analyser à postériori ces résultats pour affiner le niveau de difficultés des réponses. Si une même question a toujours une réponse qui est bonne, son niveau de difficulté doit être faible et sera donc baissé si ça n'est pas le cas. A contrario, si une question a toujours des réponses fausses, cela veut dire qu'elle est d'un niveau de difficulté supérieure.
Cela sera cependant effectué plus tard. Une version ultérieure pourra adapter ce niveau dynamiquement.

### Library

Voici les bibliothèques Arduino utilisées par le programme :  
[QRcode](https://github.com/ricmoo/qrcode/) : permet de créer un QRcode  
[Minitel1B_Hard](https://github.com/eserandour/Minitel1B_Hard) : permet la gestion du Minitel depuis un port Série  
[ElapsedMillis](https://github.com/pfeerick/elapsedMillis/) : pour la gestion du time out  

Pour le design de mes pages Minitel, j'ai utilisé le logiciel de création de page Minitel réalisé par Zigazou : [miedit](https://github.com/Zigazou/miedit)  