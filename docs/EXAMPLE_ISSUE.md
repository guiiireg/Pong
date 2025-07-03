# Exemple d'Issue de Bug Report

Ce fichier montre un exemple de ce à quoi ressemblerait une issue créée avec notre template de bug report.

---

## 🐛 Bug Report

**Titre :** [BUG] L'interpréteur crash avec des caractères spéciaux dans les strings

### 📝 Description du bug

L'interpréteur Pong plante quand il rencontre des caractères spéciaux ou accentués dans les chaînes de caractères. Le programme se termine brutalement avec une erreur de segmentation.

### 🔄 Étapes pour reproduire

1. Compilez l'interpréteur avec `make build`
2. Créez un fichier test.pong avec le contenu suivant :
   ```pong
   string message = "Voici des accents: éàü";
   ```
3. Exécutez `./build/bin/pong-interpreter test.pong`
4. Observez le crash

### ✅ Comportement attendu

L'interpréteur devrait traiter correctement les caractères spéciaux et accentués dans les strings, et afficher ou stocker la valeur sans erreur.

### ❌ Comportement observé

L'interpréteur plante avec une erreur de segmentation (segfault) dès qu'il rencontre des caractères non-ASCII dans une string.

### 📄 Code .pong problématique

```pong
string simple = "hello";  // ✅ Fonctionne
string accents = "éàü";   // ❌ Cause un crash
string emoji = "🎉";      // ❌ Cause probablement un crash aussi
```

### 📋 Logs et messages d'erreur

```bash
$ ./build/bin/pong-interpreter test.pong
Parsing file: test.pong
Tokenizing...
Segmentation fault (core dumped)
```

Avec GDB :
```bash
$ gdb ./build/bin/pong-interpreter
(gdb) run test.pong
Starting program: ./build/bin/pong-interpreter test.pong

Program received signal SIGSEGV, Segmentation fault.
0x0000555555556789 in lexer_parse_string (lexer=0x555555559260, token=0x7fffffffe100) at src/lexer.c:145
145         while (*current != '"' && *current != '\0') {
(gdb) bt
#0  0x0000555555556789 in lexer_parse_string (lexer=0x555555559260, token=0x7fffffffe100) at src/lexer.c:145
#1  0x0000555555556890 in lexer_next_token (lexer=0x555555559260) at src/lexer.c:89
#2  0x0000555555557123 in parser_parse_declaration (parser=0x555555559300) at src/parser.c:67
#3  0x0000555555557456 in main (argc=2, argv=0x7fffffffe2a8) at src/main.c:45
```

### 🏷️ Version

Version 1.0.0 (latest)

### 💻 Système d'exploitation

Linux (Ubuntu/Debian) - Ubuntu 22.04 LTS

### 🔧 Version du compilateur

```bash
$ gcc --version
gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
Copyright (C) 2021 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

### ✔️ Tests effectués

- [x] J'ai essayé `make clean && make build`
- [x] J'ai testé avec d'autres fichiers .pong (les simples fonctionnent)
- [x] J'ai vérifié que les exemples de base fonctionnent
- [x] J'ai consulté la documentation

### 🔍 Contexte additionnel

- Le problème semble lié à l'encodage UTF-8 dans le lexer
- Cela affecte probablement tous les caractères non-ASCII
- Ça pourrait être un problème de longueur de bytes vs longueur de caractères
- Le code fonctionne parfaitement avec des strings ASCII simples
- Testé sur un système avec locale fr_FR.UTF-8

---

## Labels automatiques

- `bug` 
- `triage`
- `lexer` (composant affecté)
- `utf8` (technologie liée)
- `high-priority` (suggéré car crash)

## Assignation

- Assigné automatiquement à @guiiireg

## Actions suggérées

1. **Investigation** : Examiner le code de parsing des strings dans `src/lexer.c`
2. **Reproduction** : Confirmer le bug avec différents caractères spéciaux  
3. **Correction** : Implémenter un support UTF-8 approprié
4. **Tests** : Ajouter des tests pour les caractères spéciaux
5. **Documentation** : Mettre à jour la doc sur le support Unicode
