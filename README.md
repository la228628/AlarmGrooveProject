# AlarmGrooveProject
Ce réveil utilise une API pour afficher les informations météo et utilise une carte SD pour jouer de la musique. Il est entièrement configurable via une télécommande infrarouge (IR), que interchangeable à tout moment. Les informations de connexion et les coordonnées géographiques sont transférées via l'application Alarm Groove App qui est codée en Java
Fonctionnalités
1. Affichage des informations météo

    Se connecte à l'API MeteoBlue pour afficher :
        La température actuelle
        Les conditions météorologiques (ex: ensoleillé, pluvieux, nuageux, etc.)
    Mise à jour régulière pour fournir les données les plus récentes.

2. Configuration via une télécommande IR

    Le réveil est configurable grâce à une télécommande infrarouge.
    Possibilité de changer les paramètres suivants :
        Heure de réveil
        Volume de l’alarme
        Choix de la musique
    Télécommande interchangeable : il est possible d'utiliser n’importe quelle télécommande IR compatible, configurable en appuyant sur le bouton du réveil

3. Réveil musical via carte SD

    Musiques personnalisées stockées sur une carte SD.
    Choix de la musique via la télécommande.
    Support de plusieurs formats audio (ex: MP3, WAV).

4. Fonctionnalités supplémentaires

    Écran OLED pour l'affichage de l’heure, des données météo et des informations sur la musique en cours de lecture.
    Synchronisation automatique de l'heure via un module RTC

5. Matériel utilisé

    Un microcontrôleur NodeMcu 32s
    Un écran OLED ILI 9341
    Module de télécommande infrarouge (IR)
    Lecteur DFP pour le stockage et la lecture de la musique
    Haut-parleur pour la sortie audio
    Un module RTC

6. Échange de données via une application
   Les informations de connexion et les coordonnées géographiques sont transmises par câble Usb c via l'application Alarm Groove App dont le repository se trouve à l'adresse suivante:
   https://github.com/la228628/AlarmGrooveJavaApp
8. Démonstration
   Une vidéo de démonstration est disponible à l'adresse suivante: 
   https://youtu.be/VicC3U1Sd58
