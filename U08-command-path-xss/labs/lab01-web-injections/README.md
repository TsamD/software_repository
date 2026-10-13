# U08 — Injection de commandes, traversée de chemins et XSS

Environnement Docker du laboratoire U08 — Software Security.

## Prérequis

- Docker et Docker Compose (`docker compose`)
- Ports 3000, 5001 et 5003 disponibles sur la machine hôte
- Fichiers `Dockerfile`, `compose.yaml`, `src/app.py`, `src/app_fixed.py` et `src/docs/notes.txt` présents

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
| `flask-vuln` | http://127.0.0.1:5001 | Application Flask volontairement vulnérable (Labs 8.1 et 8.2) |
| `flask-fixed` | http://127.0.0.1:5003 | Application Flask corrigée (Lab 8.2) |
| `juice-shop` | http://127.0.0.1:3000 | Entraînement autonome et facultatif aux vulnérabilités web |

Si Juice Shop n'affiche pas de port dans `docker compose ps`, vérifier `127.0.0.1:3000:3000` dans `compose.yaml`, puis exécuter :

```bash
docker compose up -d --force-recreate juice-shop
```

## Vérifications rapides

```bash
# Lecture légitime : les deux applications doivent répondre
curl -i 'http://127.0.0.1:5001/file?name=notes.txt'
curl -i 'http://127.0.0.1:5003/file?name=notes.txt'

# Vérification de l'accès HTTP à Juice Shop
curl -I http://127.0.0.1:3000
```

Pour les manipulations d'injection, les correctifs et les questions, suivre le **Cahier de laboratoire étudiant U08**. Le README ne fournit pas les solutions.

## Accès depuis un poste distant (VM sans navigateur)

Les ports Docker sont liés à `127.0.0.1` sur la VM. Depuis un terminal de l'ordinateur personnel, établir un tunnel SSH vers la VM :

```bash
ssh -N \
  -L 127.0.0.1:15001:127.0.0.1:5001 \
  -L 127.0.0.1:15003:127.0.0.1:5003 \
  -L 127.0.0.1:13000:127.0.0.1:3000 \
  utilisateur@IP_DE_LA_VM
```

Garder ce terminal ouvert. Dans le navigateur du poste personnel, utiliser `http://127.0.0.1:15001`, `http://127.0.0.1:15003` et `http://127.0.0.1:13000`. Adapter les ports des URL du cahier étudiant si cette méthode est utilisée. Les ports locaux alternatifs évitent les conflits avec d'autres applications.

## OWASP Juice Shop — approfondissement facultatif

Après les Labs 8.1 et 8.2, les étudiants qui le souhaitent peuvent explorer les challenges XSS de leur instance locale de Juice Shop. Ils formulent des hypothèses, observent les réponses et comparent les mécanismes avec les applications Flask. Aucun challenge particulier ni résultat de réussite n'est imposé.

## Arrêt

```bash
docker compose down
```

> **Sécurité :** applications volontairement vulnérables. Utilisation uniquement dans un environnement de laboratoire isolé, sur des services autorisés. Ne pas exposer ces ports publiquement.
