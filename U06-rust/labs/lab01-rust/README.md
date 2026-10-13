# U06 — Langages sûrs en mémoire (Rust)

## Lab 6.1 — Ownership, borrowing et lifetimes

Ce laboratoire permet d'observer trois erreurs détectées par le compilateur Rust 1.75, puis de corriger les programmes. Les fichiers originaux sont volontairement non compilables.

## Prérequis

- Docker et Docker Compose sur la VM Ubuntu 24.04.
- Cours U06 et notions de mémoire des unités U02–U03.
- Aucun besoin d'installer Rust sur la VM : il est fourni par l'image Docker.

## Arborescence

```text
lab01-rust/
├── Dockerfile
├── compose.yaml
├── README.md
└── src/
    ├── move.rs
    ├── borrow.rs
    └── lifetime.rs
```

## Démarrer le laboratoire

Depuis le dossier `lab01-rust` sur la VM :

```bash
export LAB_UID=$(id -u)
export LAB_GID=$(id -g)

docker compose build
docker compose run --rm rust-lab bash
```

La configuration conserve `USER student` dans le Dockerfile et les variables `LAB_UID` / `LAB_GID` dans Compose. L'identité effective dépend de la configuration Compose.

## Vérifier l'environnement

Dans le conteneur :

```bash
whoami
id
rustc --version
ls -l /workspace/src
cd /workspace/src
```

Version attendue : `rustc 1.75.0`.

## Exécuter les exercices

```bash
rustc --edition 2021 move.rs
rustc --edition 2021 borrow.rs
rustc --edition 2021 lifetime.rs
```

| Fichier | Erreur attendue | Notion |
|---|---|---|
| `move.rs` | `E0382` | Valeur utilisée après déplacement de propriété |
| `borrow.rs` | `E0502` | Conflit entre emprunt immuable et emprunt mutable |
| `lifetime.rs` | `E0597` | Référence dont la donnée ne vit pas assez longtemps |

**Ces échecs de compilation sont attendus.** Pour consulter les explications :

```bash
rustc --explain E0382
rustc --explain E0502
rustc --explain E0597
```

## Corriger et vérifier

Suivre les consignes du cahier étudiant : corriger les trois programmes, recompiler puis exécuter les binaires obtenus. Pour préserver les sources initiales, travailler sur des copies dans `/tmp`, par exemple :

```bash
cp move.rs /tmp/move_fixed.rs
# Modifier la copie selon le cahier étudiant.
rustc --edition 2021 /tmp/move_fixed.rs -o /tmp/move_fixed
/tmp/move_fixed
```

Appliquer la même démarche à `borrow.rs` et `lifetime.rs`. Le README ne fournit pas les solutions ; elles figurent dans le corrigé enseignant.

## Terminer

```bash
exit
```

Depuis la VM, si nécessaire :

```bash
docker compose down
```

Les fichiers du dossier `src/` restent sur la VM grâce au montage de volume. Les copies créées dans `/tmp` du conteneur éphémère ne sont pas conservées.
