#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 30
#define HEIGHT 60

typedef struct SnakePiece
{
	int x;
	int y;
	struct SnakePiece *next;

} SnakePiece;

struct termios old, new;

char screen[WIDTH][HEIGHT];

void drawBody(SnakePiece *head, int *index);
void Bodymove(SnakePiece *head);
void randomFood(int *index);
void cleanTerminal();
void movimentationSnakePiece(SnakePiece *head, char *inputkeyboard, char *lastinput, int *index);
void createPieceSnake(SnakePiece *head);
void newModeTerminal(struct termios *old, struct termios *new);
void returnModeTerminal(struct termios *old);
void insertHead(SnakePiece *head);
void startScreen();
void printScreen();

int main()
{
	// start head snake
	SnakePiece *head = malloc(sizeof(SnakePiece));
	if (head == NULL)
	{
		printf("head NULL");
		return 1;
	}
	head->next= NULL;


	SnakePiece *body = malloc(sizeof(SnakePiece));
	if (body == NULL)
	{
		printf("head NULL");
		return 1;
	}

	body->next = NULL;
	head->next = body;

	char inputkeyboard;
	char lastinput;
	int index[2];

	head->x = 15;
	head->y = 30;

	body->x = head->x;
	body->y = head->y;

	newModeTerminal(&old, &new);
	startScreen();
	randomFood(index);
	while (1)
	{	
		if (index[0] == head->x && index[1] == head->y)
		{
			randomFood(index);
			createPieceSnake(head);
		}
		movimentationSnakePiece(head, &inputkeyboard, &lastinput, index);
		Bodymove(head);
		printScreen();
		usleep(100000);
		cleanTerminal();
	}
	
	returnModeTerminal(&old);
	return 0;
}

void drawBody(SnakePiece *head, int *index)
{
	cleanTerminal();
	screen[index[0]][index[1]] = '@';

	SnakePiece *current = head;
	SnakePiece *prev = NULL;

	while (current != NULL)
	{
		screen[current->x][current->y] = '#';
		current = current->next;
	}

}
void randomFood(int *index)
{
	srand(time(NULL));

	index[0] = rand() % WIDTH-1;
	index[1] = rand() % HEIGHT-1;

}

void cleanTerminal()
{
	printf("\033[H\033[J");
	return;
}

void movimentationSnakePiece(SnakePiece *head ,char *inputkeyboard, char *lastinput, int *index)
{
	read(STDIN_FILENO, inputkeyboard, 1);
	
	if (*inputkeyboard != 'h' && *inputkeyboard != 'j' && *inputkeyboard != 'k' && *inputkeyboard != 'l')
	{
		*lastinput = *lastinput;
	}
	else 
	{
		*lastinput = *inputkeyboard;
	}
	
	switch (*lastinput) 
	{
		case 'k':
			head->x--;
			break;
		case 'j':
			head->x++;
			break;
		case 'h':
			head->y--;
			break;
		case 'l':
			head->y++;
			break;
	}
	drawBody(head, index);
	return;
}

void createPieceSnake(SnakePiece *head)
{
	SnakePiece *bodypiece = malloc(sizeof(SnakePiece));
	if (bodypiece == NULL)
	{
		printf("Error allocated memory");
		return;
	}
	
	bodypiece->x = head->x;
	bodypiece->y = head->y;
	bodypiece->next = NULL;

	SnakePiece *current = head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = bodypiece;;

	return;
}

void Bodymove(SnakePiece *head)
{	
	SnakePiece *current = head;
	SnakePiece *prev = NULL;

	while (current->next != NULL)
	{
		prev = current;
		current = current->next;
	}
	
	SnakePiece *copyfrom = head;

	int tempX = copyfrom->x;
	int tempY = copyfrom->y;
	
	SnakePiece *copyto = head->next;

	while (copyto != NULL)
	{
		int savex = copyto->x;
		int savey = copyto->y;
		copyto->x = tempX;
		copyto->y = tempY;
		copyfrom = copyto;
		tempX = savex;
		tempY = savey;
		copyto = copyfrom->next;
	}

	screen[tempX][tempY] = '.';
	return;
}

void newModeTerminal(struct termios *old, struct termios *new)
{
	tcgetattr(STDIN_FILENO, old);
	*new = *old;
	new->c_lflag &= ~(ICANON | ECHO);
	new->c_cc[VMIN] = 0;
	new->c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, new);
	return;
}

void returnModeTerminal(struct termios *old)
{
	tcsetattr(STDIN_FILENO, TCSANOW, old);
	return;
}

void insertHead(SnakePiece *head)
{
	screen[head->x][head->y] = '#';
	return;
}

void startScreen()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			screen[i][j] = '.';
		}
	}
	return;
}

void printScreen()
{	
	for (int i = 0; i < WIDTH; i++)
	{
		printf("\n");
		for (int j = 0; j < HEIGHT; j++)
		{
			printf("%c", screen[i][j]);
		}
	}
	return;
}


