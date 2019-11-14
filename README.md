# funambulus
## Description du projet

Les enfants atteints d’une malformation du vestibule sont sujets à des problèmes d’équilibre, d’audition et de vue. L’encadrement médical s’organise en deux domaines : le diagnostic et la rééducation. Funambulium est conçu comme un outil thérapeutique au service de la kinésithérapie rééducatrice. Elle immerge l'enfant dans des univers interactif afin d'être à la fois un moyen de garder l'attention de l'enfant à travers un gameplay qui sert la rééducation et stimule l’imaginaire de l'enfant, et un espace de travail pour les kinésithérapeutes que l'on peut moduler et complexifier en fonction des exercices à effectuer.

### Scénario / Mode d'emploi
La télécommande du projet est l'Ipad blanc. 

Pour **commencer**, appuyer sur *START*.
Pour **suivant**, appuyer sur le bouton *NEXT*.  
Pour **éteindre**, appuyer sur *START* (bouton toggle).
Pour **bouger le sol**, appuyer sur *RotX* ou *RotY* ou *RotZ* puis utiliser les *Slider* pour paramétrer l'intensité et la vitesse


- La narration est linéaire et se déroule étapes par étapes sans possibilités de revenir en arrière.

- **Chapitre 1** (*lever du jour*) : unlock -> aller de la première "cellule" à la deuxième.
- **Chapitre 2** (*forêt*) : Le but est de découvrir le chemin en dessous des feuilles, qui se trouve à gauche de la première cellule. **But** étant de faire prendre de l'initiative à l'enfant en se mettant "en danger".  **PS** ce scénario est LE PLUS CONCLUANT lorsque l'on décide de faire bouger le sol.
- **Chapitre 3** (*poisson*) : Mettre les modules sur le lac et faire traverser ces obstacles de la première à la deuxième cellule. **Suite** : Se tenir sur un pied sur la deuxième cellule face à l'écran le plus immobile possible.
- **Chapitre 4** (*découverte*) : pareil que le premier chapitre -> première cellule à la deuxième.

## Matériel
* 2 machines sous Ubuntu
  * 1 PC pour la captation Kinect / Augmenta (*Zotac standard*)
  * 1 PC Type PC de VR (*Fractal VR Ready*)
* 2 VP (voire 3 pour les ombres portées)
* 2 zones de projections (mur frontal + sol)
* 1 Ipad avec TouchOSC
* Technologie Augmenta et Augmenta Fusion

## Setup / Démarrage
### Procédure manuelle de démarrage 
1. Allumer les 2 VP (au dessus de l'install + derrière l'écran)
1. Allumer PC de captation
  1. pour vérifier le bon allumage, lumière rouge sur la kinect
1. Allumer PC d'affichage en haut de la structure
1. Avec la souris du PC d'affichage, lancer le programme via le raccourci desktop "Funambulium" (démarrage auto)
    1. S'assurer que l'on soit en plein écran (en cliquant sur l'icône Expand de la fenêtre)
    1. Avec le clavier du PC d'affichage, entrer "d" (debug), puis "shift+w", puis à nouveau "d" : le mapping devrait être calé
1. Lancer TouchOSC sur l'iPad blanc du lab
     1. Vérifier que l'IP dans TouchOSC soit celui du PC d'affichage (*voir sections adresses IP*) 
     1. Vérifier que le "Layout" soit Funambulium
1. Pour vérifier qu'Augmenta fonctionne :
  1. Démarrer un explorateur web pour voir l'interface de monitoring
     1. Si vous etes sur le PC Augmenta, tapez 127.0.0.1 dans la barre d'adresse
     1. Si vous etes sur une autre machine, tapez l'adresse IP du PC augmenta dans la barre d'adresse
     
### Adresses IP
les machines sont branchées par câble sur le réseau erasme-dmz et ont les adresses suivantes :
* PC de captation Augmenta : xxx.xxx.xxx.xxx
* PC d'affichage Mapping : xxx.xxx.xxx.xxx
#### Ports OSC attendus
PC augmenta -> PC d'affichage : 12000 *(à vérifier ou paramétrer sur le monitoring Augmenta)* 
Tablette iPad / TouchOSC -> PC d'affichage : 12011 *(à vérifier ou paramétrer dans Touch OSC)*

### Mapping sur le PC d'affichage (Fractl VR Ready)
* Appuyer sur Shift+W (mode wrapping)
* Identifier sur quel écran on fait le mapping (un écran à la fois)
* Pour plus de précisions, sélectionner les ancres au clavier avec les touches 1 , 2 , 3 , 4 (pour retirer l'affichage du menu : Espace)
* Pour changer d'écran de travail : w
* Positionner les ancres aux bons endroits avec la souris
* Appuyer sur D (DEBUG), un contour rouge apparait
* Positionner les ancres au clavier avec les flèches

* Pour sauvegarder : Echap
* Pour sortir du mode Wrapping : Shift+W (ne pas sortir pour garder le mapping)
* Pour sortir du mode Debug : D

### MAPPING AUGMENTA sur le Mac Mini (Zotac)
* Ouvrir AugmentaFusion sur le Mac Mini
* Avec l'iPad appuyer sur Start/Stop dans TouchOSC, puis appuyer sur Next jusqu'à aller dans le scénario avec les poissons et flamands roses
* Demander à une personne de se positionner sur le cercle de départ
* Déplacer la croix rouge dans **Merger** pour faire correspondre la position du joueur avec la détection
* Au besoin, maintenir Shift pour faire tourner la croix rouge

## Réinstallation
### PC Augmenta
** Pas de procédure de réinstallation **

### PC d'affichage
* Télécharger et installer openframeworks à partir du site officiel: http://openframeworks.cc/download/
    * Version 0.9.8 uniquement (celle-ci n'est compatible qu'avec ubuntu antérieurs à 16.04) : https://openframeworks.cc/download/older/
    * Pour l'installation, suivre les instructions ici [https://openframeworks.cc/setup/linux-install/]
    * Cette installation commence par le déroulement de ce script
    ```
    cd OF/scripts/linux/ubuntu
    sudo ./install_dependencies.sh
    ```
    * Quand apparaît la question sur les packages spécifiques 16.04, répondre non
    * compiler OpenFrameworks avec ce script
    ```
    cd OF/scripts/linux
    ./compileOF.sh
    ```
    * Vérifier l'install d'OF en compilant et éxécutant un exemple
    ```
    cd OF/examples/graphics/polygonExample
    make
    make run
    ```
* De même installer ofxAugmenta et vérifier qu'un des exemples fonctionne bien: https://github.com/Theoriz/ofxAugmenta
* Télécharger ou cloner l'archive github du projet funambulus : https://github.com/urbanlab/funambulium . Cette archive contient 
  * le code source *(dossier src)*
  * les addons *(dossier pour installation, fichiers addons_xxx.zip)*
  * les app compilées *(dossier bin)*
* Décompresser l'archive *pour installation/data.zip* doit etre décompressé dans le dossier *0F_0.9.8/apps/funambulium/bin/data*
* les app compilées doivent suffire à démarrer le projet. 
  * Double-cliquer sur *funambulium-ubuntu* pour démarrer l'installation
* Pour les addons
  * certains sont déjà fournis dans le repo d'openframeworks; par sécurité, on peut les trouver dans *addons_fournis_par_OF.zip*
  * d'autres sont requis. Ils sont dans le fichier *addons_supplementaires_requis* et doivent être extraits dans *OF_0.9.8/addons*
* Voir les screenshots de la configuration présents dans pourInstallation sur le depot github pour une meilleur compréhension
* Compiler
```
cd OF/apps/urbanlab/funambulium
make
make run
```
* On pourra retravailler le projet à condition d'avoir installer QTCreator 4.1.0[https://download.qt.io/archive/qtcreator/4.1/4.1.0/]
* Penser à corriger l'ip dans le fichier ip.txt qui est dans la dossier data
* Penser à bien installer les pilotes de la carte graphique de la machine où lancer le dispositif

## Bugs connus
* Dans Augmenta, toujours saisir une adresse IP de destination des paquets OSC valide
       * Dans l'onglet Output, les champs IP et Port doivent correspondre à une machine sur le réseau
       * Saisir et appuyer sur **Add**
       * L'adresse IP apparait alors dans le cadre **Global information** dans le champ **Output**
* Parfois la connexion à Augmenta Fusion ne se fait pas. Il faut le reconnecter manuellement -> voir étape 4.1 de la procédure d'allumage
