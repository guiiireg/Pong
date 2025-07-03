# Changelog

Toutes les modifications notables de ce projet seront documentées dans ce fichier.

Le format est basé sur [Keep a Changelog](https://keepachangelog.com/fr/1.0.0/),
et ce projet adhère au [Versioning Sémantique](https://semver.org/lang/fr/).

## [1.0.0] - 2025-07-03

### Ajouté
- Interpréteur complet pour le langage .pong
- Support des types de données : `int`, `char`, `string`
- Déclarations de variables avec initialisation
- Assignations de valeurs aux variables existantes
- Système de build complet avec Makefile avancé
- Gestion d'erreurs robuste avec position dans le code
- Exemples de programmes .pong
- Tests intégrés et démonstrations
- Documentation complète (README, LICENSE)
- Commandes Git intégrées dans le Makefile
- Support pour debugging avec Valgrind et GDB
- Analyse statique de code
- Configurations de build multiples (debug, release, profile, coverage)

### Architecture
- **types** : Structures de données fondamentales
- **token** : Gestion des tokens lexicaux
- **lexer** : Analyse lexicale du code source
- **environment** : Gestion de l'environnement d'exécution
- **parser** : Analyse syntaxique et construction AST
- **interpreter** : Moteur d'exécution
- **utils** : Fonctions utilitaires
- **main** : Point d'entrée principal

### Fonctionnalités supportées
```pong
int age = 25;
string name = "John";
char grade = 'A';

age = 30;
name = "Jane";
grade = 'B';
```

## [Non publié]

### Fonctionnalités prévues
- Expressions arithmétiques (`+`, `-`, `*`, `/`)
- Structures de contrôle (`if`, `else`)
- Boucles (`while`, `for`)
- Fonctions définies par l'utilisateur
- Tableaux et structures de données avancées
