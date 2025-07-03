# Security Policy

## Supported Versions

Ce tableau indique les versions du Pong Language Interpreter qui reçoivent des mises à jour de sécurité :

| Version | Supportée          |
| ------- | ------------------ |
| 1.0.x   | :white_check_mark: |
| < 1.0   | :x:                |

## Reporting a Vulnerability

### 🔒 Signaler une vulnérabilité de sécurité

Si vous découvrez une vulnérabilité de sécurité dans le Pong Language Interpreter, merci de la signaler de manière responsable :

#### ⚡ Processus de signalement

1. **NE PAS** créer d'issue publique GitHub pour les problèmes de sécurité
2. **Envoyez** un email à : `security@example.com` (remplacez par votre vraie adresse)
3. **Incluez** le maximum d'informations pour nous aider à comprendre et reproduire le problème

#### 📋 Informations à inclure

- **Description** détaillée de la vulnérabilité
- **Étapes** pour reproduire le problème
- **Impact** potentiel de la vulnérabilité
- **Version** affectée du logiciel
- **Environnement** système (OS, compilateur, etc.)
- **Preuve de concept** (si applicable et sûre)

#### 🔍 Exemples de vulnérabilités à signaler

- **Buffer overflows** dans le parsing
- **Injection de code** via les fichiers .pong
- **Accès mémoire** non autorisé
- **Escalade de privilèges**
- **Déni de service** (DoS) exploitable
- **Fuites d'informations** sensibles

#### ⏰ Délais de réponse

- **24 heures** : Accusé de réception de votre rapport
- **72 heures** : Évaluation initiale et classification
- **7 jours** : Plan de correction et timeline
- **30 jours** : Publication du correctif (si possible)

#### 🛡️ Politique de divulgation responsable

Nous demandons que vous :

- **Nous donniez** un délai raisonnable pour corriger le problème avant toute divulgation publique
- **Ne pas exploitiez** la vulnérabilité à des fins malveillantes
- **N'accédiez pas** ou ne modifiez pas les données d'autres utilisateurs
- **Respectiez** la confidentialité des utilisateurs

En retour, nous nous engageons à :

- **Répondre rapidement** à votre rapport
- **Vous tenir informé** du progrès de la correction
- **Vous créditer** publiquement (si vous le souhaitez) une fois le problème résolu
- **Ne pas engager** de poursuites légales si vous respectez cette politique

#### 🎖️ Hall of Fame

Nous maintiendrons une liste des chercheurs en sécurité qui ont contribué à améliorer la sécurité du projet :

- *Votre nom pourrait être ici !*

#### ✅ Scope de sécurité

**Dans le scope :**
- Code source de l'interpréteur (`src/`, `include/`)
- Parsing des fichiers .pong
- Gestion mémoire
- Messages d'erreur révélant des informations sensibles

**Hors scope :**
- Attaques nécessitant un accès physique à la machine
- Déni de service nécessitant des ressources excessives (par design)
- Vulnérabilités dans les dépendances tierces (signalez-les directement aux projets concernés)

#### 🔧 Conseils pour les développeurs

Si vous contribuez au projet, voici quelques bonnes pratiques de sécurité :

##### Validation des entrées
```c
// ✅ Bon : validation des paramètres
int parse_expression(const char *input, Expression **result) {
    if (input == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }
    // ... suite du code ...
}

// ❌ Mauvais : pas de validation
int parse_expression(const char *input, Expression **result) {
    *result = malloc(sizeof(Expression));
    strcpy((*result)->value, input); // Risque de buffer overflow
}
```

##### Gestion mémoire
```c
// ✅ Bon : vérification des allocations
char *buffer = malloc(size);
if (buffer == NULL) {
    return ERROR_MEMORY_ALLOCATION;
}

// ✅ Bon : libération systématique
void cleanup_tokens(Token *tokens, int count) {
    if (tokens == NULL) return;
    
    for (int i = 0; i < count; i++) {
        free(tokens[i].value);
    }
    free(tokens);
}
```

##### Fonctions sécurisées
```c
// ✅ Préférez les fonctions sécurisées
strncpy(dest, src, sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';

snprintf(buffer, sizeof(buffer), "Value: %d", value);

// ❌ Évitez les fonctions dangereuses
strcpy(dest, src);  // Risque de buffer overflow
sprintf(buffer, "Value: %d", value);  // Risque de buffer overflow
```

#### 📚 Ressources de sécurité

- [OWASP Secure Coding Practices](https://owasp.org/www-project-secure-coding-practices-quick-reference-guide/)
- [CWE - Common Weakness Enumeration](https://cwe.mitre.org/)
- [CERT C Coding Standard](https://wiki.sei.cmu.edu/confluence/display/c/SEI+CERT+C+Coding+Standard)

#### 🔄 Mises à jour de cette politique

Cette politique de sécurité peut être mise à jour pour refléter les changements dans le projet ou les meilleures pratiques de sécurité. Consultez régulièrement cette page pour les dernières informations.

---

**Dernière mise à jour :** 2025-01-03
