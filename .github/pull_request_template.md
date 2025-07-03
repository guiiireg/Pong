---
name: 🔄 Pull Request
about: Propose changes to the Pong interpreter
title: ""
labels: []
assignees: []
---

## 📝 Description

Décrivez clairement les changements apportés dans cette Pull Request.

## 🎯 Type de changement

- [ ] 🐛 Bug fix (changement qui corrige un problème)
- [ ] ✨ Nouvelle fonctionnalité (changement qui ajoute une fonctionnalité)
- [ ] 💥 Breaking change (changement qui casse la compatibilité)
- [ ] 📖 Documentation (amélioration de la documentation)
- [ ] 🎨 Style (formatage, espaces, etc. - pas de changement de code)
- [ ] ♻️ Refactoring (amélioration du code sans changer les fonctionnalités)
- [ ] ⚡ Performance (amélioration des performances)
- [ ] ✅ Tests (ajout ou modification de tests)
- [ ] 🔧 Outils (changements des outils de build, CI, etc.)

## 🔗 Issue liée

Ferme #(numéro de l'issue)

## 🧪 Tests

Décrivez les tests que vous avez effectués pour valider vos changements :

- [ ] `make test` - Tous les tests passent
- [ ] `make test-examples` - Les exemples fonctionnent
- [ ] Tests manuels réalisés :
  - [ ] Test 1 : ...
  - [ ] Test 2 : ...

## 📋 Checklist

### Code quality
- [ ] Mon code suit les conventions du projet
- [ ] J'ai effectué une auto-review de mon code
- [ ] J'ai commenté mon code, particulièrement les parties complexes
- [ ] Mes changements ne génèrent pas de nouveaux warnings
- [ ] J'ai utilisé `make format` pour formatter le code

### Tests
- [ ] J'ai ajouté des tests qui prouvent que ma correction fonctionne
- [ ] J'ai ajouté des tests qui prouvent que ma nouvelle fonctionnalité fonctionne
- [ ] Les tests nouveaux et existants passent avec mes changements
- [ ] Tous les exemples .pong continuent de fonctionner

### Documentation
- [ ] J'ai mis à jour la documentation si nécessaire
- [ ] J'ai ajouté des commentaires dans le code pour expliquer les changements
- [ ] J'ai mis à jour le CHANGELOG.md si applicable

## 🔍 Changements détaillés

### Fichiers modifiés
- `src/...` : Description des changements
- `include/...` : Description des changements  
- `tests/...` : Tests ajoutés/modifiés
- `examples/...` : Exemples ajoutés/modifiés

### Comportement avant/après
**Avant :**
```
Décrivez le comportement actuel
```

**Après :**
```
Décrivez le nouveau comportement
```

## 📄 Exemple d'usage (si applicable)

```pong
// Exemple de code .pong qui utilise les nouvelles fonctionnalités
int x = 5;
string message = "Hello World";
// ...
```

## 🖼️ Captures d'écran (si applicable)

Ajoutez des captures d'écran pour illustrer les changements visuels.

## 📋 Notes supplémentaires

Ajoutez toute note ou considération particulière pour les reviewers :
- Points d'attention spécifiques
- Compromis de design
- Dépendances nouvelles
- Impact sur les performances
- Considérations de compatibilité

---

**Reviewers :** Merci de vérifier particulièrement :
- [ ] La cohérence avec l'architecture existante
- [ ] La qualité des messages d'erreur  
- [ ] La gestion de la mémoire
- [ ] La performance des nouveaux algorithmes
- [ ] La couverture des cas d'erreur
