# U11 — Fuzzing AFL++ (prototype)

**Environnement isolé, uniquement sur les programmes fournis.** Ce labo est en cours de validation sur Ubuntu x86_64. Il ne nécessite ni `--privileged`, ni modification de `/proc/sys/kernel/*`.

## Démarrer

```bash
cd labs/04-fuzzing
docker compose build
docker compose run --rm lab
```

Dans le conteneur :

```bash
./scripts/build.sh
AFL_SKIP_CPUFREQ=1 afl-fuzz -i corpus -o findings -- ./build/vuln_fuzz
```

Si AFL++ refuse de démarrer à cause de la configuration des core dumps, **ne pas modifier le noyau de l'hôte**. Lire le message d'erreur et consulter la documentation AFL++ ; une solution adaptée à l'environnement Docker sera validée avant distribution. Ne pas promettre de délai de découverte de crash.

Après découverte d'un crash :

```bash
# Choisir explicitement un fichier du dossier findings/default/crashes/
ls findings/default/crashes/
# Exemple : remplacer CHEMIN_CRASH par le chemin exact
./build/vuln_asan CHEMIN_CRASH
# Le correctif doit traiter la même entrée sans signalement ASan
./build/vuln_fixed_asan CHEMIN_CRASH
```

Pour minimiser (si la campagne le permet) :

```bash
afl-tmin -i CHEMIN_CRASH -o crash_min.bin -- ./build/vuln_fuzz
```

Pour re-fuzzer :

```bash
AFL_SKIP_CPUFREQ=1 afl-fuzz -i corpus -o findings2 -- ./build/vuln_fixed_fuzz
```

## Trois niveaux

- **N1 — Observer (30–45 min)** : exécuter une entrée courte puis une entrée longue ; lire un rapport ASan ; comprendre le tampon de 64 octets.
- **N2 — Manipuler (60–90 min)** : compiler, lancer AFL++, identifier un crash, rejouer et corriger.
- **N3 — Approfondir (60–120 min)** : minimiser une entrée, comparer la couverture, écrire un harnais déterministe pour une autre fonction.

Les durées sont des hypothèses à confirmer en classe. Le PDF du cahier étudiant fourni pour le cours est dans `../../docs/supports/` et doit encore être corrigé (notamment certains retours à la ligne dans les commandes).

## Arrêter et nettoyer

```bash
exit
docker compose down
```

Les résultats de fuzzing restent dans le dossier local et sont ignorés par Git. Pour libérer l'espace disque, supprimer localement `findings/`, `findings2/` et `build/` après sauvegarde éventuelle.
