# U09 — Analyse statique de sécurité (SAST)

Ce laboratoire accompagne le cahier étudiant **U09 — Bonnes pratiques & SAST**. Il réutilise des exemples Python des unités U07/U08 et des exemples C des unités mémoire. Les analyses se déroulent dans un conteneur Docker isolé, sans réseau.

## Prérequis

- Ubuntu 24.04 avec Docker et le plugin Docker Compose.
- Se placer dans `U09-sast/labs/lab01-static-analysis`, là où se trouvent `Dockerfile` et `compose.yaml`.
- Les fichiers `src/web/app.py`, `src/web/app_fixed.py`, `src/heap/*.c` et `rules/u09-python.yaml` doivent être présents.

## Démarrage

Sur la machine Ubuntu (hors conteneur) :

```bash
export LAB_UID=$(id -u)
export LAB_GID=$(id -g)
docker compose build
docker compose run --rm lab bash
```

Dans le conteneur, les sources sont montées dans `/workspace` ; l'utilisateur prend l'UID/GID de l'hôte afin de pouvoir écrire dans le dossier partagé.

Versions validées : **Bandit 1.9.4**, **Cppcheck 2.13.0**, **Semgrep 1.180.0**, Python 3.12.3. Une nouvelle reconstruction sans versions épinglées peut installer d'autres versions : vérifier les résultats avant diffusion.

## Lab 9.1 — Bandit : application Python

```bash
cd /workspace
bandit src/web/app.py
bandit src/web/app_fixed.py
```

Observations validées :

- `app.py` : **B602** (High / High) sur `shell=True`, **B608** (Medium / Low) sur la requête SQL construite dynamiquement, et **B404** (Low / High) pour l'import `subprocess`.
- `app_fixed.py` : **B404**, **B607**, **B603**, toutes de sévérité Low ; **aucune alerte Medium ou High**.

La confiance Low de B608 ne signifie pas que la vulnérabilité est inexistante : confronter le diagnostic au code.

## Lab 9.2 — Cppcheck : erreurs mémoire en C

```bash
cd /workspace
cppcheck --enable=warning,style \
  src/heap/double_free.c \
  src/heap/uaf.c \
  src/heap/heap_of.c \
  src/heap/uninit.c
```

Observations validées :

- `double_free.c:8` : **doubleFree**.
- `heap_of.c:7` : **bufferAccessOutOfBounds**.
- Aucune alerte pour `uaf.c` et `uninit.c` avec ces options dans l'environnement testé. **L'absence d'alerte ne démontre pas l'absence de vulnérabilité.**

Pour confirmer dynamiquement les défauts mémoire, réutiliser les exercices de sanitizers des unités précédentes, dans leurs environnements respectifs.

## Lab 9.3 — Audit combiné

Choisir un des codes fournis, effectuer une revue du code, exécuter les outils adaptés et produire un rapport argumenté. Pour les exemples Python :

```bash
cd /workspace
bandit src/web/app.py
semgrep scan --config rules/u09-python.yaml src/web/app.py
semgrep scan --config rules/u09-python.yaml src/web/app_fixed.py
```

Les règles locales ont détecté **deux findings** sur `app.py` (construction SQL dynamique et `shell=True`) et **zéro** sur `app_fixed.py`. Elles sont **ciblées sur ces motifs pédagogiques** et ne constituent pas une analyse exhaustive.

**Ne pas utiliser** `semgrep --config auto` dans ce conteneur : `network_mode: none` empêche le téléchargement de règles. Le fichier `code.py` mentionné dans une ancienne version du cahier n'existe pas ; utiliser les fichiers de `src/`.

Pour la confirmation dynamique, reprendre les exercices correspondants des unités U05/U07/U08 ou U11, selon la vulnérabilité choisie. **Le conteneur U09 est destiné au SAST ; il n'exécute pas automatiquement les services web des autres unités.**

Le rapport étudiant doit comprendre : code et outil étudiés, finding et emplacement, CWE, sévérité et confiance (si disponibles), justification du tri, preuve dynamique si demandée, correctif proposé et résultat de la nouvelle analyse.

## Exporter les rapports

```bash
cd /workspace
mkdir -p /tmp/u09-reports

bandit -f json -o /tmp/u09-reports/bandit.json src/web/app.py

cppcheck --enable=warning,style --xml --xml-version=2 \
  src/heap/double_free.c src/heap/uaf.c \
  src/heap/heap_of.c src/heap/uninit.c \
  2> /tmp/u09-reports/cppcheck.xml

semgrep scan --config rules/u09-python.yaml --json \
  --output /tmp/u09-reports/semgrep.json src/web/app.py

ls -lh /tmp/u09-reports/
```

Ces trois exports ont été validés. Les fichiers dans `/tmp` sont **temporaires** et disparaissent à la suppression du conteneur ; pour les conserver, utiliser un répertoire accessible en écriture dans `/workspace` et ne pas versionner les rapports générés.

## Points d'attention

- Une commande d'analyse peut retourner un code non nul lorsqu'elle trouve des problèmes ; lire les diagnostics plutôt que de conclure à une panne.
- `cppcheck` peut retourner `0` malgré des findings si `--error-exitcode` n'est pas spécifié.
- Les résultats dépendent des versions et des règles activées.
- Ne pas confondre sévérité et confiance, ni « aucune détection » et « code sûr ».
- Les codes vulnérables sont fournis exclusivement à des fins pédagogiques dans un environnement isolé.

Quitter le conteneur avec `exit` ; depuis l'hôte, `docker compose run --rm lab bash` crée un nouveau conteneur temporaire.
