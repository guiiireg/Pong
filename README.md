# Pong Language

Un langage de programmation interprété, implémenté en C.

**Repository:** https://github.com/guiiireg/Pong.git

**État actuel:** En développement - Seuls les types de base sont implémentés.

## Installation

```bash
git clone https://github.com/guiiireg/Pong.git
cd Pong
make build
```

## Prérequis

- GCC (C99 ou supérieur)
- Make

## Compilation

```bash
make build          # Version debug
make release        # Version optimisée
make clean          # Nettoyer les fichiers de compilation
```

## État actuel du développement

### Implémenté
- Types de base : `int`, `char`, `string`
- Structure de base du projet
- Système de build

### À implémenter
- Lexer (analyse lexicale)
- Parser (analyse syntaxique) 
- Interpréteur (exécution du code)
- Déclarations de variables
- Opérations de base
- Structures de contrôle

## Architecture

Le projet est organisé en modules :

- `types` : Structures de données de base (implémenté)
- `lexer` : Analyse lexicale (à faire)
- `parser` : Analyse syntaxique (à faire)
- `interpreter` : Exécution du code (à faire)
- `main` : Point d'entrée

### Structure du projet
```
Pong/
├── src/              # Code source
│   ├── main.c        # Point d'entrée
│   ├── types.c       # Types de base (implémenté)
│   ├── lexer.c       # Analyse lexicale (à faire)
│   ├── parser.c      # Analyse syntaxique (à faire)
│   └── interpreter.c # Interpréteur (à faire)
├── include/          # Headers
│   ├── types.h       # Types (implémenté)
│   └── ...           # Autres headers (à faire)
├── build/            # Fichiers compilés
├── examples/         # Exemples de code Pong (à faire)
├── tests/            # Tests (à faire)
├── Makefile          # Système de build
├── README.md         # Documentation
└── LICENSE           # Licence MIT
```

## Licence

Ce projet est sous licence MIT. Voir [LICENSE](LICENSE) pour plus de détails.
