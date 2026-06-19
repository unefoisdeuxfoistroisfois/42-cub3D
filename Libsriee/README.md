# 📚 libsriee

**A comprehensive C utility library** featuring string manipulation, memory management, I/O functions, linked lists, get_next_line, and ft_printf implementations.

**Une bibliothèque utilitaire C complète** comprenant manipulation de chaînes, gestion mémoire, fonctions I/O, listes chaînées, get_next_line et ft_printf.

Built and maintained by **sriee**

---

## 🌐 Language / Langue

- [🇬🇧 English](#english)
- [🇫🇷 Français](#français)

---

<a name="english"></a>
# 🇬🇧 English

## ✨ Features

### Core Functions
- **Character validation**: `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`
- **String manipulation**: `ft_strlen`, `ft_strcmp`, `ft_strncmp`, `ft_strchr`, `ft_strjoin`, `ft_split`, `ft_substr`, `ft_strtrim`, and more
- **Memory operations**: `ft_memset`, `ft_memcpy`, `ft_memmove`, `ft_calloc`, `ft_free_split`
- **Type conversions**: `ft_atoi`, `ft_itoa`, `ft_toupper`, `ft_tolower`
- **File descriptor output**: `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`
- **Linked lists**: Complete toolkit (`ft_lstnew`, `ft_lstadd_back`, `ft_lstmap`, `ft_lstclear`, etc.)

### Advanced Features
- **get_next_line**: Line-by-line file reading with configurable buffer size
- **ft_printf**: Custom printf implementation supporting `%c`, `%s`, `%d`, `%i`, `%u`, `%x`, `%X`, `%p`, `%%`

---

## 📁 Project Structure
```
libsriee/
├── Makefile                 # Build configuration
├── README.md               # Documentation
├── .gitignore              # Git exclusions
├── Include/
│   └── libsriee.h          # Main header file
├── Src/
│   ├── String/             # String manipulation
│   ├── Memory/             # Memory operations & management
│   ├── Convert/            # Type conversions
│   ├── Check/              # Character validation
│   ├── Output/             # File descriptor output
│   ├── List/               # Linked list operations
│   ├── Gnl/                # get_next_line implementation
│   └── Printf/             # ft_printf implementation
└── Objs/                   # Compiled objects (auto-generated)
```

---

## 🚀 Quick Start

### Installation
```bash
# Clone the repository
git clone https://github.com/sriee94/libsriee.git
cd libsriee

# Compile the library
make

# Clean up (optional)
make clean      # Remove object files
make fclean     # Remove everything including libsriee.a
make re         # Recompile from scratch
```

### Integration
```bash
# Copy library to your project
cp libsriee.a /path/to/your/project/
cp Include/libsriee.h /path/to/your/project/

# Include in your C file
#include "libsriee.h"

# Compile with the library
cc -Wall -Wextra -Werror your_file.c -L. -lsriee -o your_program
```

---

## 💡 Usage Examples

### Basic String Operations
```c
#include "libsriee.h"

int main(void)
{
    char **words;
    
    // Split string
    words = ft_split("Hello World Programming", ' ');
    
    // Use split results
    ft_printf("First word: %s\n", words[0]);
    
    // Clean up
    ft_free_split(words);
    
    return (0);
}
```

### File Reading with get_next_line
```c
#include "libsriee.h"
#include <fcntl.h>

int main(void)
{
    int fd;
    char *line;
    
    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)))
    {
        ft_printf("%s", line);
        free(line);
    }
    close(fd);
    
    return (0);
}
```

### Using ft_printf
```c
#include "libsriee.h"

int main(void)
{
    int num = 42;
    char *str = "World";
    
    ft_printf("Hello %s!\n", str);
    ft_printf("Number: %d\n", num);
    ft_printf("Hex: %x\n", num);
    ft_printf("Pointer: %p\n", &num);
    
    return (0);
}
```

---

## 📖 Function Reference

### String Functions (15 functions)

| Function | Description |
|----------|-------------|
| `ft_strlen` | Calculate string length |
| `ft_strcmp` | Compare two strings |
| `ft_strncmp` | Compare strings (n bytes) |
| `ft_strchr` | Locate character in string |
| `ft_strrchr` | Locate character from end |
| `ft_strdup` | Duplicate a string |
| `ft_substr` | Extract substring |
| `ft_strjoin` | Concatenate two strings |
| `ft_strtrim` | Trim characters from string |
| `ft_split` | Split string by delimiter |
| `ft_strlcpy` | Size-bounded string copy |
| `ft_strlcat` | Size-bounded concatenation |
| `ft_strnstr` | Locate substring (n bytes) |
| `ft_strmapi` | Apply function to string |
| `ft_striteri` | Iterate over string with function |

### Memory Functions (8 functions)

| Function | Description |
|----------|-------------|
| `ft_memset` | Fill memory with constant byte |
| `ft_bzero` | Zero a byte string |
| `ft_memcpy` | Copy memory area |
| `ft_memmove` | Copy memory (handles overlap) |
| `ft_memchr` | Scan memory for character |
| `ft_memcmp` | Compare memory areas |
| `ft_calloc` | Allocate and zero memory |
| `ft_free_split` | Free split array |

### Conversion Functions (4 functions)

| Function | Description |
|----------|-------------|
| `ft_atoi` | String to integer |
| `ft_itoa` | Integer to string |
| `ft_toupper` | Convert to uppercase |
| `ft_tolower` | Convert to lowercase |

### Character Check Functions (5 functions)

| Function | Description |
|----------|-------------|
| `ft_isalpha` | Check if alphabetic |
| `ft_isdigit` | Check if digit |
| `ft_isalnum` | Check if alphanumeric |
| `ft_isascii` | Check if ASCII |
| `ft_isprint` | Check if printable |

### Output Functions (5 functions)

| Function | Description |
|----------|-------------|
| `ft_printf` | Formatted output to stdout |
| `get_next_line` | Read line from file descriptor |
| `ft_putchar_fd` | Output character to fd |
| `ft_putstr_fd` | Output string to fd |
| `ft_putendl_fd` | Output string + newline to fd |
| `ft_putnbr_fd` | Output number to fd |

### Linked List Functions (9 functions)

| Function | Description |
|----------|-------------|
| `ft_lstnew` | Create new list element |
| `ft_lstadd_front` | Add element at beginning |
| `ft_lstadd_back` | Add element at end |
| `ft_lstsize` | Count list elements |
| `ft_lstlast` | Get last element |
| `ft_lstdelone` | Delete one element |
| `ft_lstclear` | Delete all elements |
| `ft_lstiter` | Iterate with function |
| `ft_lstmap` | Map function to new list |

**Total: 51 functions**

*Complete prototypes in `Include/libsriee.h`*

---

## ⚙️ Configuration

### Modify BUFFER_SIZE for get_next_line

Edit `Include/libsriee.h` or compile with:
```bash
cc -D BUFFER_SIZE=1024 your_file.c -L. -lsriee
```

- **Default**: 42
- **Maximum**: 8,000,000

---

## 🎓 About

This library is a comprehensive C utility toolkit used across multiple projects including:

- ✅ **get_next_line**
- ✅ **ft_printf**
- ✅ **pipex**
- ✅ **minishell**
- ✅ **push_swap**
- 🚧 And more to come...

**Built with:**
- Clean code principles
- Memory safety
- Performance optimization
- Modularity and reusability

---

## 👤 Author

**sriee**  
[GitHub](https://github.com/sriee94) | Belgium - 2025

---

## 🔗 Related Projects

- [get_next_line](https://github.com/sriee94/get_next_line)
- [ft_printf](https://github.com/sriee94/ft_printf)
- [push_swap](https://github.com/sriee94/push_swap)
- [pipex](https://github.com/sriee94/pipex)

---

**⭐ If you find this useful, consider giving it a star!**

---
---

<a name="français"></a>
# 🇫🇷 Français

## ✨ Fonctionnalités

### Fonctions de base
- **Validation de caractères**: `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`
- **Manipulation de chaînes**: `ft_strlen`, `ft_strcmp`, `ft_strncmp`, `ft_strchr`, `ft_strjoin`, `ft_split`, `ft_substr`, `ft_strtrim`, et plus
- **Opérations mémoire**: `ft_memset`, `ft_memcpy`, `ft_memmove`, `ft_calloc`, `ft_free_split`
- **Conversions de types**: `ft_atoi`, `ft_itoa`, `ft_toupper`, `ft_tolower`
- **Sortie sur descripteur**: `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`
- **Listes chaînées**: Boîte à outils complète (`ft_lstnew`, `ft_lstadd_back`, `ft_lstmap`, `ft_lstclear`, etc.)

### Fonctionnalités avancées
- **get_next_line**: Lecture ligne par ligne avec buffer configurable
- **ft_printf**: Implémentation personnalisée supportant `%c`, `%s`, `%d`, `%i`, `%u`, `%x`, `%X`, `%p`, `%%`

---

## 📁 Structure du projet
```
libsriee/
├── Makefile                 # Configuration de compilation
├── README.md               # Documentation
├── .gitignore              # Exclusions Git
├── Include/
│   └── libsriee.h          # Fichier d'en-tête principal
├── Src/
│   ├── String/             # Manipulation de chaînes
│   ├── Memory/             # Opérations & gestion mémoire
│   ├── Convert/            # Conversions de types
│   ├── Check/              # Validation de caractères
│   ├── Output/             # Sortie sur descripteur
│   ├── List/               # Opérations sur listes chaînées
│   ├── Gnl/                # Implémentation get_next_line
│   └── Printf/             # Implémentation ft_printf
└── Objs/                   # Objets compilés (auto-généré)
```

---

## 🚀 Démarrage rapide

### Installation
```bash
# Cloner le dépôt
git clone https://github.com/sriee94/libsriee.git
cd libsriee

# Compiler la bibliothèque
make

# Nettoyage (optionnel)
make clean      # Supprimer les fichiers objets
make fclean     # Tout supprimer y compris libsriee.a
make re         # Recompiler depuis zéro
```

### Intégration
```bash
# Copier la bibliothèque dans votre projet
cp libsriee.a /chemin/vers/votre/projet/
cp Include/libsriee.h /chemin/vers/votre/projet/

# Inclure dans votre fichier C
#include "libsriee.h"

# Compiler avec la bibliothèque
cc -Wall -Wextra -Werror votre_fichier.c -L. -lsriee -o votre_programme
```

---

## 💡 Exemples d'utilisation

### Opérations sur chaînes
```c
#include "libsriee.h"

int main(void)
{
    char **mots;
    
    // Diviser une chaîne
    mots = ft_split("Bonjour Monde Programmation", ' ');
    
    // Utiliser les résultats
    ft_printf("Premier mot: %s\n", mots[0]);
    
    // Nettoyage
    ft_free_split(mots);
    
    return (0);
}
```

### Lecture de fichier avec get_next_line
```c
#include "libsriee.h"
#include <fcntl.h>

int main(void)
{
    int fd;
    char *ligne;
    
    fd = open("fichier.txt", O_RDONLY);
    while ((ligne = get_next_line(fd)))
    {
        ft_printf("%s", ligne);
        free(ligne);
    }
    close(fd);
    
    return (0);
}
```

### Utilisation de ft_printf
```c
#include "libsriee.h"

int main(void)
{
    int num = 42;
    char *str = "Monde";
    
    ft_printf("Bonjour %s!\n", str);
    ft_printf("Nombre: %d\n", num);
    ft_printf("Hex: %x\n", num);
    ft_printf("Pointeur: %p\n", &num);
    
    return (0);
}
```

---

## 📖 Référence des fonctions

### Fonctions de chaînes (15 fonctions)

| Fonction | Description |
|----------|-------------|
| `ft_strlen` | Calculer la longueur d'une chaîne |
| `ft_strcmp` | Comparer deux chaînes |
| `ft_strncmp` | Comparer des chaînes (n octets) |
| `ft_strchr` | Localiser un caractère |
| `ft_strrchr` | Localiser depuis la fin |
| `ft_strdup` | Dupliquer une chaîne |
| `ft_substr` | Extraire une sous-chaîne |
| `ft_strjoin` | Concaténer deux chaînes |
| `ft_strtrim` | Enlever des caractères |
| `ft_split` | Diviser par délimiteur |
| `ft_strlcpy` | Copie limitée en taille |
| `ft_strlcat` | Concaténation limitée |
| `ft_strnstr` | Localiser une sous-chaîne (n octets) |
| `ft_strmapi` | Appliquer une fonction |
| `ft_striteri` | Itérer avec fonction |

### Fonctions mémoire (8 fonctions)

| Fonction | Description |
|----------|-------------|
| `ft_memset` | Remplir la mémoire |
| `ft_bzero` | Mettre à zéro |
| `ft_memcpy` | Copier la mémoire |
| `ft_memmove` | Copier (gère chevauchements) |
| `ft_memchr` | Rechercher un caractère |
| `ft_memcmp` | Comparer des zones |
| `ft_calloc` | Allouer et initialiser |
| `ft_free_split` | Libérer un tableau split |

### Fonctions de conversion (4 fonctions)

| Fonction | Description |
|----------|-------------|
| `ft_atoi` | Chaîne vers entier |
| `ft_itoa` | Entier vers chaîne |
| `ft_toupper` | Vers majuscule |
| `ft_tolower` | Vers minuscule |

### Fonctions de vérification (5 fonctions)

| Fonction | Description |
|----------|-------------|
| `ft_isalpha` | Vérifier si alphabétique |
| `ft_isdigit` | Vérifier si chiffre |
| `ft_isalnum` | Vérifier si alphanumérique |
| `ft_isascii` | Vérifier si ASCII |
| `ft_isprint` | Vérifier si imprimable |

### Fonctions de sortie (5 fonctions)

| Fonction | Description |
|----------|-------------|
| `ft_printf` | Sortie formatée |
| `get_next_line` | Lire une ligne |
| `ft_putchar_fd` | Afficher un caractère |
| `ft_putstr_fd` | Afficher une chaîne |
| `ft_putendl_fd` | Afficher avec retour ligne |
| `ft_putnbr_fd` | Afficher un nombre |

### Fonctions de listes (9 fonctions)

| Fonction | Description |
|----------|-------------|
| `ft_lstnew` | Créer un élément |
| `ft_lstadd_front` | Ajouter au début |
| `ft_lstadd_back` | Ajouter à la fin |
| `ft_lstsize` | Compter les éléments |
| `ft_lstlast` | Obtenir le dernier |
| `ft_lstdelone` | Supprimer un élément |
| `ft_lstclear` | Supprimer tous |
| `ft_lstiter` | Itérer avec fonction |
| `ft_lstmap` | Mapper vers nouvelle liste |

**Total: 51 fonctions**

*Prototypes complets dans `Include/libsriee.h`*

---

## ⚙️ Configuration

### Modifier BUFFER_SIZE pour get_next_line

Éditez `Include/libsriee.h` ou compilez avec:
```bash
cc -D BUFFER_SIZE=1024 votre_fichier.c -L. -lsriee
```

- **Défaut**: 42
- **Maximum**: 8 000 000

---

## 🎓 À propos

Cette bibliothèque est une boîte à outils utilitaire C complète utilisée dans plusieurs projets:

- ✅ **get_next_line**
- ✅ **ft_printf**
- ✅ **pipex**
- ✅ **minishell**
- ✅ **push_swap**
- 🚧 Et d'autres à venir...

**Construite avec:**
- Principes de code propre
- Sécurité mémoire
- Optimisation des performances
- Modularité et réutilisabilité

---

## 👤 Auteur

**sriee**  
[GitHub](https://github.com/sriee94) | Belgique - 2025

---

## 🔗 Projets liés

- [get_next_line](https://github.com/sriee94/get_next_line)
- [ft_printf](https://github.com/sriee94/ft_printf)
- [push_swap](https://github.com/sriee94/push_swap)
- [pipex](https://github.com/sriee94/pipex)

---

**⭐ Si vous trouvez cela utile, pensez à mettre une étoile!**
