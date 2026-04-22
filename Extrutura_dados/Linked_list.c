#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5
#define LETTERS 26

typedef struct Node {
  char value;
  struct Node *next;
} Node;

int Check_Node(Node *node) {
  if (node == NULL) {
    printf("error memory allocated");
    return 1;
  }
  return 0;
}

Node *Create_Node(char *value) {
  Node *node = malloc(sizeof(Node));
  node->next = NULL;
  node->value = *value;
  return node;
}

void Print_list(Node *node) {
  Node *current = node;

  while (current != NULL) {
    printf("-> %c ", current->value);
    current = current->next;
  }
}

void Free_Linked_list(Node *node) {
  Node *current = node;
  Node *temp;

  while (current != NULL) {
    temp = current;
    current = current->next;
    free(temp);
  }
}

void Free_Item_list(Node *node, char *item) {
  Node *current = node;
  Node *prev = current;
  Node *temp;

  while (current != NULL) {
    if (current->value == *item) {
        temp = current;
      current = current->next;
      prev->next = current;
      free(temp);
      break;
    }
    prev = current;
    current = current->next;
  }
}

int main(void) {

  srand(time(NULL));

  char first_letter = '0';
  Node *node = Create_Node(&first_letter);
  if (Check_Node(node) == 1) {
    return 1;
  }

  for (int i = 0; i < N; i++) {
    char letter = 'A' + rand() % LETTERS;
    Node *new_node = Create_Node(&letter);
    if (Check_Node(new_node) == 1) {
      return 1;
    }

    Node *current = node;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_node;
  }

  Print_list(node);

  char character = getchar();
  Free_Item_list(node, &character);

  Print_list(node);
  return 0;
}
