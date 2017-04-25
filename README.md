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

### Comment utiliser *myAdBlock*
#### Utiliser le proxy sur son pc, sur Mozilla Firefox :
 - Lancez dans un terminal `./myAdBlock 7777`
 - Dans Firefox, allez dans le 'Menu' -> 'Préférences' -> 'Avancées' -> 'Réseaux' -> Bouton 'Paramètres' sous 'Connexion'
 - Séléctionnez 'Configuration manuelle du proxy'
 - Dans 'HTTP Proxy', rentrez `127.0.0.1`
 - Juste à droite, dans 'Port', rentrez `7777`
 - /!\\ Il est impératif que le numéro de port soit identique au numéro de port renseigné à l'exécution de MyAdBlock.
 - N'oubliez pas de cocher 'Utiliser ce serveur proxy pour tous les protocoles', pour que myAdBlock puisse filtrer les connexions **https**
 - Surfez librement sans publicité sur le net !

#### Utiliser le proxy sur son pc, sur Google Chrome :
 - Lancez dans un terminal `./myAdBlock 7777`
 - Dans un autre terminal, lancez `google-chrome --proxy-server="https=127.0.0.1:7777;http=127.0.0.1:7777"`
 - /!\\ Il est impératif que le numéro de port dans cette commande soit identique au numéro de port renseigné à l'exécution de MyAdBlock.
 - Cette solution fonctionne difficilement. Préférez l'utilisation de Firefox.
 - Surfez librement sans publicité sur le net !

### Travail d'analyse, wireshark et templates
  Le travail d'analyse des différentes étapes du projets est présenté dans le rapport léger au format pdf `rapportMyAdBlock.pdf`. Certaines images explicatives (wireshark) sont présentes dans le dossier `images/`.
  Les templates et autres modèles utilisés pour construire le serveur proxy (surtout pour la partie serveur, échanges clients-serveur) sont présents dans le dossier `templates/`.

### Principe d'exclusion des publicités
  Le code source de myAdBlock ainsi que la liste `MyAdListLight` des hosts de publicités sont dans le dossier `src/`. Libre à vous d'ajouter des hosts dans la liste. Cette liste est une version allégée et plus simple de la liste de [easylist.to](https://easylist.to/), qui constitue notre banque de base de hosts de publicités.
  Chaque connexion entrante est filtrée, parsée et comparée à cette liste. Si elle appartient à cette liste, cette connexion est simplement bloquée (il s'agit d'une publicité).
  Compte tenu du fait que notre liste est réduite et ne tient pas comtpe des expressions régulières de la liste originale, myAdBlock est donc moins efficace que AdBlock (utilisant la même banque), mais est beaucoup plus simple et léger; son principe de fonctionnement est donc facile à comprendre.

  Dans sa dernière version, myAdBlock est capable de filtrer des connexions **https** en plus des connexions **http**
