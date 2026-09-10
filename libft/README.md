*Este projeto foi criado como parte do currículo 42 por ljanuari.*

# Libft

## Descrição
A **Libft** é o primeiro projeto do currículo da escola 42. O objetivo é recriar funções da biblioteca padrão C (`libc`), além de funções utilitárias e manipulação de listas encadeadas, servindo como base para futuros projetos.

---

## Instruções

### Compilação
* `make`: Compila a biblioteca e gera `libft.a`.
* `make clean`: Remove arquivos de objeto (`.o`).
* `make fclean`: Remove objetos e o arquivo `libft.a`.
* `make re`: Recompila tudo do zero.

### Utilização
Inclua o cabeçalho no seu código:
```c
#include "libft.h"
```
E compile ligando a biblioteca:
```bash
cc -Wall -Wextra -Werror seu_programa.c libft.a -o seu_programa
```

---

## Descrição Detalhada da Biblioteca

* **Funções da Libc (`ft_`):** Verificações (`isalpha`, `isdigit`, etc.), manipulação de strings/memória (`strlen`, `memset`, `memcpy`, `strlcpy`, `strlcat`, `strncmp`, `atoi`, etc.) e alocação (`calloc`, `strdup`).
* **Funções Adicionais:** `substr`, `strjoin`, `strtrim`, `split`, `itoa`, `strmapi`, `striteri`, e funções `_fd` de output.
* **Listas Encadeadas:** `lstnew`, `lstadd_front`, `lstsize`, `lstlast`, `lstadd_back`, `lstdelone`, `lstclear`, `lstiter`, `lstmap`.

---

## Recursos

### Referências
* Manpages oficiais do C (`man 3`).
* www.ibm.com/

### Uso de Inteligência Artificial
A Inteligência Artificial foi utilizada estritamente para me ajudar a conhecer a prototipagem das funções sem prototipagem e conhecer ou aprofuncar o conhecimento sobre as funcoes originais. Em nenhum momento copiei código gerado por IA.
