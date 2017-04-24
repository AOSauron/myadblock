# myAdBlock
Bloqueur de publicités par proxy - Projet de RSA Réseaux TELECOM Nancy 2017

## Auteurs
 - DUGUE Clément
 - GARCIA Guillaume

## Dépendances
 - gcc
 - glibc

## Build
 - `make main`

## Execute
 - `./MyAdBlock [NUMERO_PORT]`

## Exemples d'utilisations
### Utiliser le proxy sur son pc, sur Mozilla Firefox :
 - Lancez dans un terminal `./MyAdBlock 7777`
 - Dans Firefox, allez dans le 'Menu' -> 'Préférences' -> 'Avancées' -> 'Réseaux' -> Bouton 'Paramètres' sous 'Connexion'
 - Séléctionnez 'Configuration manuelle du proxy'
 - Dans 'HTTP Proxy', rentrez `127.0.0.1`
 - Juste à droite, dans 'Port', rentrez `7777`
 - /!\\ Il est impératif que le numéro de port soit identique aux numéro de port renseigné à l'exécution de MyAdBlock.
 - Surfez librement sur le net !

## Travail d'analyse et wireshark
  Le travail d'analyse des différentes étapes du projets est présenté dans le rapport au format pdf. Certaines réponses et analyses, notamment avec wireshark sont présentes dans le dossier `questions/`, ainsi que certaines images explicatives (wireshark) dans le dossier `images/`.
