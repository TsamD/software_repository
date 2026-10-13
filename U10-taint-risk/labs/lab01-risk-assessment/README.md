# U10 — Taint Analysis, CVSS & Risk Assessment

## Objectif

Ce laboratoire permet d'analyser les flux de données non fiables (source → sink), de classifier les vulnérabilités avec les CWE, de calculer des scores CVSS v3.1 et de prioriser les risques.

Les exercices sont décrits dans le cahier étudiant U10.

## Prérequis

- Docker et Docker Compose
- Environnement Linux Ubuntu 24.04
- Connaissances des unités U07 et U08

Les outils Python, Flask, CVSS, GCC et GDB sont intégrés à l'image Docker.

## Démarrage

Depuis `U10-taint-risk/labs/lab01-risk-assessment` :

```bash
export LAB_UID=$(id -u)
export LAB_GID=$(id -g)

docker compose build
docker compose run --rm lab bash
```

## Structure

```text
lab01-risk-assessment/
├── Dockerfile
├── compose.yaml
├── README.md
└── src/
    ├── heap/
    │   ├── double_free.c
    │   ├── heap_of.c
    │   ├── uaf.c
    │   └── uninit.c
    └── web/
        ├── app.py
        ├── app_fixed.py
        └── docs/
            └── notes.txt
```

Les sources sont accessibles dans le conteneur sous `/workspace/src`.

## Laboratoires

### Lab 10.1 — Taint Analysis

Analyser `src/web/app.py` et `src/web/app_fixed.py`.

Identifier pour chaque route `/login`, `/ping`, `/file` et `/search` :

- La source des données non fiables
- Le sink
- Le mécanisme de protection dans la version corrigée

### Lab 10.2 — CVSS et CWE

Calculer les scores CVSS v3.1 avec la bibliothèque Python `cvss`.

Exemple :

```bash
python3 - <<'PY'
from cvss import CVSS3
v = "CVSS:3.1/AV:N/AC:L/PR:N/UI:N/S:U/C:H/I:H/A:H"
print(CVSS3(v).base_score)
PY
```

Associer les vulnérabilités aux CWE correspondants et justifier les vecteurs retenus.

Les fichiers `src/heap/` fournissent des exemples supplémentaires de vulnérabilités mémoire à classifier.

### Lab 10.3 — Registre de risques

Construire un registre de risques à partir des vulnérabilités analysées.

Pour chaque vulnérabilité, documenter :

- Description et CWE
- Score CVSS et exploitabilité
- Actif concerné
- Traitement proposé
- Échéance

Classer les risques par priorité et justifier les décisions.

## Vérification de l'environnement

Dans le conteneur :

```bash
python3 -c "import flask, cvss; print('Flask et CVSS OK')"
python3 -m py_compile src/web/app.py src/web/app_fixed.py
```

## Sécurité

Les applications contiennent volontairement des vulnérabilités à des fins pédagogiques.

L'environnement Docker est isolé du réseau (`network_mode: none`).

Ne pas déployer ces applications sur un serveur public.
