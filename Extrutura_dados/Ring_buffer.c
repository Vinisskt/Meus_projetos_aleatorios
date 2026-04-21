#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 101
#define LETTERS 26

typedef struct Buffer {
  char buffer[N];
  int head;
  int tail;
} Buffer;

int putChar(Buffer *buffer) {

  if ((buffer->head + 1) % N != buffer->tail) {
    buffer->buffer[buffer->head] = 'a' + rand() % LETTERS;
    buffer->head = (buffer->head + 1) % N;
    return 0;
  }
  return 1;
}

int getChar(Buffer *buffer, char *character) {

  if (buffer->tail != buffer->head) {
    *character = buffer->buffer[buffer->tail];
    buffer->buffer[buffer->tail] = '0';
    buffer->tail = (buffer->tail + 1) % N;
    return 0;
  }
  return 1;
}

int main(void) {

  srand(time(NULL));

  Buffer *buffer = malloc(sizeof(Buffer));

  buffer->head = 0;
  buffer->tail = 0;
  char character;

  for (int i = 0; i < N; i++) {
    if (putChar(buffer) == 1) {
      printf("\nBuffer Cheio\n\n");
      break;
    }
  }

  for (int i = 0; i < N; i++) {
    if (getChar(buffer, &character) == 1) {
      printf("\n\nBuffer vazio\n");
      break;
    }
    printf(" %c |", character);
  }
  printf("\n%s\n", buffer->buffer);
  for (int i = 0; i < 10; i++) {
    printf("\n");
  }
  free(buffer);
  return 0;
}
