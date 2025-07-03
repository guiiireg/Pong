#!/bin/bash

# ============================================================================
# Pong Language Interpreter - Initial GitHub Setup
# ============================================================================
# 
# Ce script automatise la configuration initiale du repository GitHub
# selon les instructions fournies par GitHub pour un nouveau repository.
# 
# Usage: ./setup-github.sh
# 
# ============================================================================

echo "🚀 Configuration initiale du repository GitHub"
echo "=============================================="
echo ""

# Vérifier que nous sommes dans le bon répertoire
if [ ! -f "Makefile" ] || [ ! -d "src" ]; then
    echo "❌ Erreur: Ce script doit être exécuté depuis le répertoire racine du projet Pong"
    exit 1
fi

# Vérifier que Git est initialisé
if [ ! -d ".git" ]; then
    echo "📝 Initialisation de Git..."
    git init
    git branch -M main
fi

# Vérifier le statut Git
echo "📊 Statut du repository:"
if [ -d ".git" ]; then
    echo "Branch: $(git branch --show-current 2>/dev/null || echo 'Not on any branch')"
    echo "Remote: $(git remote get-url origin 2>/dev/null || echo 'No remote configured')"
    echo ""
    echo "Status:"
    git status --short
else
    echo "Git repository not initialized"
fi
echo ""

# Construire le projet pour vérifier que tout fonctionne
echo "🔨 Construction du projet..."
make build
if [ $? -ne 0 ]; then
    echo "❌ Erreur lors de la construction. Veuillez corriger les erreurs avant de continuer."
    exit 1
fi
echo "✅ Construction réussie"
echo ""

# Tests
echo "🧪 Exécution des tests..."
make test
if [ $? -ne 0 ]; then
    echo "❌ Erreur lors des tests. Veuillez corriger les erreurs avant de continuer."
    exit 1
fi
echo "✅ Tests réussis"
echo ""

# Push vers GitHub
echo "📤 Push vers GitHub..."
echo "Repository: https://github.com/guiiireg/Pong.git"
echo ""

read -p "Voulez-vous pousser vers GitHub maintenant? (y/N): " -n 1 -r
echo ""

if [[ $REPLY =~ ^[Yy]$ ]]; then
    echo "Pushing to GitHub..."
    git push -u origin main
    
    if [ $? -eq 0 ]; then
        echo ""
        echo "🎉 Configuration réussie!"
        echo "✅ Le repository Pong est maintenant disponible sur:"
        echo "   https://github.com/guiiireg/Pong"
        echo ""
        echo "🔗 Liens utiles:"
        echo "   - Repository: https://github.com/guiiireg/Pong"
        echo "   - Issues: https://github.com/guiiireg/Pong/issues"
        echo "   - Wiki: https://github.com/guiiireg/Pong/wiki"
        echo ""
        echo "📚 Prochaines étapes:"
        echo "   - Ajouter des collaborateurs: make help"
        echo "   - Créer des issues pour les fonctionnalités futures"
        echo "   - Configurer les branches de protection"
        echo "   - Ajouter des workflows GitHub Actions"
    else
        echo "❌ Erreur lors du push. Vérifiez vos droits d'accès au repository."
        echo "💡 Assurez-vous d'avoir:"
        echo "   - Créé le repository sur GitHub"
        echo "   - Configuré votre clé SSH ou token d'accès"
        echo "   - Les droits d'écriture sur le repository"
    fi
else
    echo "⏸️  Push annulé. Vous pouvez le faire plus tard avec:"
    echo "   git push -u origin main"
    echo "   ou: make git-push"
fi

echo ""
echo "🏁 Configuration terminée!"
