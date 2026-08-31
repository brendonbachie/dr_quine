/*
** Programa de teste da libasm.
**
** Cada funcao escrita em assembly e comparada com a equivalente da libc,
** de forma que o teste se valide sozinho em vez de depender de eu conferir
** os numeros no olho.
**
**   cc -Wall -Wextra -Werror main.c -L. -lasm -o test_libasm
*/

#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dst, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t	ft_write(int fd, const void *buf, size_t count);
ssize_t	ft_read(int fd, void *buf, size_t count);
char	*ft_strdup(const char *s);

#define VERDE	"\033[32m"
#define VERMELHO "\033[31m"
#define NEGRITO	"\033[1m"
#define RESET	"\033[0m"

static int	g_falhas = 0;

/*
** Imprime o resultado de uma verificacao e contabiliza as falhas.
*/
static void	verifica(int passou, const char *fmt, ...)
{
	va_list	args;

	if (passou)
		printf("  " VERDE "ok   " RESET " ");
	else
	{
		printf("  " VERMELHO "FALHA" RESET " ");
		g_falhas++;
	}
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf("\n");
}

static void	titulo(const char *nome)
{
	printf("\n" NEGRITO "== %s ==" RESET "\n", nome);
}

/*
** O padrao C so garante o SINAL do retorno de strcmp, nao o valor exato,
** entao e o sinal que comparamos.
*/
static int	sinal(int valor)
{
	if (valor > 0)
		return (1);
	if (valor < 0)
		return (-1);
	return (0);
}

static void	testa_strlen(void)
{
	const char	*casos[] = {
		"",
		"a",
		"Hello, World!",
		"   com espacos   ",
		"acentuado: cafe com pao",
		"uma string longa o bastante para varias iteracoes do loop, com 80+ bytes no total",
		NULL
	};
	const char	*frase = "Hello, World!";
	int			i;

	titulo("ft_strlen");
	i = 0;
	while (casos[i])
	{
		verifica(ft_strlen(casos[i]) == strlen(casos[i]),
			"\"%.25s\" -> minha %zu, libc %zu",
			casos[i], ft_strlen(casos[i]), strlen(casos[i]));
		i++;
	}
	verifica(ft_strlen(frase + 7) == strlen(frase + 7),
		"ponteiro no meio da string (frase + 7) -> %zu", ft_strlen(frase + 7));
}

static void	testa_strcpy(void)
{
	const char	*origem = "Hello, World!";
	char		meu[64];
	char		libc[64];
	char		*retorno;

	titulo("ft_strcpy");
	memset(meu, '#', sizeof(meu));
	memset(libc, '#', sizeof(libc));
	retorno = ft_strcpy(meu, origem);
	strcpy(libc, origem);
	verifica(strcmp(meu, libc) == 0, "copiou \"%s\"", meu);
	verifica(retorno == meu, "devolveu o ponteiro do destino");
	verifica(meu[strlen(origem)] == '\0', "copiou o terminador junto");
	verifica(meu[strlen(origem) + 1] == '#',
		"nao escreveu alem do terminador");
	memset(meu, '#', sizeof(meu));
	ft_strcpy(meu, "");
	verifica(meu[0] == '\0' && meu[1] == '#',
		"string vazia gera destino com apenas o terminador");
}

static void	testa_strcmp(void)
{
	const char	*pares[][2] = {
		{"abc", "abc"},
		{"", ""},
		{"", "a"},
		{"a", ""},
		{"abc", "abd"},
		{"abd", "abc"},
		{"abc", "abcd"},
		{"Hello", "hello"},
		{"\x7f", "\x80"},
		{"\xff", "\x01"},
		{NULL, NULL}
	};
	int			i;

	titulo("ft_strcmp");
	i = 0;
	while (pares[i][0])
	{
		verifica(sinal(ft_strcmp(pares[i][0], pares[i][1]))
			== sinal(strcmp(pares[i][0], pares[i][1])),
			"cmp(\"%s\", \"%s\") -> minha %d, libc %d",
			pares[i][0], pares[i][1],
			ft_strcmp(pares[i][0], pares[i][1]),
			strcmp(pares[i][0], pares[i][1]));
		i++;
	}
	printf("       (os dois ultimos usam bytes acima de 127: o padrao manda\n");
	printf("        comparar como unsigned char, entao o sinal tem que bater)\n");
}

static void	testa_write(void)
{
	const char	*msg = "       esta linha foi impressa pelo meu ft_write\n";
	size_t		tamanho;
	ssize_t		devolvido;
	int			errno_meu;
	int			errno_libc;

	titulo("ft_write");
	tamanho = strlen(msg);
	/*
	** printf passa pelo buffer da stdio, mas ft_write vai direto ao fd 1.
	** Sem o flush, a linha abaixo apareceria fora de ordem na saida.
	*/
	fflush(stdout);
	devolvido = ft_write(1, msg, tamanho);
	verifica(devolvido == (ssize_t)tamanho,
		"escreveu %zd de %zu bytes em stdout", devolvido, tamanho);
	verifica(ft_write(1, "", 0) == 0, "escrita de 0 bytes devolve 0");
	errno = 0;
	devolvido = ft_write(-1, "x", 1);
	errno_meu = errno;
	errno = 0;
	if (write(-1, "x", 1) == -1)
		errno_libc = errno;
	else
		errno_libc = 0;
	verifica(devolvido == -1 && errno_meu == errno_libc,
		"fd invalido -> retorno %zd, errno %d (%s)",
		devolvido, errno_meu, strerror(errno_meu));
}

static void	testa_read(void)
{
	const char	*conteudo = "Hello, World!";
	const char	*arquivo = "teste_read.tmp";
	char		buffer[64];
	int			fd;
	ssize_t		devolvido;

	titulo("ft_read");
	fd = open(arquivo, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0 || write(fd, conteudo, strlen(conteudo)) < 0)
		return ((void)printf("  nao consegui criar o arquivo de teste\n"));
	close(fd);
	fd = open(arquivo, O_RDONLY);
	memset(buffer, 0, sizeof(buffer));
	devolvido = ft_read(fd, buffer, strlen(conteudo));
	verifica(devolvido == (ssize_t)strlen(conteudo)
		&& strcmp(buffer, conteudo) == 0,
		"leu %zd bytes: \"%s\"", devolvido, buffer);
	devolvido = ft_read(fd, buffer, 10);
	verifica(devolvido == 0, "fim de arquivo devolve %zd (0, nao -1)",
		devolvido);
	close(fd);
	unlink(arquivo);
	errno = 0;
	devolvido = ft_read(-1, buffer, 1);
	verifica(devolvido == -1 && errno == EBADF,
		"fd invalido -> retorno %zd, errno %d (%s)",
		devolvido, errno, strerror(errno));
}

static void	testa_strdup(void)
{
	const char	*origem = "Hello, World!";
	char		mutavel[32] = "posso mudar";
	char		*copia;

	titulo("ft_strdup");
	copia = ft_strdup(origem);
	verifica(copia != NULL, "devolveu um ponteiro valido");
	if (!copia)
		return ;
	verifica(strcmp(copia, origem) == 0, "conteudo copiado: \"%s\"", copia);
	verifica(copia != origem, "o ponteiro e diferente: e copia, nao apelido");
	free(copia);
	copia = ft_strdup("");
	verifica(copia != NULL && copia[0] == '\0',
		"string vazia gera bloco com apenas o terminador");
	free(copia);
	copia = ft_strdup(mutavel);
	mutavel[0] = 'X';
	verifica(strcmp(copia, "posso mudar") == 0,
		"alterar a origem depois nao afeta a copia: \"%s\"", copia);
	free(copia);
}

int	main(void)
{
	printf(NEGRITO "\n Testes da libasm \n" RESET);
	testa_strlen();
	testa_strcpy();
	testa_strcmp();
	testa_write();
	testa_read();
	testa_strdup();
	if (g_falhas == 0)
		printf("\n" VERDE NEGRITO "Todos os testes passaram." RESET "\n\n");
	else
		printf("\n" VERMELHO NEGRITO "%d teste(s) falharam." RESET "\n\n",
			g_falhas);
	return (g_falhas != 0);
}
