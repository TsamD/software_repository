# U03 — Lab 01 : Heap et erreurs de gestion mémoire

## Objectifs pédagogiques

Ce laboratoire permet d'identifier, reproduire et analyser quatre catégories d'erreurs de gestion mémoire dans des programmes C :

- **Heap buffer overflow** : écriture au-delà d'une zone allouée.
- **Use-after-free (UAF)** : accès à une zone mémoire après sa libération.
- **Double-free** : libération répétée d'un même bloc mémoire.
- **Uninitialized memory** : utilisation de valeurs non initialisées.

Les exercices utilisent **AddressSanitizer (ASan)** et **Valgrind Memcheck** pour observer et comprendre les erreurs.

## 1. Prérequis

- Docker et Docker Compose
- VM Ubuntu x86_64
- GCC, AddressSanitizer et Valgrind (installés dans l'image Docker du laboratoire)

Les tests doivent être effectués dans l'environnement Docker prévu.

## 2. Structure du laboratoire

```text
lab01-heap/
├── Dockerfile
├── compose.yaml
├── README.md
└── src/
    ├── heap_of.c
    ├── uaf.c
    ├── double_free.c
    └── uninit.c
```

Le dossier `bin/` sera créé pendant les manipulations pour accueillir les exécutables compilés.

## 3. Démarrage

Depuis le dossier `lab01-heap/`, sur la VM Ubuntu :

```bash
export LAB_UID=$(id -u)
export LAB_GID=$(id -g)


echo "LAB_UID=$LAB_UID"
echo "LAB_GID=$LAB_GID"

docker compose build
docker compose run --rm lab bash
```

Le fichier `compose.yaml` doit contenir :

```yaml
user: "${LAB_UID:?Définir LAB_UID}:${LAB_GID:?Définir LAB_GID}"
```

Dans le conteneur :

```bash
mkdir -p bin
```

Toutes les commandes suivantes s'exécutent **dans le conteneur**.

## 4. Exercice 1 — Heap buffer overflow

### Compilation

```bash
gcc -O0 -g -fsanitize=address \
    -fno-omit-frame-pointer \
    src/heap_of.c -o bin/heap_of_asan
```

### Test normal

```bash
./bin/heap_of_asan bonjour
```

Résultat attendu :

```text
bonjour
```

### Test vulnérable

```bash
./bin/heap_of_asan AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
```

Diagnostic attendu :

```text
ERROR: AddressSanitizer: heap-buffer-overflow
WRITE of size 33
```

**Explication :** le programme alloue 16 octets, mais tente d'y copier une chaîne de 32 caractères, plus son caractère nul final.

## 5. Exercice 2 — Use-after-free

### Compilation

```bash
gcc -O0 -g -fsanitize=address \
    -fno-omit-frame-pointer \
    src/uaf.c -o bin/uaf_asan
```

### Exécution

```bash
./bin/uaf_asan
```

Diagnostic attendu :

```text
ERROR: AddressSanitizer: heap-use-after-free
READ of size 8
```

**Explication :** une structure `Session` est libérée avec `free(s)`, puis le programme tente d'accéder à son pointeur de fonction `action`.

Le rapport permet de retrouver l'allocation, la libération et l'accès interdit.

## 6. Exercice 3 — Double-free

### Compilation

```bash
gcc -O0 -g -fsanitize=address \
    -fno-omit-frame-pointer \
    src/double_free.c -o bin/double_free_asan
```

### Exécution

```bash
./bin/double_free_asan
```

Diagnostic attendu :

```text
ERROR: AddressSanitizer: attempting double-free
```

**Explication :** le programme appelle deux fois `free(p)` pour la même allocation.

AddressSanitizer identifie la seconde libération ainsi que la première.

## 7. Exercice 4 — Mémoire non initialisée

AddressSanitizer ne détecte pas les lectures de mémoire non initialisée. Cet exercice utilise donc **Valgrind Memcheck**.

### Compilation

```bash
gcc -O0 -g src/uninit.c -o bin/uninit
```

### Exécution

```bash
valgrind --tool=memcheck --track-origins=yes ./bin/uninit
```

Diagnostic attendu :

```text
Conditional jump or move depends on uninitialised value(s)
Uninitialised value was created by a heap allocation
```

**Explication :** le tableau dynamique contient quatre entiers, mais seuls les deux premiers sont initialisés. Le programme utilise ensuite les quatre valeurs pour calculer une somme.

L'affichage numérique éventuel n'est pas fiable : le programme présente un comportement indéfini.

Valgrind peut signaler plusieurs erreurs issues de la même cause. Il peut également confirmer que tous les blocs ont été libérés, sans que cela signifie que le programme est exempt d'erreurs.

## 8. Synthèse

| Programme | Vulnérabilité | Outil |
|---|---|---|
| `heap_of.c` | Heap buffer overflow | ASan |
| `uaf.c` | Use-after-free | ASan |
| `double_free.c` | Double-free | ASan |
| `uninit.c` | Mémoire non initialisée | Valgrind |

## 9. Questions de réflexion

1. Quelle différence existe-t-il entre un débordement sur la stack et un débordement sur la heap ?
2. Pourquoi un pointeur peut-il encore contenir une adresse après `free()` ?
3. Pourquoi `free(NULL)` est-il autorisé alors qu'une double libération ne l'est pas ?
4. Pourquoi un programme présentant un comportement indéfini peut-il parfois sembler fonctionner ?
5. Quelle différence existe-t-il entre AddressSanitizer et Valgrind Memcheck ?
6. Quelles modifications permettraient de corriger chacune des quatre vulnérabilités ?

## 10. Bonnes pratiques

- Vérifier les tailles avant toute copie mémoire.
- Contrôler les résultats des allocations.
- Définir clairement la responsabilité de chaque allocation et de sa libération.
- Ne jamais utiliser une allocation après sa libération.
- Initialiser les données avant leur lecture.
- Utiliser les sanitizers et les analyseurs mémoire pendant le développement.

## 11. Nettoyage

Quitter le conteneur :

```bash
exit
```

Puis, depuis la VM Ubuntu :

```bash
docker compose down
```

Les exécutables compilés sont des artefacts locaux et n'ont pas besoin d'être versionnés dans Git.
