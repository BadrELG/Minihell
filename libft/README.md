# Libft - Bibliothèque C Personnalisée

## 📚 Description

Libft est une bibliothèque C qui recrée un ensemble de fonctions standard de la libc ainsi que d'autres fonctions utilitaires. Ce projet fait partie du cursus de l'école 42 et constitue une base fondamentale pour les projets futurs.

## 🛠️ Fonctions Implémentées

### Fonctions de la libc

#### Fonctions de test de caractères
- `ft_isalpha` : Teste si un caractère est alphabétique
- `ft_isdigit` : Teste si un caractère est un chiffre
- `ft_isalnum` : Teste si un caractère est alphanumérique
- `ft_isascii` : Teste si un caractère est dans la table ASCII
- `ft_isprint` : Teste si un caractère est imprimable
- `ft_toupper` : Convertit en majuscule
- `ft_tolower` : Convertit en minuscule

#### Fonctions de manipulation de chaînes
- `ft_strlen` : Calcule la longueur d'une chaîne
- `ft_strchr` : Recherche un caractère dans une chaîne
- `ft_strrchr` : Recherche un caractère depuis la fin d'une chaîne
- `ft_strncmp` : Compare deux chaînes
- `ft_strlcpy` : Copie une chaîne de manière sécurisée
- `ft_strlcat` : Concatène des chaînes de manière sécurisée
- `ft_strnstr` : Recherche une sous-chaîne
- `ft_strdup` : Duplique une chaîne

#### Fonctions de manipulation de mémoire
- `ft_memset` : Remplit une zone mémoire
- `ft_bzero` : Met à zéro une zone mémoire
- `ft_memcpy` : Copie une zone mémoire
- `ft_memmove` : Déplace une zone mémoire
- `ft_memchr` : Recherche un octet dans une zone mémoire
- `ft_memcmp` : Compare deux zones mémoire
- `ft_calloc` : Alloue et initialise une zone mémoire

#### Fonctions de conversion
- `ft_atoi` : Convertit une chaîne en entier
- `ft_itoa` : Convertit un entier en chaîne

#### Manipulation de chaînes
- `ft_substr` : Extrait une sous-chaîne
- `ft_strjoin` : Joint deux chaînes
- `ft_strtrim` : Supprime des caractères en début et fin de chaîne
- `ft_split` : Découpe une chaîne selon un délimiteur
- `ft_strmapi` : Applique une fonction à chaque caractère
- `ft_striteri` : Applique une fonction à chaque caractère avec index

#### Fonctions d'affichage
- `ft_putchar_fd` : Écrit un caractère
- `ft_putstr_fd` : Écrit une chaîne
- `ft_putendl_fd` : Écrit une chaîne suivie d'un retour à la ligne
- `ft_putnbr_fd` : Écrit un nombre

### Fonctions de Gestion de Listes Chaînées

- `ft_lstnew` : Crée un nouveau nœud
- `ft_lstadd_front` : Ajoute un nœud au début
- `ft_lstsize` : Compte le nombre de nœuds
- `ft_lstlast` : Retourne le dernier nœud
- `ft_lstadd_back` : Ajoute un nœud à la fin
- `ft_lstdelone` : Supprime un nœud
- `ft_lstclear` : Supprime et libère une liste
- `ft_lstiter` : Applique une fonction à chaque nœud
- `ft_lstmap` : Crée une nouvelle liste en appliquant une fonction

## Fonctions Supplémentaires

#### Printf
- `ft_printf` : Recréation de printf
- `ft_convert` : Fonctions de conversion pour printf
- `ft_2convert` : Fonctions de conversion supplémentaires

#### Get Next Line
- `get_next_line` : Lit une ligne depuis un descripteur de fichier
- `get_next_line_utils` : Fonctions utilitaires pour GNL

#### Garbage Collector
- `ft_malloc` : Wrapper pour malloc avec gestion d'erreur
- `ft_free` : Libération sécurisée de mémoire
- `ft_tab_free` : Libération de tableaux
- `garbage` : Système de gestion automatique de la mémoire

#### Utilitaires Avancés
- `ft_sort_int_tab` : Trie un tableau d'entiers par ordre croissant
- `ft_tabstr_free` : Libère un tableau de chaînes (char **) alloué dynamiquement
- `ft_atoi_safe` : Conversion chaîne vers entier avec détection d'overflow INT_MAX/INT_MIN

## 🚀 Compilation

```bash
make        # Compile la bibliothèque
make bonus  # Compile avec les fonctions bonus
make clean  # Supprime les fichiers objets
make fclean # Supprime les fichiers objets et la bibliothèque
make re     # Recompile la bibliothèque
```

## 📖 Utilisation

```c
#include "libft.h"

int main(void)
{
    char *str = ft_strdup("Hello, World!");
    ft_putendl_fd(str, 1);
    g_free(str);
    return (0);
}
```

## 🧪 Tests

La bibliothèque a été testée avec :
- Tests unitaires complets
- Valgrind pour la détection de fuites mémoire
- Norminette pour la conformité au style de code 42
- Tests de performance pour les fonctions critiques

## 📝 Normes de Codage

Le code suit les normes de l'école 42 :
- Fonctions de maximum 25 lignes
- Maximum 5 fonctions par fichier
- Déclaration des variables en début de fonction
- Pas de déclaration et d'affectation sur la même ligne
- Indentation cohérente

## ⚙️ Compatibilité

- macOS
- Linux
- Compilateur GCC ou Clang
- Norme C89

## 🔒 Protection

Toutes les fonctions incluent :
- Vérification des paramètres NULL
- Gestion des cas limites
- Protection contre les débordements
- Libération appropriée de la mémoire

## 📜 License

Ce projet est réalisé dans le cadre du cursus de l'école 42.
