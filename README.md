# Software Security — Cours et laboratoires

**Cours Software Security** — Enseignement supérieur de type court
EPHEC

**Auteure :** Ibtissam Derfoufi
**Version :** préparation 2025-2026 · octobre 2026

> © 2026 Ibtissam Derfoufi. Support pédagogique interne destiné à l'UE Software Security.
> Les laboratoires, Dockerfiles, configurations Compose et programmes C/Python de ce dépôt
> sont mon travail, sauf les éléments tiers crédités plus bas. Usage réservé au cours ;
> toute réutilisation ou redistribution est soumise à mon autorisation préalable.

---

## Présentation

Ce dépôt regroupe mes supports et laboratoires pour le cours Software Security.
Chaque unité propose un laboratoire Docker **autonome** :
un programme volontairement vulnérable, sa version corrigée (`*_fixed`), et les consignes de
manipulation. L'objectif est d'**observer** une vulnérabilité, de la **reproduire**, de la
**diagnostiquer** avec les bons outils, puis de la **corriger**.

Principe de conception : chaque labo **démarre indépendamment**, dans son propre conteneur
isolé, sans réseau et sans privilèges. Aucun conteneur n'a besoin des autres ; on ne lance
que le labo de la séance.

## Progression pédagogique

Chaque laboratoire est pensé sur trois niveaux :

| Niveau | Objectif |
|---|---|
| N1 — Observer | Découvrir le mécanisme et comprendre les résultats |
| N2 — Manipuler | Reproduire, diagnostiquer et corriger (travail guidé) |
| N3 — Approfondir | Explorer les mécanismes internes et travailler en autonomie |

## Unités

| Unité | Thème | Labo |
|---|---|---|
| U01 | Introduction, menaces, modélisation (STRIDE) | Threat modeling (sur dossier, sans Docker) |
| U02 | Pile et sécurité mémoire | `stack0`–`stack5`, shellcode, `jmp esp` |
| U03 | Heap et erreurs mémoire | heap overflow, use-after-free, double-free, mémoire non initialisée |
| U04 | Défenses mémoire et contournement | ASLR, NX, protections, gadgets/ROP |
| U05 | Analyse de binaires et sanitizers | analyse boîte noire, ASan/UBSan, audit de code C |
| U06 | Langages sûrs en mémoire (Rust) | ownership, borrowing, lifetimes |
| U07 | Injection SQL | application Flask vulnérable + corrigée |
| U08 | Injection commande / path / XSS | injections web, versions vulnérable + corrigée |
| U09 | Analyse statique (SAST) | Bandit, Cppcheck, Semgrep |
| U10 | Taint, risque et CVSS | évaluation de gravité et d'exploitabilité |
| U11 | Fuzzing | AFL++, AddressSanitizer, triage et correction de crashs |
| U12 | Projet | conception et évaluation d'un système logiciel sécurisé |

## Prérequis techniques

- VM **Ubuntu x86_64** dédiée aux laboratoires (environnement de référence).
- **Docker Engine** et le plugin **Docker Compose** (`docker compose`).
- Terminal Linux. Notions de C, de ligne de commande et, selon les labos, de web.

Un instantané de la VM avant chaque séance est recommandé.

## Démarrer un laboratoire

Chaque labo possède son propre `README.md` avec le détail des exercices. Le schéma général :

```bash
# Se placer dans le dossier du labo, ex. :
cd U02-stack-overflow/labs/lab01-stack

# L'utilisateur du conteneur reprend votre UID/GID pour écrire dans le dossier partagé
export LAB_UID=$(id -u)
export LAB_GID=$(id -g)

docker compose build
docker compose run --rm lab bash
```

Dans le conteneur, suivre le `README.md` du labo (compilation, manipulation, correction).

**Exceptions de nom de service :**
- U06 (Rust) : le service s'appelle `rust-lab` → `docker compose run --rm rust-lab bash`
- U07 / U08 (web) : services persistants, on utilise `docker compose up -d` puis on consulte
  les URL locales indiquées dans le README du labo (ex. `http://127.0.0.1:5001`).

Pour arrêter et nettoyer :

```bash
exit
docker compose down
```

## Sécurité des environnements

Les programmes et services de ce dépôt sont **volontairement vulnérables** et strictement
réservés à un usage pédagogique contrôlé.

- Ne jamais exécuter ces programmes directement sur un poste personnel.
- Ne pas exposer les services sur Internet (les ports sont liés à `127.0.0.1`).
- Pas de mode `--privileged` ; les conteneurs tournent sans réseau (`network_mode: none`)
  et sans nouveaux privilèges (`no-new-privileges`).
- Ne lancer que le labo nécessaire ; arrêter les conteneurs après usage.
- Tout réglage sensible (ex. ASLR) uniquement dans la VM, puis restauré.

## Crédits et éléments tiers

Le code des laboratoires, les Dockerfiles, les configurations Compose et les programmes
d'exercice (y compris `cible_bb` / `cible_bb.c`) sont mon travail.

Les éléments suivants sont tiers et restent la propriété de leurs auteurs ; ils sont
seulement utilisés comme support :

- Images Docker de base (Ubuntu, Python, Rust).
- Outils installés dans les images (GCC, GDB, Valgrind, Radare2, Clang/LLVM, AFL++,
  Bandit, Cppcheck, Semgrep, Ropper, etc.).
- Applications d'entraînement web (ex. OWASP Juice Shop), citées dans les labos concernés.

Avant toute publication, l'originalité, les licences et les droits de réutilisation de
chaque élément seront vérifiés.

---

**Principe du projet : comprendre, reproduire, vérifier, corriger, puis enseigner.**
