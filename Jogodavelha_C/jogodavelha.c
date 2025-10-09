#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LINHAS_E_COLUNAS 3
#define MAXPOSICOES 2
#define VAZIO '_'
#define JOGADOR_X 'X'
#define JOGADOR_O 'O'
 
void converterposicoes(int posicaoescolhida, int linhaecoluna[MAXPOSICOES]);
void exibirtabuleiro(char tabuleiro[LINHAS_E_COLUNAS][LINHAS_E_COLUNAS]);
void jogadores(char tabuleiro[LINHAS_E_COLUNAS][LINHAS_E_COLUNAS], char jogador);
int verificarlinha(char tabuleiro[LINHAS_E_COLUNAS][LINHAS_E_COLUNAS], char jogador);
int verificardiagonais(char tabuleiro[LINHAS_E_COLUNAS][LINHAS_E_COLUNAS], char jogador);
int verificarcoluna(char tabuleiro[LINHAS_E_COLUNAS][LINHAS_E_COLUNAS], char jogador);

int main(void)
{	
	char tabuleiro[LINHAS_E_COLUNAS][LINHAS_E_COLUNAS];
	int jogadorX[LINHAS_E_COLUNAS] = {0,0,0};
	int jogadorO[LINHAS_E_COLUNAS] = {0,0,0};	

	for (int i = 0; i < LINHAS_E_COLUNAS; i++)
	{
		for (int j = 0; j < LINHAS_E_COLUNAS; j++)
		{
			tabuleiro[i][j] = VAZIO;
		}
	}

	int x = 0;
	while (x == 0)
	{
		jogadores(tabuleiro, JOGADOR_X);
		exibirtabuleiro(tabuleiro);

		jogadorX[0] = verificarlinha(tabuleiro, JOGADOR_X);
		jogadorX[1] = verificarcoluna(tabuleiro, JOGADOR_X);
		jogadorX[2] = verificardiagonais(tabuleiro, JOGADOR_X);

	
		for (int i = 0; i < LINHAS_E_COLUNAS; i++)
		{
			if (jogadorX[i] == 1)
			{
				printf("\nparabens jogador X\n");
				return 0;
			}
		}

		jogadores(tabuleiro, JOGADOR_O);
		exibirtabuleiro(tabuleiro);

		jogadorO[0] = verificarlinha(tabuleiro, JOGADOR_O);
		jogadorO[1] = verificarcoluna(tabuleiro, JOGADOR_O);
		jogadorO[2] = verificardiagonais(tabuleiro, JOGADOR_O);

		for (int i = 0; i < LINHAS_E_COLUNAS; i++)
		{
			if (jogadorO[i] == 1)
			{
				printf("\nparabens jogador O\n");
					return 0;
			}
		}
		
		int contador = 0;
		for (int i = 0; i < LINHAS_E_COLUNAS; i++)
		{
			for (int j = 0; j < LINHAS_E_COLUNAS; j++)
			{
				if (tabuleiro[i][j] != VAZIO)
				{
					contador++;
				}
			}
		}
		
		if (contador == 8)
		{
			printf("\ntemos um empate\n");
			return 0;
		}
	}
	
	
	return 0;
}

int verificardiagonais(char tabuleiro[LINHAS_E_COLUNAS][LINHAS_E_COLUNAS], char jogador)
{
	if (tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador)
	{
		return 1;
	}
	if (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador)
	{
		    return 1;
	}
	return 0;
}


int verificarlinha(char tabuleiro[LINHAS_E_COLUNAS][LINHAS_E_COLUNAS], char jogador)
{
	for (int i = 0; i < LINHAS_E_COLUNAS; i++)
	{
		int linha = 0;
		for (int j = 0; j < LINHAS_E_COLUNAS; j++)
		{
			if (tabuleiro[i][j] == jogador)
			{
				linha++;
			}
		}
		if (linha == LINHAS_E_COLUNAS)
		{
			return 1;
		}
	}
	return 0;
}

int verificarcoluna(char tabuleiro[LINHAS_E_COLUNAS][LINHAS_E_COLUNAS], char jogador)
{
	for (int i = 0; i < LINHAS_E_COLUNAS; i++)
	{
		int coluna = 0;
		for (int j = 0; j < LINHAS_E_COLUNAS; j++)
		{
			if (tabuleiro[j][i] == jogador)
			{
				coluna++;
			}
		}
		if (coluna == LINHAS_E_COLUNAS)
		{
			return 1;
		}
	}
	return 0;
}

void converterposicoes(int posicaoescolhida, int linhaecoluna[2])
{
	if (posicaoescolhida == 1)
	{
		linhaecoluna[0] = 0;
		linhaecoluna[1] = 0;
	}
	if (posicaoescolhida == 2)
	{
		linhaecoluna[0] = 0;
		linhaecoluna[1]= 1;
	}
	if (posicaoescolhida == 3)
	{
		linhaecoluna[0] = 0;
		linhaecoluna[1] = 2;
	}

	if (posicaoescolhida == 4)
	{
		linhaecoluna[0] = 1;
		linhaecoluna[1] = 0;
	}
	if (posicaoescolhida == 5)
	{
		linhaecoluna[0] = 1;
		linhaecoluna[1] = 1;
	}
	if (posicaoescolhida == 6)
	{
		linhaecoluna[0] = 1;
		linhaecoluna[1] = 2;
	}
	if (posicaoescolhida == 7)
	{
		linhaecoluna[0] = 2;
		linhaecoluna[1] = 0;
	}
	if (posicaoescolhida == 8)
	{
		linhaecoluna[0] = 2;
		linhaecoluna[1] = 1;
	}
	if (posicaoescolhida == 9)
	{
		linhaecoluna[0] = 2;
		linhaecoluna[1] = 2;
	
	}
	return;
}

void jogadores(char tabuleiro[LINHAS_E_COLUNAS][LINHAS_E_COLUNAS], char jogador)
{
	int posicaoescolhida;
	int posicoes[2];

	printf("\ndigite a posicao de 1 a 9\n");

	if (scanf("\n%d", &posicaoescolhida) != 1 && (posicaoescolhida < 1 || posicaoescolhida > 9)) 
	{
		printf("\nnumero de 1 a 9\n");
		while (getchar() != '\n');
		return;
	}

	converterposicoes(posicaoescolhida, posicoes);
	

	if (tabuleiro[posicoes[0]][posicoes[1]] != VAZIO)
	{
		printf("\nessa casa ja esta preenchida\n");
		return;
	}

	tabuleiro[posicoes[0]][posicoes[1]] = jogador;
	

	return;
}

void exibirtabuleiro(char tabuleiro[LINHAS_E_COLUNAS][LINHAS_E_COLUNAS])
{
	for (int i = 0; i < LINHAS_E_COLUNAS; i++)
	{
		for (int j = 0; j < LINHAS_E_COLUNAS; j++)
		{
			printf("| %c |", tabuleiro[i][j]);
		}
		printf("\n");
	}
	return;
}
