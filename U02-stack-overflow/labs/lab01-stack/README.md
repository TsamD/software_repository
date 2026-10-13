# U02 — Laboratoire Stack Overflow

## Présentation

Ce laboratoire permet d'étudier la pile d'exécution (*stack*) et les débordements de tampon (*stack buffer overflow*) dans des programmes C.

Il comprend six exercices progressifs, de `stack0` à `stack5`.

Les programmes sont volontairement vulnérables et doivent être utilisés uniquement dans l'environnement de laboratoire prévu.

## 1. Prérequis

- VM Ubuntu **x86_64** dédiée aux laboratoires.
- Docker Engine et Docker Compose installés dans la VM.
- Accès à un terminal Linux.
- Notions élémentaires de langage C.

Les programmes sont compilés en architecture x86 32 bits (`gcc -m32`).

**Sécurité :** ne pas exécuter les programmes vulnérables directement sur l'ordinateur personnel, ne pas utiliser Docker avec `--privileged` et ne pas désactiver les protections mémoire de la machine personnelle.

## 2. Démarrage

Depuis la VM Ubuntu, se placer dans le répertoire :

```bash
cd software_security/U02-stack-overflow/labs/lab01-stack
```
# Vérifier l'identité de l'utilisateur
id

# Définir l'UID et le GID de l'utilisateur courant
export LAB_UID=$(id -u)
export LAB_GID=$(id -g)

# Vérifier les variables
echo "LAB_UID=$LAB_UID"
echo "LAB_GID=$LAB_GID"

Construire l'image :

```bash
docker compose build
```

Démarrer le conteneur :

```bash
docker compose run --rm lab bash
```

Le terminal doit maintenant se trouver dans `/workspace`.

Compiler tous les exercices :

```bash
bash scripts/build.sh
```

Vérifier les exécutables :

```bash
ls -l bin/
```

Les fichiers `stack0` à `stack5` doivent être présents.

## 3. Exercices

### Stack0 — Observation de la pile

**Objectif :** observer le fonctionnement d'un programme C simple, ses variables locales et ses appels de fonctions.

```bash
./bin/stack0
```

Résultat attendu :

```text
result = 6
```

Cet exercice ne nécessite pas de débordement de tampon.

### Stack1 — Modification d'une variable

**Objectif :** comprendre comment une copie non bornée peut modifier une variable voisine en mémoire.

```bash
./bin/stack1 "$(python3 -c 'print("A"*32+"BBBB")')"
```

Résultat attendu :

```text
value = 0x42424242
```

Les quatre caractères `B` correspondent à la valeur hexadécimale `0x42424242`.

### Stack2 — Atteindre une valeur cible

**Objectif :** construire une entrée qui modifie une variable pour atteindre la valeur attendue.

```bash
./bin/stack2 "$(python3 -c 'import sys; sys.stdout.buffer.write(b"A"*10+b"\xf7")')"
```

Le programme doit afficher :

```text
Condition atteinte
```

### Stack3 — Adresse de retour

**Objectif :** observer le fonctionnement d'une adresse de retour et comprendre comment un débordement peut modifier le flot d'exécution.

Exécution normale :

```bash
./bin/stack3 Alice
```

Le programme affiche notamment :

```text
Bonjour Alice
```

Pour observer le programme dans GDB :

```bash
gdb ./bin/stack3
```

Dans GDB :

```gdb
break main
run Alice
info registers
disassemble main
```

L'analyse du débordement est détaillée dans le cahier étudiant.

### Stack4 — Exécution d'un shellcode

**Objectif :** observer l'exécution d'un shellcode x86 dans un environnement contrôlé.

```bash
printf 'echo SHELLCODE_OK\nexit\n' | ./bin/stack4
```

Résultat attendu :

```text
SHELLCODE_OK
```

Le programme source correspondant est `src/stack4.c`.

### Stack5 — Exploitation avec `jmp esp`

**Objectif :** approfondir le détournement du flot d'exécution avec une instruction `jmp esp`.

Le programme vulnérable est :

```text
src/stack5.c
```

Le script de démonstration est :

```text
src/exploit_stack5.py
```

Exécuter :

```bash
python3 src/exploit_stack5.py
```

Résultat attendu :

```text
STACK5_OK
```

Le script recherche le décalage nécessaire à l'exploitation. Si les fichiers core ne sont pas disponibles, il peut utiliser une méthode alternative.

L'exercice est réservé à l'approfondissement.

## 4. Vérification rapide des six exercices

Après compilation, exécuter ce bloc dans le conteneur :

```bash
set -e

echo "===== STACK0 ====="
./bin/stack0 | grep -F 'result = 6'

echo "===== STACK1 ====="
./bin/stack1 "$(python3 -c 'print("A"*32+"BBBB")')" | grep -F 'value = 0x42424242'

echo "===== STACK2 ====="
./bin/stack2 "$(python3 -c 'import sys; sys.stdout.buffer.write(b"A"*10+b"\xf7")')" | grep -F 'Condition atteinte'

echo "===== STACK3 ====="
./bin/stack3 Alice | grep -F 'Bonjour Alice'

echo "===== STACK4 ====="
printf 'echo SHELLCODE_OK\nexit\n' | ./bin/stack4 | grep -F 'SHELLCODE_OK'

echo "===== STACK5 ====="
python3 src/exploit_stack5.py | grep -F 'STACK5_OK'

echo "===== FIN ====="
echo "U02 : TOUS LES TESTS ONT RÉUSSI"
```

Si tous les tests réussissent, la dernière ligne sera :

```text
U02 : TOUS LES TESTS ONT RÉUSSI
```

Ce test vérifie les comportements attendus, mais ne remplace pas les observations demandées dans le cahier étudiant.

## 5. Débogage avec GDB

GDB permet d'observer les registres, la mémoire et les instructions exécutées.

Commandes utiles :

| Commande | Fonction |
|---|---|
| `break main` | Placer un point d'arrêt dans `main` |
| `run` | Démarrer le programme |
| `next` | Exécuter la ligne suivante sans entrer dans les fonctions |
| `step` | Exécuter la ligne suivante en entrant dans les fonctions |
| `info registers` | Afficher les registres |
| `info frame` | Afficher les informations de la trame courante |
| `x/32wx $esp` | Examiner 32 mots mémoire depuis ESP |
| `disassemble main` | Afficher le code assembleur de `main` |
| `quit` | Quitter GDB |

Les exercices étant compilés en x86 32 bits, les registres étudiés comprennent notamment `EIP`, `ESP` et `EBP`.

## 6. Dépannage

**Le dossier `bin/` est vide :**

Relancer :

```bash
bash scripts/build.sh
```

**Un programme est introuvable :**

Vérifier le répertoire courant et les fichiers :

```bash
pwd
ls -l bin/
```

**Le conteneur ne démarre pas :**

Quitter le laboratoire et reconstruire l'image depuis la VM :

```bash
docker compose build --no-cache
docker compose run --rm lab bash
```

**Le script `stack5` indique qu'aucun fichier core n'est disponible :**

Ce message peut être normal. Le script dispose d'un mécanisme alternatif. Vérifier si `STACK5_OK` apparaît à la fin.

**Un programme affiche `Segmentation fault` :**

Un débordement peut provoquer un accès mémoire invalide. Dans ce laboratoire, cela peut être un comportement attendu selon l'entrée fournie. Utiliser GDB pour comprendre la cause.

## 7. Protections et bonnes pratiques

Les programmes du laboratoire sont volontairement compilés avec certaines protections désactivées pour permettre l'observation des vulnérabilités.

En production, il convient notamment de :

- Contrôler les tailles avant les copies en mémoire.
- Éviter les copies non bornées.
- Activer les protections de pile.
- Utiliser NX, ASLR et PIE.
- Tester les programmes avec des outils d'analyse adaptés.

La priorité reste de **corriger les vulnérabilités dans le code source**.

## 8. Arrêt du laboratoire

Dans le conteneur :

```bash
exit
```

Depuis la VM :

```bash
docker compose down
```

## 9. Documentation pédagogique

Les questions, manipulations guidées et travaux à remettre figurent dans le cahier étudiant :

`../../supports/C_U2_Cahier_labo_etudiant.pdf`

---

**État de validation :** les six exercices ont passé les tests fonctionnels après reconstruction de l'environnement depuis le dépôt GitHub.
