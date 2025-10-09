#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAXPALAVRAS 20
#define MAXLETRAS 10
#define MAXTENTATIVAS 10

// funcoes do jogo
int jogada(char *palavra, char tabuleiro[10]);
int abrirarquivo(char *nomearquivo, char buffer[][10]);
int aleatorizar(int itens);
void exibirparabens(void);
void escolherarquivo(char nomearquivo[20]);

// array para armazenar as palavras na memoria
char buffer[MAXPALAVRAS][MAXLETRAS];

int main(void)
{
	// 
	char tabuleiro[MAXLETRAS];
	int tentativas = 0;

	// sortear uma palavra 
	int indicealeatorio = aleatorizar(MAXPALAVRAS);

	// escolher o tema das palavras
	char nomearquivo[20];
	escolherarquivo(nomearquivo);


	if (abrirarquivo(nomearquivo, buffer) == 0)
	{
		printf("\n o tema escolhido e %s\n", nomearquivo);
		return 0;
	}

	char *palavra = buffer[indicealeatorio];
	
	// inicializando o array das letras escondidas
	for (int i = 0; i < strlen(palavra); i++)
	{
		tabuleiro[i] = '_';
	}
	tabuleiro[strlen(palavra)] = '\0';

	while (strcmp(palavra, tabuleiro) != 0)
	{	
		// verificacao das tentativas
		if (tentativas == MAXTENTATIVAS)
		{
			printf("\nacabou suas tentativas\n");
			return 0;
		}

		// exibir tabuleiro
		for (int i = 0; i < strlen(palavra); i++)
		{
			printf("%c ", tabuleiro[i]);

		}
		
		// jogador 
		printf("\nescolha uma letra\n");
		jogada(palavra, tabuleiro);

		// contagem tentativas
		printf("\n");
		tentativas++;
	}

	exibirparabens();
	return 0;
}

void escolherarquivo(char nomearquivo[20])
{	
	int indicearquivo;
	char nomes[5][20] = 
	{
		"plantas.txt",
		"skate.txt",
		"programacao.txt",
		"musica.txt",
		"anime.txt"

	};

	printf("\nescolha um tema");
	printf("\n1 para plantas");
	printf("\n2 para skate");
	printf("\n3 para programacao");
	printf("\n4 para musica");
	printf("\n5 para anime");

	scanf("%d", &indicearquivo);
	
	// copia o nome do arquivo para nomearquivo
	strcpy(nomearquivo, nomes[indicearquivo - 1]);

	return;

}


int abrirarquivo(char *nomearquivo, char buffer[][MAXLETRAS])
{
	// abre arquivo 
	FILE *arquivo = fopen(nomearquivo, "r");
	if (arquivo == NULL)
	{
		printf("\narquivo nao encontrado\n");
		return 0;
	}
	// armazena as plavras em buffer 
	int i = 0;
	while (i < MAXPALAVRAS && fscanf(arquivo, " %s", buffer[i]) == 1)
	{
		i++;
	}

	// fecha arquivo e retorna a quantidade de palavras lidas
	fclose(arquivo);
	return i;
}

int aleatorizar(int itens)
{
	srand(time(NULL));
	int indicealeatorio = rand() % itens;
	
	return indicealeatorio;
	
}

int jogada(char *palavra, char tabuleiro[10])
{
	char letra[3];
	scanf(" %s", letra);

	if (strlen(letra) > 1)
	{
		printf("\napenas uma letra de cada vez\n");
		return 1;
	}

	for (int i = 0; i < strlen(palavra); i++)
	{
		if (letra[0] == palavra[i])
		{
			tabuleiro[i] = letra[0];
		}
	}
	return 0;
}


void exibirparabens(void) 
{
	printf("Parabéns, você ganhou a Forca! 🏆\n");
	printf("==================================\n\n");

	printf("         ___________        \n");
	printf("        '._==_==_=_.''      \n");
	printf("        .-\\:      /-.      \n");
	printf("       | (|:.     |) |      \n");
	printf("        '-|:.     |-'       \n");
	printf("          \\::.    /        \n");
	printf("           '::. .'          \n");
	printf("             ) (            \n");
	printf("           _.' '._          \n");
	printf("          `````````         \n");

	printf("       TROFÉU DA FORCA!     \n");

 	return;
}
