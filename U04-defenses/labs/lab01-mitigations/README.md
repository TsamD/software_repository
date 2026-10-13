# Lab 01 — Défenses contre les vulnérabilités mémoire

**Unité U04 — Software Security**

## Objectifs pédagogiques

Ce laboratoire permet d'observer et de comparer plusieurs mécanismes de protection des programmes C :

- Stack canaries
- NX (Non-Executable Stack)
- PIE (Position Independent Executable)
- RELRO
- Introduction aux gadgets ROP

Les exercices sont réalisés dans un conteneur Docker isolé sous Ubuntu 24.04.

## Prérequis

- Docker et Docker Compose
- Une machine Linux x86_64
- Variables `LAB_UID` et `LAB_GID` configurées sur l'hôte

Configuration initiale, à effectuer une seule fois sur la VM Ubuntu :

```bash
echo 'export LAB_UID=$(id -u)' >> ~/.bashrc
echo 'export LAB_GID=$(id -g)' >> ~/.bashrc
source ~/.bashrc
```

## Démarrage

Depuis le dossier `lab01-mitigations` :

```bash
docker compose build
docker compose run --rm lab bash
```

Dans le conteneur :

```bash
cd /workspace/src
```

Les sources sont accessibles dans `/workspace/src`.

## Lab 4.1 — Stack Canary

Compiler la version vulnérable :

```bash
gcc -m32 -fno-pie -no-pie -fno-stack-protector -z execstack -g stack3.c -o stack3
```

Compiler la version avec canary et NX :

```bash
gcc -m32 -fno-pie -no-pie -fstack-protector-all -g stack3.c -o stack3_canary
```

Comparer les protections :

```bash
readelf -lW stack3 | grep GNU_STACK
readelf -lW stack3_canary | grep GNU_STACK
readelf -sW stack3_canary | grep stack_chk
```

Déclencher le débordement :

```bash
./stack3_canary "$(python3 -c 'print("A"*80)')"
echo "Code de sortie : $?"
```

Résultat observé sur la VM de validation : `stack smashing detected`, code `134`.

## Lab 4.2 — NX et ROP

Compiler une version avec NX activé :

```bash
gcc -m32 -fno-pie -no-pie -fno-stack-protector -g stack3.c -o stack3_nx
```

Compiler les deux versions du programme de démonstration :

```bash
gcc -m32 -fno-stack-protector -fno-pie -no-pie -z noexecstack -g test_shellcode.c -o test_shellcode_nx
gcc -m32 -fno-stack-protector -fno-pie -no-pie -z execstack -g test_shellcode.c -o test_shellcode_exec
```

Vérifier les protections :

```bash
readelf -lW test_shellcode_nx | grep GNU_STACK
readelf -lW test_shellcode_exec | grep GNU_STACK
```

Tester :

```bash
./test_shellcode_nx
echo "Code de sortie : $?"
```

Résultat observé : `Segmentation fault`, code `139`.

Puis :

```bash
./test_shellcode_exec
```

Dans le shell ouvert :

```bash
echo NX_DESACTIVE_OK
exit
```

Enfin, rechercher les gadgets ROP :

```bash
python3 -m ropper --file stack3_nx --nocolor --search "pop"
```

Les adresses des gadgets peuvent varier selon le binaire et l'environnement.

## Lab 4.3 — Durcissement complet

Compiler :

```bash
gcc -m32 -fstack-protector-all -g stack3.c -o stack3_hard
```

Vérifier les protections :

```bash
readelf -lW stack3_hard | grep GNU_STACK
readelf -h stack3_hard | grep Type
readelf -sW stack3_hard | grep stack_chk
readelf -lW stack3_hard | grep GNU_RELRO
readelf -dW stack3_hard | grep -E 'BIND_NOW|FLAGS'
```

Sur l'environnement de validation, NX, PIE, canary et Full RELRO ont été confirmés.

Tester une entrée normale :

```bash
./stack3_hard "Etudiant"
echo "Code normal : $?"
```

Tester le débordement :

```bash
./stack3_hard "$(python3 -c 'print("A"*80)')"
echo "Code débordement : $?"
```

Résultats observés : code `0` pour l'entrée normale et code `134` pour le débordement.

## Sécurité et nettoyage

Les programmes sont volontairement vulnérables et doivent être exécutés uniquement dans l'environnement de laboratoire isolé.

Pour quitter le conteneur :

```bash
exit
```

Le conteneur lancé avec `--rm` est supprimé automatiquement à sa fermeture. Les fichiers présents dans le dossier monté restent conservés sur la VM.

## Documentation

Consulter le cahier étudiant U04 pour les consignes, questions et livrables attendus. Le corrigé enseignant est réservé à l'enseignant.
