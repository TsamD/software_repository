# U05 — Analyse de binaires et sanitizers

## Objectifs

Cette unité comprend trois laboratoires :

- **Lab 5.1 — Analyse boîte noire :** examiner un binaire avec `strings`, `objdump`, Radare2 et GDB.
- **Lab 5.2 — ASan et UBSan :** compiler et analyser des programmes C présentant des vulnérabilités.
- **Lab 5.3 — Audit de code C :** identifier des fonctions dangereuses et confirmer les vulnérabilités avec les sanitizers.

## Prérequis

- Docker et Docker Compose
- Environnement Linux (testé sur Ubuntu 24.04)

## Démarrage

Depuis le dossier contenant `Dockerfile` et `compose.yaml` :

```bash
export LAB_UID=$(id -u)
export LAB_GID=$(id -g)

docker compose build
docker compose run --rm lab bash
```

## Fichiers des laboratoires

Les fichiers se trouvent dans le répertoire `src/` :

| Fichier | Laboratoire |
|---|---|
| `cible_bb` | Lab 5.1 — Binaire à analyser sans code source |
| `intov.c` | Lab 5.2 — Dépassement d'entier signé |
| `heap_of.c` | Lab 5.2 — Débordement mémoire |
| `code.c` | Lab 5.3 — Programme C à auditer |

## Accès aux exercices

Dans le conteneur :

```bash
cd /workspace/src
```

Les consignes détaillées figurent dans le **cahier de laboratoire étudiant U05**.

## Outils disponibles

GDB, Radare2, `strings`, `objdump`, `readelf`, `nm`, `file`, Clang, AddressSanitizer (ASan) et UndefinedBehaviorSanitizer (UBSan).

## Arrêt

Pour quitter le conteneur :

```bash
exit
```

Les fichiers modifiés dans `/workspace` sont conservés dans le dossier du laboratoire sur la machine hôte.
