# Questions étudiantes — Lab 02 : Threat Modeling

Nom / binôme : ____________________   Date : ____________________

## N1 — Observer et identifier (15 min)

**1. Actifs.** À partir du scénario DocuCampus, indiquez au moins **cinq actifs** et la propriété de sécurité prioritaire pour chacun (confidentialité, intégrité, disponibilité, authenticité ou traçabilité, selon le vocabulaire CIAAA du cours). Justifiez brièvement.

| Actif | Propriété prioritaire | Justification |
|---|---|---|
| | | |
| | | |
| | | |
| | | |
| | | |

**2. Acteurs et confiance.** Citez trois catégories d'utilisateurs et une frontière de confiance importante (par exemple entre navigateur et serveur). Expliquez pourquoi elle compte.

## N2 — Surface d'attaque et STRIDE (30 min)

**3. Surface d'attaque.** Recensez au moins **six points d'entrée**. Pour chacun, indiquez une donnée reçue et une vérification de sécurité à envisager.

| Point d'entrée | Donnée / action reçue | Vérification à prévoir |
|---|---|---|
| | | |
| | | |
| | | |
| | | |
| | | |
| | | |

**4. STRIDE simplifié.** Associez au moins **quatre catégories distinctes** de STRIDE à des menaces plausibles pour DocuCampus :

- **S** — Spoofing : usurpation d'identité
- **T** — Tampering : altération
- **R** — Repudiation : répudiation / contestation d'une action
- **I** — Information disclosure : divulgation d'information
- **D** — Denial of service : indisponibilité provoquée
- **E** — Elevation of privilege : élévation de privilèges

| Catégorie STRIDE | Menace plausible | Fonction concernée | Contrôle à vérifier |
|---|---|---|---|
| | | | |
| | | | |
| | | | |
| | | | |

**5. Précision du vocabulaire.** Pour un exemple de votre tableau, distinguez en quatre phrases : **menace**, **vulnérabilité potentielle**, **impact** et **risque**. N'affirmez pas qu'une vulnérabilité existe si le scénario ne le précise pas.

## N2 — Réduire les risques (20 min)

**6. Priorisation.** Choisissez trois risques et attribuez-leur une priorité **faible, moyenne ou élevée**. Justifiez qualitativement avec la vraisemblance et l'impact (aucun score chiffré requis).

| Risque | Vraisemblance estimée | Impact estimé | Priorité et justification |
|---|---|---|---|
| | | | |
| | | | |
| | | | |

**7. Contre-mesures.** Proposez **deux mesures techniques ou de conception**, précisez la menace visée, expliquez comment elles réduisent le risque et donnez une limite ou un risque résiduel pour chacune.

**8. Défense en profondeur.** Pourquoi un contrôle d'accès dans l'interface web ne suffit-il pas à protéger le téléchargement des documents ? Proposez un second contrôle à un autre niveau.

## N3 — Facultatif : réévaluer (20 min)

Une version ultérieure de DocuCampus ajoute les mesures suivantes :

- Vérification des droits sur chaque téléchargement **côté serveur**.
- Journalisation des opérations d'administration.
- Limitation du nombre de tentatives de connexion.

**9.** Quels risques de votre tableau diminuent grâce à ces mesures ? Lesquels restent plausibles ?

**10.** Proposez un test fonctionnel ou de sécurité **non destructif** pour vérifier qu'un des contrôles fonctionne, en utilisant uniquement des comptes et des documents de test autorisés.

## Critères de réussite

La réponse doit employer correctement le vocabulaire, relier les menaces aux fonctionnalités, distinguer hypothèses et faits, et justifier les contre-mesures. La qualité du raisonnement compte davantage que le nombre de menaces listées.
