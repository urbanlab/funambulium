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
les machines sont connectées en WiFi le réseau erasme-dmz et ont les adresses suivantes :
* PC de captation Augmenta : 192.168.61.129
* PC d'affichage Mapping : 192.168.61.120

#### Ports OSC attendus
PC augmenta -> PC d'affichage : 12000 *(à vérifier ou paramétrer sur le monitoring Augmenta)* 

Tablette iPad / TouchOSC -> PC d'affichage : 12011 *(à vérifier ou paramétrer dans Touch OSC)*

Ces informations (adresses et ports) sont nécessaires pour les paramétrages suivants :
* renseigner l'adresse IP, et le port du PC d'affichage sur Augmenta
* renseigner l'adresse IP, et le port du PC d'affichage sur TouchOSC (Tablette)
* en tapant l'adresse IP du PC Augmenta dans un navigateur, vous pourrez monitorer et paramétrer la captation

**Changer les adresses IP aprés branchement des PC sur le réseau filaire**

### Mapping sur le PC d'affichage (Fractl VR Ready)
* Appuyer sur Shift+W (mode wrapping)
* Appuyer sur D (DEBUG), un contour rouge apparait
* Identifier sur quel écran on fait le mapping (un écran à la fois)
* Pour plus de précisions, sélectionner les ancres au clavier avec les touches 1 , 2 , 3 , 4 (pour retirer l'affichage du menu : Espace)
* Positionner les ancres au clavier avec les flèches

#### Raccourcis clavier
* Pour sauvegarder : Esc
* Pour mettre en plein écran : f
* Pour sortir du mode Wrapping : Shift+W (ne pas sortir pour garder le mapping)
* Pour changer d'écran de travail : w
* Pour sortir/entrer du mode Debug : d
* Pour afficher/cacher les menus du mode debug : Espace

## Réinstallation
### PC d'affichage
#### Réinstallation complète (pour recompilation)

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
* Télécharger ou cloner l'archive github du projet funambulus : https://github.com/urbanlab/funambulium . Cette archive contient 
  * le code source *(dossier src)*
  * les addons *(dossier pour installation, fichiers addons_xxx.zip)*
  * les app compilées *(dossier bin)*
* Décompresser l'archive *pour installation/data.zip* dans le dossier *0F_0.9.8/apps/funambulium/bin/data*
* les app compilées doivent suffire à démarrer le projet. 
  * Double-cliquer sur *funambulium-xxxx* pour démarrer l'installation
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
* Penser à corriger l'ip dans le fichier ip.txt qui est dans la dossier data. C'est l'adresse d'envoi des paquets OSC depuis le dispositif. (*Feature à priori obsoléte*)

#### Réinstallation partielle (lancement)
voir réinstallation complète
* Télécharger et installer OpenFrameworks
* Télécharger ou cloner l'archive github du projet funambulus
* Décompresser les datas dans le dossier *bin/data*
* Décompresser les addons dans le dossier *OF_0.9.8/addons*
* Pas besoin de compilation, vous pouvez lancer directement l'application *funambulium-ubuntu*

### Réinstallation PC Augmenta
**Pas de procédure connue de réinstallation d'Augmenta**
**Contactez [Theoriz](https://www.theoriz.com) pour plus d'informations**

## Bugs connus
* Dans Augmenta, toujours saisir une adresse IP de destination des paquets OSC valide
       * Dans l'onglet Output, les champs IP et Port doivent correspondre à une machine sur le réseau
       * Saisir et appuyer sur **Add**
       * L'adresse IP apparait alors dans le cadre **Global information** dans le champ **Output**
* Parfois la connexion à Augmenta Fusion ne se fait pas. Il faut le reconnecter manuellement -> voir étape 4.1 de la procédure d'allumage
* Risque de plantage de la machine (redémarrage sauvage de la session) lors des branchements physiques des câbles HDMI. Installer et activer les pilotes NVIDIA de la carte graphique de la machine où lancer le dispositif.
* Problèmes d'édition du projet via QT Creator, plus globalement le project creator d'openframeworks n'est pas opérationnel dans cette configuration : https://forum.openframeworks.cc/t/of-0-9-8-qt-creator-projects-not-compiling/33777
