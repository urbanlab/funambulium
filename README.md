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
      * 1 PC pour la captation Kinect (*Zotac standard*)
      * 1 PC Type PC de VR (*Fractal VR Ready*)
* 2 VP (voire 3 pour les ombres portées)
* 2 zones de projections (mur frontal + sol)
* 1 Ipad avec TouchOSC
* Technologie Augmenta et Augmenta Fusion

## Setup / Démarrage
### Procédure manuelle de démarrage 
1. Allumer VP Smartsign + VP derrière la paroi frontale
1. Allumer Smartsign en monitoring (192.168.71.58) > pour vérifier le bon allumage, lumière rouge sur la kinect
1. Allumer PC d'affichage en haut de la structure
1. Démarrer AugmentaFusion sur le Mac mini
      1. Dans AugmentaFusion, aller dans File -> Open Recent File ("Funambulum.fusion")
      1. Dans AugmentaFusion, aller dans Panels > Layout > _lastSession
1. : Avec la souris du PC d'affichage, lancer le programme via le raccourci desktop "Funambulium"
    1. S'assurer que l'ont soit en plein écran (en cliquant sur l'icône Expand de la fenêtre)
    1. Avec le clavier du PC d'affichage, entrer "d" (debug), puis "shift+w", puis à nouveau "d" : le mapping devrait être calé
1. Lancer TouchOSC sur l'iPad blanc du lab
     1. Vérifier que l'IP dans TouchOSC soit 192.168.71.200 et que "Layout" soit Funambulium

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

### MAPPING AUGMENTA sur le Mac Mini (via PC Smartsign)
* Ouvrir AugmentaFusion sur le Mac Mini
* Avec l'iPad appuyer sur Start/Stop dans TouchOSC, puis appuyer sur Next jusqu'à aller dans le scénario avec les poissons et flamands roses
* Demander à une personne de se positionner sur le cercle de départ
* Déplacer la croix rouge dans **Merger** pour faire correspondre la position du joueur avec la détection
* Au besoin, maintenir Shift pour faire tourner la croix rouge

## Réinstallation
* Télécharger et installer openframeworks à partir du site officiel: http://openframeworks.cc/download/
    * Version 0.9.8 uniquement (celle-ci n'est compatible qu'avec ubuntu antérieurs à 16.04) : https://openframeworks.cc/download/older/
    * Pour l'installation, suivre les instructions ici [https://openframeworks.cc/setup/linux-install/]
    * Cette installation commence par lors du déroulement du script
    ```
    cd OF/scripts/linux/ubuntu
    sudo ./install_dependencies.sh
    ```
    * Quand apparaît la question sur les packages spécifiques 16.04, répondre non
    * compiler OpenFrameworks
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
* Télécharger ou cloner l'archive github du projet funambulus : https://github.com/urbanlab/funambulium
* Vérifier que dans le dossier de openframeworks (généralement nommé of_v0.9.8_linux64_release) on trouve bien le fichier suivant: apps/urbanlab/funambulus. Où funambulus est l'archive téléchargée depuis le git.
* Décompresser l'archive "pourInstallation" contenue dans le dépôt git de funambulus
* Remplacer le dossier "addons" d'openframeworks par les fichiers addons1 et addons2 décompressés (ensembles, pour que le contenu des deux soit directement dans "addons")
* Meme manipulation avec le dossier "data" contenu dans app/urbanlab/funambulus/bin (il faut que dans ce dossier "data" se trouvent ensembles le contenu des archives data1 à data5)
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
