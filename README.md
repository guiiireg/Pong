# Pong Language Interpreter

Un interpréteur complet pour le langage de programmation .pong, implémenté en C.

**Version:** 1.0.0  
**Auteur:** guiiireg  
**Repository:** https://github.com/guiiireg/Pong.git

## Schéma de Versioning

- **Ajout de fonctionnalités:** 1.0.0 → 1.1.0 (version mineure)
- **Corrections de bugs:** 1.0.0 → 1.0.1 (version de patch)
- **Mises à jour majeures:** 1.x.x → 2.0.0 (version majeure)

## Gestion de Version et Git

Le projet utilise un système de versioning sémantique. La gestion Git est séparée du système de build :

### Configuration Git initiale
```bash
./setup-github.sh    # Script d'initialisation automatique
```

### Gestion des versions
- **Fonctionnalités :** 1.0.0 → 1.1.0 (modifier VERSION dans Makefile)
- **Corrections :** 1.0.0 → 1.0.1 (modifier VERSION dans Makefile)  
- **Changements majeurs :** 1.x.x → 2.0.0 (modifier VERSION dans Makefile)

```bash
make version-info     # Afficher les informations de version
```

### Première installation depuis GitHub
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
Pong/
├── src/           # Code source (.c)
├── include/       # Headers (.h)
├── build/         # Fichiers compilés (généré)
├── examples/      # Exemples de code .pong
├── tests/         # Tests unitaires (future extension)
├── Makefile       # Système de build complet
├── README.md      # Documentation du projet
├── LICENSE        # Licence MIT
└── .gitignore     # Fichiers à ignorer par Git
```

## Développement

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
