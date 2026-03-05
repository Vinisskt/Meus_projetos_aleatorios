#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 40
#define HEIGHT 25

typedef struct SnakePiece {
  int x;
  int y;
  struct SnakePiece *next;
} SnakePiece;

struct termios old, new;

char screen[HEIGHT][WIDTH];

void drawBody(SnakePiece *head, int *foodIndex);
void Bodymove(SnakePiece *head, int oldHeadX, int oldHeadY);
void randomFood(int *foodIndex);
void cleanTerminal();
void movimentationSnakePiece(SnakePiece *head, char *inputkeyboard,
                             char *lastinput, int *foodIndex);
void createPieceSnake(SnakePiece *head);
void newModeTerminal(struct termios *old, struct termios *new);
void returnModeTerminal(struct termios *old);
void startScreen();
void printScreen();
int checkCollision(SnakePiece *head);
void printGameOver();

int main() {
  srand(time(NULL));

  // Inicia a cabeça da cobra
  SnakePiece *head = malloc(sizeof(SnakePiece));
  if (head == NULL) {
    printf("Erro ao alocar cabeça\n");
    return 1;
  }
  head->x = WIDTH / 2;
  head->y = HEIGHT / 2;
  head->next = NULL;

  // Adiciona um primeiro pedaço de corpo
  createPieceSnake(head);

  char inputkeyboard = 0;
  char lastinput;
  int foodIndex[2];

  newModeTerminal(&old, &new);
  startScreen();
  randomFood(foodIndex);

  while (1) {
    cleanTerminal();

    if (checkCollision(head)) {
      returnModeTerminal(&old);
      printGameOver();
      return 0;
    }

    if (foodIndex[0] == head->x && foodIndex[1] == head->y) {
      createPieceSnake(head);
      randomFood(foodIndex);
    }

    movimentationSnakePiece(head, &inputkeyboard, &lastinput, foodIndex);
    printScreen();
    usleep(100000);
  }

  returnModeTerminal(&old);
  return 0;
}

void printGameOver() {
  printf("\n  GAME OVER  \n");
  printf("    #####    \n");
  printf("  #       #  \n");
  printf("  # X   X #  \n");
  printf("  #  ...  #  \n");
  printf("  # .   . #  \n");
  printf("  #       #  \n");
  printf("    #####    \n\n");
}

int checkCollision(SnakePiece *head) {
  if (head->x < 0 || head->x >= WIDTH || head->y < 0 || head->y >= HEIGHT) {
    return 1;
  }

  return 0;
}

void drawBody(SnakePiece *head, int *foodIndex) {
  screen[foodIndex[1]][foodIndex[0]] = '@';

  SnakePiece *current = head;
  while (current != NULL) {
    if (current->y >= 0 && current->y < HEIGHT && current->x >= 0 &&
        current->x < WIDTH) {
      screen[current->y][current->x] = '#';
    }
    current = current->next;
  }
}

void randomFood(int *foodIndex) {
  foodIndex[0] = rand() % WIDTH;
  foodIndex[1] = rand() % HEIGHT;
}

void cleanTerminal() { printf("\033[H\033[J"); }

void movimentationSnakePiece(SnakePiece *head, char *inputkeyboard,
                             char *lastinput, int *foodIndex) {
  if (read(STDIN_FILENO, inputkeyboard, 1) > 0) {
    if (*inputkeyboard == 'h' || *inputkeyboard == 'j' ||
        *inputkeyboard == 'k' || *inputkeyboard == 'l') {
      *lastinput = *inputkeyboard;
    }
  }

  int oldX = head->x;
  int oldY = head->y;

  switch (*lastinput) {
  case 'k':
    head->y--;
    break; // Cima
  case 'j':
    head->y++;
    break; // Baixo
  case 'h':
    head->x--;
    break; // Esquerda
  case 'l':
    head->x++;
    break; // Direita
  }

  Bodymove(head, oldX, oldY);
  drawBody(head, foodIndex);
}

void createPieceSnake(SnakePiece *head) {
  SnakePiece *newPiece = malloc(sizeof(SnakePiece));
  if (newPiece == NULL)
    return;

  SnakePiece *current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  newPiece->x = current->x;
  newPiece->y = current->y;
  newPiece->next = NULL;
  current->next = newPiece;
}

void Bodymove(SnakePiece *head, int oldHeadX, int oldHeadY) {
  SnakePiece *current = head->next;
  int prevX = oldHeadX;
  int prevY = oldHeadY;

  while (current != NULL) {
    int tempX = current->x;
    int tempY = current->y;

    current->x = prevX;
    current->y = prevY;

    prevX = tempX;
    prevY = tempY;

    current = current->next;
  }

  if (prevY >= 0 && prevY < HEIGHT && prevX >= 0 && prevX < WIDTH) {
    screen[prevY][prevX] = '.';
  }
}

void newModeTerminal(struct termios *old, struct termios *new) {
  tcgetattr(STDIN_FILENO, old);
  *new = *old;
  new->c_lflag &= ~(ICANON | ECHO);
  new->c_cc[VMIN] = 0;
  new->c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, new);
}

void returnModeTerminal(struct termios *old) {
  tcsetattr(STDIN_FILENO, TCSANOW, old);
}

void startScreen() {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      screen[i][j] = '.';
    }
  }
}

void printScreen() {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      printf("%c", screen[i][j]);
    }
    printf("\n");
  }
}
