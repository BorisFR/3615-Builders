#pragma once
#ifndef MY_CONFIG_HPP
#define MY_CONFIG_HPP

// pour avoir des infos sur la console série de debug
// mettre en commentaire pour la production
#define DEBUG

// définir le port série sur lequel vous avez branché le Minitel
#define SERIAL_MINITEL Serial5
//#define PIN_MINITEL_SERIAL_TX 34
//#define PIN_MINITEL_SERIAL_RX 33

// le code secret a saisir sur l'écran d'accueil
// pour accéder à l'écran de configuration
#define SECRETCODE "boris"

// normalement, pas besoin de toucher en dessous

#define CATEGORY_CINEMA "Cinéma"
#define CATEGORY_DROIDE "Droïde"
#define CATEGORY_KNOWLEDGE "Connaissance"
#define CATEGORY_HISTORY "Histoire"

#define HUMAN_MOTTO "Star Wars, ça vous cause ?"
#define SENSITIF_MOTTO "Vous êtes sensible à la Force, continuez votre découverte."
#define INITIE_MOTTO "La Force est en vous, découvrez vos possibilités."
#define PADAWAN_MOTTO "La Force vous guide, approfondissez vos connaissances."
#define CHEVALIER_MOTTO "Votre sagesse vous honore, partagez votre savoir."
#define MASTER_MOTTO "Votre maîtrise de la Force est exemplaire !"

#define MONDAY "lundi"
#define TUESDAY "mardi"
#define WEDNESDAY "mercredi"
#define THURSDAY "jeudi"
#define FRIDAY "vendredi"
#define SATURDAY "samedi"
#define SUNDAY "dimanche"

#define JANUARY "janvier"
#define FEBRUARY "février"
#define MARCH "mars"
#define APRIL "avril"
#define MAY "mai"
#define JUNE "juin"
#define JULY "juillet"
#define AUGUST "août"
#define SEPTEMBER "septembre"
#define OCTOBER "octobre"
#define NOVEMBER "novembre"
#define DECEMBER "décembre"

enum PlayerStatus
{
	Human,
	Sensitif,
	Initie,
	Padawan,
	Chevalier,
	GrandMaitre
};

// combien de questions pour une session de jeu
#define MAX_QUESTIONS_PER_GAME 10

// combien de bonnes réponses successives pour passer au niveau supérieur
#define GOOD_ANSWER_TO_LEVEL_UP 3

#define BAD_ANSWER_TO_LEVEL_DOWN 2

// temps limite pour répondre
#define SECONDS_TO_ANSWER 30 * 1000

// nombre de joueurs au classement
#define MAX_SCORES 18
#define MAX_PODIUM_PLAYER 10

// http://www.qrcode.com/en/about/version.html
// Nom du joueur : 14
// Score : 3
// date + heure : xx/xx/xxxx 10 + xx:xx:xx 8 = 18
// soit un total de 35 caractères

// minitel = 80 x 24
// soit en graphique = 160 x 72

// soit au max, un QRcode de 72x72...
// niveau d'erreur max
// et 35 caractères
// = version 3 en High (58 caractères)
// soit un QRcode de 29 x 29

#define QR_CODE_VERSION 3
#define QR_CODE_ERROR ECC_HIGH
#define QR_CODE_SIZE 29

#endif