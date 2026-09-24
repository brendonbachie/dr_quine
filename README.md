*This project has been created as part of the 42 curriculum by bgomes-b.*

# Dr Quine

## Descrição

Um *quine* é um programa que, ao ser executado, imprime o próprio código-fonte,
byte a byte, sem ler o arquivo de origem em disco — a única "cópia" do
código que ele pode usar é a que está armazenada dentro dele mesmo (tipicamente
uma string). Este projeto implementa três variações do exercício **Dr Quine**
do 42, cada uma em C e em Assembly (NASM, x86-64), além de uma pequena
biblioteca em Assembly (`libasm`) usada como exercício à parte.

As três variações, presentes tanto em `C/` quanto em `ASM/`:

- **Colleen** — o quine "clássico": imprime seu próprio código-fonte na saída
  padrão e termina.
- **Grace** — em vez de imprimir na tela, escreve o próprio código-fonte num
  arquivo novo (`Grace_kid.c` na versão C, `Grace_kid.s` na versão ASM).
- **Sully** — quine "geracional": a cada execução gera e compila uma nova
  versão de si mesmo com um contador decrescente. Na versão em C ele lê a
  variável `int i` embutida no início do arquivo, calcula `j = i - 1` (a
  menos que o arquivo `Sully_j.c` já exista, caso em que usa `i`), escreve
  `Sully_j.c`, compila com `gcc` e executa o binário resultante via `system()`.
  Se `j` for negativo o processo para. A versão em ASM segue a mesma lógica
  (contador em `num`, checagem de existência do arquivo com `access`, geração
  de `Sully_j.s`, montagem com `nasm`/`gcc` e execução com `system`).

## Estrutura do repositório

```
.
├── C/                  # Colleen, Grace e Sully em C
│   ├── Colleen.c
│   ├── Grace.c
│   ├── Sully.c
│   └── Makefile
├── ASM/                # Colleen, Grace e Sully em Assembly (NASM, elf64)
│   ├── Colleen.s
│   ├── Grace.s
│   ├── Sully.s
│   └── Makefile
├── libasm/             # biblioteca própria com funções da libc reescritas em ASM
│   ├── ft_strlen.s / ft_strcpy.s / ft_strcmp.s / ft_write.s / ft_read.s / ft_strdup.s
│   ├── main.c          # programa de teste (test_libasm)
│   └── Makefile
├── Makefile            # wrapper na raiz: chama make em C/ e ASM/
└── en.subject.pdf       # enunciado do exercício
```

## Como compilar e executar

### C e ASM (Colleen, Grace, Sully)

Na raiz do repositório, o `Makefile` apenas repassa o alvo para `C/` e `ASM/`:

```bash
make        # compila Colleen, Grace e Sully em C/ e em ASM/
make clean  # remove os .o
make fclean # remove binários e os arquivos gerados em runtime (Grace_kid.*, Sully_*)
make re     # fclean + all
```

Também é possível compilar cada implementação isoladamente entrando em `C/`
ou `ASM/` e rodando os mesmos alvos (`all`, `clean`, `fclean`, `re`) —
`C/Makefile` compila cada `.c` direto com `gcc -Wall -Wextra -Werror`, e
`ASM/Makefile` monta cada `.s` com `nasm -f elf64` e depois linka com `gcc`.

Depois de compilado, cada binário é executado diretamente:

```bash
./Colleen   # imprime o próprio código-fonte no stdout
./Grace     # escreve Grace_kid.c (ou Grace_kid.s) no diretório atual
./Sully     # gera e roda a próxima geração (Sully_4, depois Sully_3, ...)
```

### libasm

```bash
cd libasm
make        # gera libasm.a a partir dos .s
make test   # compila main.c linkando com -lasm e roda test_libasm
make clean  # remove os .o e o binário de teste
make fclean # clean + remove libasm.a
make re     # fclean + all
```

`test_libasm` compara, para cada função (`ft_strlen`, `ft_strcpy`, `ft_strcmp`,
`ft_write`, `ft_read`, `ft_strdup`), o resultado da implementação em Assembly
com o da função equivalente da libc, imprimindo `ok`/`FALHA` por caso.

## Como verificar um quine

A prova de que um programa é um quine é que sua saída seja **idêntica** ao
seu código-fonte. Isso pode ser conferido comparando a saída do binário com
o arquivo `.c`/`.s` que o originou:

```bash
# Colleen: a saída no stdout deve ser igual ao próprio fonte
diff <(./Colleen) Colleen.c && echo "é um quine"

# Grace: o arquivo gerado deve ser igual ao fonte original
./Grace
diff Grace_kid.c Grace.c && echo "é um quine"

# Sully: cada geração escrita em disco deve ser igual à geração anterior
./Sully
diff Sully_4.c Sully.c && echo "é um quine"
```

Um `diff` sem saída (status de saída `0`) confirma que os dois arquivos são
byte a byte idênticos, ou seja, que o programa reproduziu exatamente o
próprio código.

## Licença

MIT, see LICENSE.
