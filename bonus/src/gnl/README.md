*This project has been created as part of the 42 curriculum by ljanuari.*

# get_next_line

## Description

`get_next_line` é uma função em C que lê e devolve, uma de cada vez, as linhas
de um file descriptor, através de chamadas sucessivas. O objectivo principal
do projecto é compreender e aplicar o conceito de **variável estática** em C:
como guardar estado entre chamadas de uma função sem recorrer a variáveis
globais (proibidas pelo subject), de forma a "lembrar" o que já foi lido de
cada fd entre uma chamada e a seguinte.

A função lê o mínimo possível de cada vez (por blocos de `BUFFER_SIZE` bytes)
em vez de ler o ficheiro inteiro de uma vez, e devolve a linha completa
assim que encontra um `\n`, guardando o resto do buffer para a próxima
chamada.

- **Parte obrigatória**: lê de **um único fd de cada vez** (o comportamento
  com múltiplos fds intercalados é indefinido).
- **Parte bónus**: gere **vários fds em simultâneo**, mantendo o estado de
  leitura de cada um de forma independente, mesmo intercalando chamadas
  (ex: fd 3, depois fd 4, depois fd 3 outra vez).

## Instructions

### Compilação

Os ficheiros devem ficar na raiz do repositório e são compilados directamente
com `cc`, sem Makefile, exactamente como o subject pede:

```sh
# Parte obrigatória
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl

# Parte bónus
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

O `BUFFER_SIZE` pode ser omitido; nesse caso assume o valor por omissão
definido no header (`256`). O projecto compila corrctamente com qualquer
valor de `BUFFER_SIZE`, incluindo valores extremos (`1`, `9999`,
`10000000`, etc.), porque a lógica nunca assume que uma linha cabe num
único buffer.

### Uso

```c
#include "get_next_line.h"

int main(void)
{
	int		fd;
	char	*line;

	fd = open("ficheiro.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
```

Funciona tanto com ficheiros regulares como com a standard input (`fd 0`).

## Resources

- `man 2 read`, `man 3 malloc` — comportamento e valores de retorno usados
  como base da lógica de leitura.
- Stackoverflow e artigos genéricos sobre `get_next_line` — usados apenas no
  arranque do projecto, para ter uma primeira noção de que tipo de estrutura
  de dados costuma ser usada para guardar o estado entre chamadas (buffer
  estático, struct auxiliar, lista ligada para múltiplos fds). Nenhum código
  foi copiado desses sites; serviram só de ponto de partida para a minha
  própria implementação.
- Documentação sobre `static` em C — para perceber o ciclo de vida da
  variável estática e porque é que ela é a chave para "lembrar" o estado
  entre chamadas sem variáveis globais.

### Uso de IA

Usei o Claude (Anthropic) exclusivamente como apoio de **debugging**, nunca
para gerar ou copiar a solução do projecto. Especificamente:

- Ajuda a interpretar comportamentos inesperados (segfaults, leituras
  incompletas, linhas duplicadas ou truncadas) apontando onde no meu código
  o estado estava a ser corrompido, sem me dar a correcção directamente.
- Discussão sobre casos de borda a testar (ficheiro sem `\n` final,
  `BUFFER_SIZE` muito pequeno ou muito grande, leitura de `stdin`,
  intercalação de fds na parte bónus) para eu próprio construir os testes.
- Revisão da conformidade com a Norm (declaração de variáveis, número de
  linhas por função, etc.) depois de eu já ter o código funcional.

## Algoritmo e estrutura de dados

Um ponto importante deste projecto é que, apesar de a parte obrigatória e a
parte bónus terem exactamente a mesma assinatura e o mesmo comportamento
externo, **os algoritmos por trás são significativamente diferentes** um do
outro — não é a mesma lógica com um "extra" por cima, são duas abordagens
distintas ao mesmo problema.

### Parte obrigatória — um único buffer estático global à função

```c
typedef struct v_aux
{
	int			save;
	int			readt;
	char		*line;
	int			i;
}	t_helper;
```

Aqui existe **apenas um** `static char buffer[BUFFER_SIZE + 1]` dentro da
própria `get_next_line`, partilhado por todas as chamadas. A struct
`t_helper` não é estática — é local a cada chamada e serve apenas para
transportar o estado de trabalho (linha em construção, tamanho alocado,
posição actual) entre as funções auxiliares durante essa chamada.

Fluxo:
1. `remember` procura no buffer estático (o que sobrou da leitura anterior)
   se já existe um `\n`. Se existir, a linha é extraída logo dali, sem sequer
   chamar `read`.
2. Caso contrário, entra-se num ciclo que lê `BUFFER_SIZE` bytes de cada vez
   com `read`, e `ft_strllcat` vai concatenando esses bytes à linha (com
   `ft_realloc` a duplicar a capacidade sempre que necessário), até encontrar
   um `\n` ou o `read` devolver `0`/`-1`.
3. `buffer_move` desloca para o início do buffer estático o que sobrou depois
   do `\n`, para a próxima chamada continuar dali.

Como só existe **um** buffer estático (associado à função, não a um fd
específico), esta implementação só é segura com **um fd de cada vez**: se se
intercalar leitura de dois fds diferentes, o conteúdo de um pisa o do outro.
Isto está de acordo com o que o subject permite como comportamento indefinido
para a parte obrigatória.

### Parte bónus — lista ligada de buffers, um nó por fd

```c
typedef struct s_list
{
	struct s_list	*next;
	int				save;
	int				i;
	int				fd;
	char			buffer[BUFFER_SIZE + 1];
}	t_list;
```

Aqui a única variável estática é um **ponteiro para o topo de uma lista
ligada** (`static t_list *heap`), o que respeita a exigência do bónus de usar
"apenas uma variável estática". Cada nó da lista guarda o seu próprio
`buffer`, o seu próprio índice de posição (`i`) e o `fd` a que pertence.

Fluxo:
1. `check` percorre a lista à procura de um nó com o `fd` pedido.
2. Se não existir, `div1`/`remember` criam um nó novo e adicionam-no ao fim
   da lista — o resto do trabalho é feito exactamente sobre o buffer *desse*
   nó, nunca sobre um buffer partilhado.
3. `buffer_move` e `ft_realloc` funcionam de forma equivalente à versão
   obrigatória, mas sempre a operar sobre o buffer isolado do nó
   correspondente ao fd actual.
4. Quando um fd chega ao fim (`read` devolve `0`), `ft_lstremove` retira o nó
   correspondente da lista, libertando a memória.

Por causa disto, é possível intercalar chamadas a fds diferentes (3, 4, 5, 3,
4, ...) sem que o estado de leitura de um interfira no de outro — cada fd tem
o seu próprio "bloco de memória" persistente entre chamadas, indexado pela
lista ligada.

### Porquê duas abordagens distintas

A opção por uma lista ligada na bónus (em vez de, por exemplo, um array fixo
de buffers) foi deliberada: não há um limite conhecido de antemão para o
número de fds que a função pode ter de gerir ao mesmo tempo, e a lista
ligada permite alocar um nó por fd apenas quando esse fd é usado pela
primeira vez, sem desperdiçar memória com fds que nunca chegam a ser lidos.
Já na parte obrigatória, como só é preciso suportar um fd de cada vez, um
único buffer estático simples é suficiente e mais direto — não haveria
vantagem em complicar essa versão com uma lista.
