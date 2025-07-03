# Contributing to Pong Language Interpreter

Merci de votre intérêt pour contribuer au projet **Pong Language Interpreter** ! 🎉

Ce guide vous aidera à comprendre comment contribuer efficacement au projet.

## 📋 Table des matières

- [Code de conduite](#code-de-conduite)
- [Comment contribuer](#comment-contribuer)
- [Signaler des bugs](#signaler-des-bugs)
- [Proposer des fonctionnalités](#proposer-des-fonctionnalités)
- [Contribuer au code](#contribuer-au-code)
- [Standards de code](#standards-de-code)
- [Workflow de développement](#workflow-de-développement)
- [Tests](#tests)
- [Documentation](#documentation)
- [Communauté](#communauté)

## 🤝 Code de conduite

En participant à ce projet, vous acceptez de respecter notre code de conduite :

- **Soyez respectueux** : Traitez tous les participants avec respect et courtoisie
- **Soyez constructif** : Focalisez-vous sur l'amélioration du projet
- **Soyez inclusif** : Accueillez les contributions de tous niveaux d'expérience
- **Soyez patient** : Comprenez que chacun a des niveaux d'expertise différents

## 🚀 Comment contribuer

Il y a plusieurs façons de contribuer au projet :

### 🐛 Signaler des bugs
- Utilisez le [template de bug report](https://github.com/guiiireg/Pong/issues/new?template=bug_report.yml)
- Fournissez le maximum d'informations pour reproduire le problème
- Incluez votre environnement système et la version utilisée

### ✨ Proposer des fonctionnalités
- Utilisez le [template de feature request](https://github.com/guiiireg/Pong/issues/new?template=feature_request.yml)
- Expliquez clairement le problème que la fonctionnalité résoudrait
- Proposez une solution et discutez des alternatives

### ❓ Poser des questions
- Utilisez le [template de question](https://github.com/guiiireg/Pong/issues/new?template=question.yml)
- Consultez d'abord la documentation et les issues existantes

### 💻 Contribuer au code
- Suivez le workflow décrit ci-dessous
- Respectez les standards de code
- Ajoutez des tests pour vos changements
- Mettez à jour la documentation si nécessaire

## 🔧 Contribuer au code

### Prérequis

Assurez-vous d'avoir installé :
- **GCC** (compatible C99 ou supérieur)
- **Make** (pour le système de build)
- **Git** (pour le versioning)

Outils recommandés :
- **Valgrind** (pour le debugging mémoire)
- **clang-format** (pour le formatage du code)
- **cppcheck** (pour l'analyse statique)

### Fork et clone

1. **Fork** le repository sur GitHub
2. **Clone** votre fork localement :
   ```bash
   git clone https://github.com/VOTRE-USERNAME/Pong.git
   cd Pong
   ```

3. **Ajoutez** le repository original comme remote :
   ```bash
   git remote add upstream https://github.com/guiiireg/Pong.git
   ```

### Workflow de développement

1. **Synchronisez** avec le repository principal :
   ```bash
   git checkout main
   git pull upstream main
   ```

2. **Créez** une branche pour votre fonctionnalité :
   ```bash
   git checkout -b feature/ma-super-fonctionnalite
   ```

3. **Développez** votre fonctionnalité :
   ```bash
   # Compilez et testez régulièrement
   make build
   make test
   ```

4. **Testez** vos changements :
   ```bash
   # Tests complets
   make test
   make test-examples
   make format-check
   make analyze
   ```

5. **Commitez** vos changements :
   ```bash
   git add .
   git commit -m "feat: ajoute support pour les boucles for"
   ```

6. **Pushez** votre branche :
   ```bash
   git push origin feature/ma-super-fonctionnalite
   ```

7. **Ouvrez** une Pull Request sur GitHub

## 📏 Standards de code

### Style de code

- **Standard C99** avec extensions GNU si nécessaire
- **Indentation** : 4 espaces (pas de tabs)
- **Longueur de ligne** : maximum 80 caractères
- **Noms de variables** : snake_case
- **Noms de fonctions** : snake_case
- **Noms de constantes** : UPPER_CASE
- **Noms de structures** : PascalCase

### Exemple de style :
```c
// ✅ Bon style
typedef struct {
    int value;
    char *name;
} VariableData;

static int calculate_expression_value(const Expression *expr) {
    if (expr == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    switch (expr->type) {
        case EXPR_NUMBER:
            return expr->data.number;
        case EXPR_VARIABLE:
            return get_variable_value(expr->data.variable);
        default:
            return ERROR_UNKNOWN_TYPE;
    }
}
```

### Conventions de nommage

#### Fichiers
- **Sources** : `module_name.c`
- **Headers** : `module_name.h`
- **Tests** : `test_module_name.c`

#### Fonctions
- **Publiques** : `module_function_name()`
- **Privées** : `static module_internal_function()`
- **Utilitaires** : `util_helper_function()`

#### Structures et énums
```c
// Énumérations
typedef enum {
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_IDENTIFIER
} TokenType;

// Structures
typedef struct {
    TokenType type;
    char *value;
    size_t length;
} Token;
```

### Gestion des erreurs

- **Utilisez** les codes de retour pour signaler les erreurs
- **Définissez** des constantes pour les codes d'erreur
- **Documentez** les cas d'erreur dans les commentaires

```c
// Codes d'erreur standardisés
#define SUCCESS 0
#define ERROR_NULL_POINTER -1
#define ERROR_MEMORY_ALLOCATION -2
#define ERROR_INVALID_SYNTAX -3

int parse_expression(const char *input, Expression **result) {
    if (input == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    *result = malloc(sizeof(Expression));
    if (*result == NULL) {
        return ERROR_MEMORY_ALLOCATION;
    }
    
    // ... parsing logic ...
    
    return SUCCESS;
}
```

### Commentaires et documentation

- **Commentez** les fonctions publiques avec leur but et usage
- **Expliquez** les algorithmes complexes
- **Documentez** les paramètres et valeurs de retour
- **Utilisez** des commentaires en français ou anglais selon le contexte

```c
/**
 * Parse une expression arithmétique et retourne un AST
 * 
 * @param input Chaîne contenant l'expression à parser
 * @param result Pointeur vers le pointeur de résultat (modifié)
 * @return SUCCESS en cas de succès, code d'erreur sinon
 */
int parse_arithmetic_expression(const char *input, Expression **result);
```

## 🧪 Tests

### Types de tests

1. **Tests unitaires** : Pour tester des fonctions individuelles
2. **Tests d'intégration** : Pour tester l'interpréteur complet
3. **Tests d'exemples** : Pour valider les fichiers .pong d'exemple

### Écrire des tests

```c
// test_lexer.c
#include "test_framework.h"
#include "lexer.h"

void test_lexer_numbers() {
    Token *tokens;
    int count = tokenize("123", &tokens);
    
    assert_equals(count, 1);
    assert_equals(tokens[0].type, TOKEN_TYPE_NUMBER);
    assert_string_equals(tokens[0].value, "123");
    
    free_tokens(tokens, count);
}
```

### Lancer les tests

```bash
# Tests unitaires
make test

# Tests des exemples
make test-examples

# Tests avec coverage
make test-coverage

# Tests mémoire avec Valgrind
make valgrind-test
```

## 📚 Documentation

### Que documenter

- **README.md** : Guide d'installation et d'usage
- **Code source** : Commentaires dans les fonctions
- **CHANGELOG.md** : Historique des versions
- **Exemples** : Fichiers .pong démonstratifs

### Format de la documentation

- Utilisez **Markdown** pour les fichiers de documentation
- Incluez des **exemples de code** pratiques
- Ajoutez des **captures d'écran** si pertinent
- Maintenez la **cohérence** avec l'existant

## 🎯 Types de contributions

### 🐛 Corrections de bugs

Priorité pour les bugs :
1. **Critiques** : Crashes, corruption de données
2. **Majeurs** : Fonctionnalités cassées
3. **Mineurs** : Comportements inattendus
4. **Cosmétiques** : Messages d'erreur, formatage

### ✨ Nouvelles fonctionnalités

Exemples de fonctionnalités recherchées :
- Support de nouveaux types de données
- Nouvelles constructions syntaxiques (if, while, for)
- Améliorations des messages d'erreur
- Optimisations de performance
- Outils de debugging

### 🎨 Améliorations

- Refactoring du code pour améliorer la lisibilité
- Optimisations de performance
- Amélioration de l'architecture
- Meilleure gestion des erreurs

## 🔄 Processus de review

### Critères de review

1. **Fonctionnalité** : Le code fait-il ce qu'il est censé faire ?
2. **Tests** : Y a-t-il des tests suffisants ?
3. **Style** : Le code respecte-t-il les conventions ?
4. **Performance** : Y a-t-il des impacts sur les performances ?
5. **Sécurité** : Y a-t-il des failles de sécurité potentielles ?
6. **Documentation** : La documentation est-elle à jour ?

### Timeline de review

- **24-48h** : Premier regard par un maintainer
- **3-7 jours** : Review complète et feedback
- **1-2 semaines** : Merge après validation

## 🏷️ Conventions de commit

Utilisez le format [Conventional Commits](https://www.conventionalcommits.org/) :

```
type(scope): description

[body optionnel]

[footer optionnel]
```

### Types de commit

- **feat** : Nouvelle fonctionnalité
- **fix** : Correction de bug
- **docs** : Documentation uniquement
- **style** : Formatage, espaces, etc.
- **refactor** : Refactoring sans changement de comportement
- **test** : Ajout ou modification de tests
- **chore** : Tâches de maintenance

### Exemples

```bash
feat(lexer): ajoute support pour les commentaires
fix(parser): corrige crash sur expression vide
docs(readme): met à jour les instructions d'installation
test(interpreter): ajoute tests pour les variables string
```

##  Communauté et support

### Où obtenir de l'aide

- **Issues GitHub** : Pour les bugs et feature requests
- **Discussions GitHub** : Pour les questions générales
- **Email** : Pour les questions sensibles

### Canaux de communication

- **GitHub Issues** : Support principal
- **Pull Requests** : Reviews de code
- **GitHub Discussions** : Discussions générales

## 🎉 Reconnaissance

Tous les contributeurs seront reconnus dans :
- Le fichier `CONTRIBUTORS.md`
- Les notes de release
- Les commentaires de remerciement

## 📋 Checklist du contributeur

Avant de soumettre votre contribution :

- [ ] J'ai lu ce guide de contribution
- [ ] Mon code suit les standards du projet
- [ ] J'ai ajouté des tests pour mes changements
- [ ] Tous les tests passent (`make test`)
- [ ] J'ai formaté mon code (`make format`)
- [ ] J'ai mis à jour la documentation si nécessaire
- [ ] Mon commit suit les conventions de nommage
- [ ] J'ai testé mes changements manuellement

---

**Merci encore pour votre contribution au projet Pong Language Interpreter !** 🙏

Votre aide est précieuse pour faire de ce projet un outil encore plus utile pour la communauté.
