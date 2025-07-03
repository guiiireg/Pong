# Pong Language Interpreter

Un interpréteur complet pour le langage de programmation .pong, implémenté en C.

**Version:** 1.0.0  
**Auteur:** guiiireg  
**Repository:** https://github.com/guiiireg/Pong.git

## Schéma de Versioning

- **Ajout de fonctionnalités:** 1.0.0 → 1.1.0 (version mineure)
- **Corrections de bugs:** 1.0.0 → 1.0.1 (version de patch)
- **Mises à jour majeures:** 1.x.x → 2.0.0 (version majeure)

## Installation Rapide

```bash
git clone https://github.com/guiiireg/Pong.git
cd Pong
make build
```

## Compilation

```bash
make
```

Pour une compilation en mode debug :
```bash
make debug
```

Pour une compilation optimisée :
```bash
make release
```

## Utilisation

```bash
./build/pong-interpreter <fichier.pong>
```

## Fonctionnalités Supportées

### Types de Données
- `int` : Nombres entiers
- `char` : Caractères simples
- `string` : Chaînes de caractères

### Opérations
- Déclaration de variables avec initialisation
- Assignation de valeurs à des variables existantes

### Syntaxe

#### Déclarations
```pong
int age = 25;
string name = "John Doe";
char grade = 'A';
```

#### Assignations
```pong
age = 30;
name = "Jane Smith";
grade = 'B';
```

## Exemples

Le dossier `examples/` contient plusieurs exemples :

- `counter.pong` : Manipulation de variables entières
- `strings.pong` : Opérations sur les chaînes
- `characters.pong` : Gestion des caractères

## Architecture

Le projet est organisé en modules :

- **types** : Structures de données fondamentales
- **token** : Gestion des tokens lexicaux
- **lexer** : Analyse lexicale
- **environment** : Gestion de l'environnement d'exécution
- **parser** : Analyse syntaxique
- **interpreter** : Moteur d'exécution
- **utils** : Fonctions utilitaires
- **main** : Point d'entrée principal

## Structure du Projet

```
pong/
├── src/           # Code source (.c)
├── include/       # Headers (.h)
├── build/         # Fichiers compilés
├── examples/      # Exemples de code .pong
├── lib/           # Bibliothèques (future extension)
├── tests/         # Tests unitaires (future extension)
└── Makefile       # Script de compilation
```

## Gestion d'Erreurs

L'interpréteur détecte et rapporte :
- Erreurs de syntaxe
- Variables non déclarées
- Erreurs d'allocation mémoire
- Fichiers introuvables

## Développement

### Ajouter de Nouvelles Fonctionnalités

1. Définir les nouveaux tokens dans `types.h`
2. Étendre le lexer dans `lexer.c`
3. Ajouter les règles de parsing dans `parser.c`
4. Implémenter l'exécution dans `interpreter.c`

### Tests

```bash
make test
```

## Licence

Projet éducatif - Libre d'utilisation et de modification.
