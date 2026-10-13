# U07 — Injection SQL (SQLi)

Environnement Docker du laboratoire U07 — Software Security.

## Prérequis

- Docker et Docker Compose (`docker compose`)
- Ports 3000, 5001 et 5003 disponibles sur la machine hôte
- Fichiers `Dockerfile`, `compose.yaml`, `src/app.py` et `src/app_fixed.py` présents

## Démarrage

Depuis le dossier contenant `compose.yaml` :

```bash
id
export LAB_UID=$(id -u)
export LAB_GID=$(id -g)

docker compose build
docker compose up -d
docker compose ps
```

## Services

| Service | URL locale | Utilisation |
| --- | --- | --- |
| `flask-vuln` | http://127.0.0.1:5001 | Application Flask volontairement vulnérable (Lab 7.1) |
| `flask-fixed` | http://127.0.0.1:5003 | Application Flask corrigée (Lab 7.2) |
| `juice-shop` | http://127.0.0.1:3000 | Application d'entraînement OWASP Juice Shop (Lab 7.3) |

Le service Juice Shop doit publier le port `127.0.0.1:3000:3000` dans `compose.yaml`. Si la colonne `PORTS` de `docker compose ps` est vide pour ce service, vérifier sa configuration et le recréer :

```bash
docker compose up -d --force-recreate juice-shop
```

## Vérifications rapides

```bash
# Connexion légitime (doit réussir dans les deux versions)
curl -sG 'http://127.0.0.1:5001/login' --data-urlencode 'user=admin' --data-urlencode 'pass=S3cret!'
curl -sG 'http://127.0.0.1:5003/login' --data-urlencode 'user=admin' --data-urlencode 'pass=S3cret!'

# Vérification de l'accès HTTP à Juice Shop
curl -I http://127.0.0.1:3000
```

Pour les manipulations d'injection et les questions à rendre, suivre le **Cahier de laboratoire étudiant U07**, Labs 7.1 à 7.3. Le README ne contient pas les solutions.

## Arrêt

```bash
docker compose down
```

> **Sécurité :** applications volontairement vulnérables. Utilisation uniquement dans un environnement de laboratoire isolé, sur des services autorisés. Ne pas exposer ces ports publiquement.
