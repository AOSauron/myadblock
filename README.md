# myAdBlock

**myAdBlock - Bloqueur de publicités par serveur proxy pour Linux**

*Projet de RSA Réseaux TELECOM Nancy 2017*

### Auteurs
 - DUGUE Clément
 - GARCIA Guillaume

### Dépendances
 - gcc
 - glibc

### Build
 - `make main` ou `make`

### Execute
 - `./myAdBlock [NUMERO_PORT]`

### Exemples d'utilisations
#### Utiliser le proxy sur son pc, sur Mozilla Firefox :
 - Lancez dans un terminal `./myAdBlock 7777`
 - Dans Firefox, allez dans le 'Menu' -> 'Préférences' -> 'Avancées' -> 'Réseaux' -> Bouton 'Paramètres' sous 'Connexion'
 - Séléctionnez 'Configuration manuelle du proxy'
 - Dans 'HTTP Proxy', rentrez `127.0.0.1`
 - Juste à droite, dans 'Port', rentrez `7777`
 - /!\\ Il est impératif que le numéro de port soit identique aux numéro de port renseigné à l'exécution de MyAdBlock.
 - N'oubliez pas de cocher 'Utiliser ce serveur proxy pour tous les protocoles', pour que myAdBlock puisse filtrer les connexions **https**
 - Surfez librement sans publicité sur le net !

### Travail d'analyse et wireshark
  Le travail d'analyse des différentes étapes du projets est présenté dans le rapport au format pdf `rapportMyAdBlock.pdf`. Certaines réponses et analyses, notamment avec wireshark sont présentes dans le dossier `questions/`, ainsi que certaines images explicatives (wireshark) dans le dossier `images/`.

### Principe d'exclusion des publicités
  Le code source de myAdBlock ainsi que la liste `MyAdListLight` des hosts de publicités sont dans le dossier `src/`. Libre à vous d'ajouter des hosts dans la liste. Cette liste est une version allégée et plus simple de la liste de [easylist.to](https://easylist.to/), qui constitue notre banque de base de hosts de publicités.
  Chaque connexion entrante est filtrée, parsée et comparée à cette liste. Si elle appartient à cette liste, cette connexion est simplement bloquée (il s'agit d'une publicité).
  Compte tenu du fait que notre liste est réduite et ne tient pas comtpe des expressions régulières de la liste originale, myAdBlock est donc moins efficace que AdBlock (utilisant la même banque), mais est beaucoup plus simple et léger; son principe de fonctionnement est donc facil à comprendre.

  Dans sa dernière version, myAdBlock est capable de filtrer des connexions **https** en plus des connexions **http**
