# Scénario — DocuCampus

Une petite école souhaite mettre à disposition des étudiants et des enseignants des documents pédagogiques via une application web nommée **DocuCampus**.

## Fonctionnalités prévues

- Un utilisateur se connecte avec une adresse courriel et un mot de passe.
- Un **étudiant** consulte la liste des documents de ses cours et télécharge les documents auxquels il a droit.
- Un **enseignant** dépose des documents et peut les remplacer ou les retirer pour ses cours.
- Un **administrateur** crée les comptes, affecte les utilisateurs aux cours et consulte un journal des opérations importantes.
- Un utilisateur peut demander une réinitialisation de mot de passe par courriel.

## Parcours illustratifs

Les adresses ci-dessous sont des **exemples de points d'entrée**, pas une implémentation ni la preuve d'une vulnérabilité.

| Fonction | Exemple d'interface ou de route |
|---|---|
| Connexion | Formulaire `/login` |
| Catalogue des documents | Page `/courses` |
| Consultation / téléchargement | Lien `/documents/42/download` |
| Dépôt de fichier | Formulaire `/upload` |
| Administration | Page `/admin/users` |
| Réinitialisation | Formulaire `/reset-password` |

## Données et composants

- Comptes et rôles (étudiant, enseignant, administrateur).
- Inscriptions aux cours et droits d'accès.
- Documents publics et documents réservés à certains cours.
- Fichiers téléversés, métadonnées, journaux d'audit.
- Navigateur, serveur web, stockage des documents, base de données et service d'envoi de courriels.

## Hypothèses de travail

- Le service est accessible sur Internet et utilisé depuis des appareils personnels.
- Certains documents contiennent des informations personnelles fictives et doivent rester confidentiels.
- L'équipe de développement est petite ; elle souhaite lancer une première version rapidement.
- **Aucun détail n'est fourni** sur les contrôles d'accès côté serveur, la gestion des sessions, le stockage des mots de passe, la validation des fichiers ou la journalisation effective.

Votre mission n'est pas de déclarer l'application vulnérable sans preuve : vous devez **identifier des menaces plausibles, les conditions dans lesquelles elles deviendraient des risques et les contrôles à vérifier ou à prévoir**.
