# U02 — Pile et sécurité mémoire

## Objectifs pédagogiques

Cette unité permet de comprendre l'organisation de la pile d'exécution en C et d'étudier les conséquences d'une copie non bornée dans un tampon mémoire.

À l'issue du laboratoire, l'étudiant doit pouvoir :

- Identifier les principales zones d'une trame de pile.
- Expliquer les conséquences d'un débordement de tampon.
- Observer la modification d'une variable adjacente.
- Comprendre le rôle de l'adresse de retour et du registre `EIP`.
- Analyser un détournement du flot d'exécution dans un environnement contrôlé.
- Expliquer les protections mémoire et proposer des corrections de code.

## 1. Environnement de laboratoire

Les manipulations s'effectuent **exclusivement dans une VM Ubuntu x86_64 dédiée aux laboratoires**, disposant de Docker Engine et de Docker Compose.

Les exercices utilisent des programmes C compilés en **x86 32 bits**, notamment avec l'option `gcc -m32`.

Consignes de sécurité :

- Créer un instantané de la VM avant la séance.
- Ne pas exécuter les programmes vulnérables directement sur l'ordinateur personnel.
- Ne pas utiliser Docker avec l'option `--privileged`.
- Ne pas désactiver les protections mémoire de l'ordinateur personnel.
- Effectuer tout éventuel réglage de l'ASLR uniquement dans la VM, sous la supervision de l'enseignant, puis restaurer sa configuration.

Une VM ARM64 n'est pas l'environnement de référence de cette unité.

## 2. Structure du laboratoire

Les fichiers d'exécution se trouvent dans :

`U02-stack-overflow/labs/lab01-stack/`

Structure attendue :

```text
lab01-stack/
├── Dockerfile
├── compose.yaml
├── README.md
├── scripts/
│   └── build.sh
├── src/
│   ├── stack0.c
│   ├── stack1.c
│   ├── stack2.c
│   ├── stack3.c
│   ├── stack4.c
│   ├── stack5.c
│   ├── shellcode.s
│   └── exploit_stack5.py
└── bin/                 # Généré à la compilation
```

Le répertoire `bin/` contient les exécutables compilés et n'a pas besoin d'être versionné.

## 3. Démarrage du laboratoire

Depuis la VM Ubuntu, ouvrir un terminal dans le dossier `lab01-stack`.

Construire l'image Docker :

```bash
docker compose build
```

Démarrer le laboratoire :

```bash
docker compose run --rm lab bash
```

Dans le conteneur, compiler les exercices :

```bash
bash scripts/build.sh
```

Vérifier les exécutables :

```bash
ls -l bin/
```

Les programmes `stack0`, `stack1`, `stack2`, `stack3`, `stack4` et `stack5` doivent être présents.

L'image utilisée par le laboratoire est `software-security-lab:latest`.

## 4. Parcours pédagogique

| Laboratoire | Sujet | Modalité |
|---|---|---|
| Lab 2.0 | Préparation de l'environnement, compilation et GDB | Préparation |
| Lab 2.1 — `stack0` | Observation de la pile et des variables locales | Guidé |
| Lab 2.2 — `stack1` | Débordement modifiant une variable adjacente | Guidé |
| Lab 2.3 — `stack2` | Atteindre une valeur cible en mémoire | Autonome |
| Lab 2.4 — `stack3` | Comprendre la modification de l'adresse de retour | Guidé |
| Lab 2.5 — `stack4` | Exécution contrôlée d'un shellcode x86 | Démonstration |
| Lab 2.6 — `stack5` | Détournement du flot via `jmp esp` | Approfondissement |

**Parcours principal :** Labs 2.0 à 2.4.

**Approfondissement :** Labs 2.5 et 2.6, selon le temps disponible et les consignes de l'enseignant.

## 5. Vérification fonctionnelle

Les commandes suivantes permettent de vérifier le comportement attendu des programmes après compilation.

### `stack0` — Observation

```bash
./bin/stack0
```

Résultat attendu :

```text
result = 6
```

### `stack1` — Modification d'une variable

```bash
./bin/stack1 "$(python3 -c 'print("A"*32+"BBBB")')"
```

Résultat attendu :

```text
value = 0x42424242
```

### `stack2` — Valeur cible

```bash
./bin/stack2 "$(python3 -c 'import sys; sys.stdout.buffer.write(b"A"*10+b"\xf7")')"
```

Le programme doit afficher :

```text
Condition atteinte
```

### `stack3` — Fonction et adresse de retour

Exécution normale :

```bash
./bin/stack3 Alice
```

Le programme doit afficher notamment :

```text
Bonjour Alice
```

L'étude du débordement et de l'adresse de retour est réalisée avec GDB, conformément aux consignes du laboratoire.

### `stack4` — Shellcode

```bash
printf 'echo SHELLCODE_OK\nexit\n' | ./bin/stack4
```

Résultat attendu :

```text
SHELLCODE_OK
```

Ce programme constitue une démonstration autonome de l'exécution d'un shellcode x86 dans l'environnement contrôlé.

### `stack5` — Exploitation avec `jmp esp`

```bash
python3 src/exploit_stack5.py
```

Le script doit afficher :

```text
STACK5_OK
```

Le script peut tenter d'utiliser un fichier core pour déterminer le décalage. Si celui-ci est indisponible, un mécanisme alternatif peut être utilisé. L'absence de fichier core ne signifie donc pas nécessairement un échec.

## 6. Niveaux d'accompagnement

**N1 — Observer**

Compiler et exécuter les programmes, repérer les variables locales, les registres et les zones mémoire.

**N2 — Expliquer**

Utiliser GDB, interpréter les adresses, mesurer les décalages et expliquer les conséquences d'une écriture hors limites.

**N3 — Approfondir**

Étudier le détournement du flot d'exécution, analyser les mécanismes de protection et proposer des corrections.

## 7. Protections mémoire et remédiation

Les exercices utilisent volontairement des programmes vulnérables et certaines options de compilation destinées à rendre leurs comportements observables.

Dans un logiciel réel, les mesures suivantes doivent être étudiées :

- Vérification des limites avant toute copie.
- Utilisation correcte des tailles de tampon.
- Protection de pile par canaris.
- Protection contre l'exécution de données (NX).
- Randomisation des adresses (ASLR).
- Exécutables indépendants de leur adresse de chargement (PIE).
- Tests automatisés et analyse du code.

**Les protections mémoire réduisent les possibilités d'exploitation, mais ne remplacent jamais la correction du code vulnérable.**

## 8. Cahier étudiant

Le document de référence pour les consignes détaillées, les manipulations GDB, les questions et les observations est :

[`supports/C_U2_Cahier_labo_etudiant.pdf`](supports/C_U2_Cahier_labo_etudiant.pdf)

Le cahier doit utiliser les mêmes noms de fichiers, tailles de tampons et résultats attendus que les sources du dépôt.

## 9. Remise et évaluation

Les observations, réponses et captures éventuelles sont consignées selon les consignes du cahier étudiant.

Les modalités de remise, le barème et les éventuels approfondissements évalués sont communiqués par l'enseignant.

## 10. Arrêt du laboratoire

Quitter le conteneur :

```bash
exit
```

Depuis la VM, dans le dossier du laboratoire :

```bash
docker compose down
```

Cette commande arrête les services associés au projet Compose, sans supprimer les fichiers sources.

---

**Validation technique :** les six programmes `stack0` à `stack5` ont été exécutés avec succès dans un environnement Docker reconstruit à partir du dépôt GitHub.

**Limite de cette validation :** elle confirme le fonctionnement des tests réalisés, mais ne remplace pas une relecture pédagogique du cahier étudiant ni une vérification de toutes les manipulations GDB.
