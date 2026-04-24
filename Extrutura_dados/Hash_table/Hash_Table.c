#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_WORD 10
#define SIZE_HASH 26

typedef struct Node {
	char word[SIZE_WORD];
	struct Node *next;
} Node;

int load_hash(Node *hash[SIZE_HASH]);
int check_node(Node *node);
int check_index_word(Node *node);
void start_hash(Node *hash[SIZE_HASH]);
void print_hash(Node *hash[SIZE_HASH]);
void free_hash(Node *hash[SIZE_HASH]);

int main(void) {

	Node *hash[SIZE_HASH];
	start_hash(hash);
	load_hash(hash);
	print_hash(hash);
	free_hash(hash);
	return 0;
}

void start_hash(Node *hash[SIZE_HASH]) {
	for (int i = 0; i < SIZE_HASH; i++) {
		Node *head = malloc(sizeof(Node));
		head->next = NULL;
		hash[i] = head;
	}
	return;
}

int check_index_word(Node *node) {
	return node->word[0] - 'a';
}

int check_node(Node *node) {
	if (node == NULL) {
		printf("error memory allocated");
		return 1;
	}
	return 0;
}

Node *create_node(char word[SIZE_WORD]) {
	Node *node = malloc(sizeof(Node));
	node->next = NULL;
	strcpy(node->word, word);

	return node;
}

int load_hash(Node *hash[SIZE_HASH]) {
	
	char word[SIZE_WORD];
	FILE *file = fopen("palavras.txt", "r");
	if (file == NULL) {
		printf("file not found");
		return 1;
	}

	while (fscanf(file, "%s", word) != EOF ) {
		Node *new_node = create_node(word);
		if (check_node(new_node) == 1) {
			return 1;
		}
		
		int index = check_index_word(new_node);
		Node *current = hash[index];
		new_node->next = current->next;
		current->next = new_node;
	}

	fclose(file);
	return 0;
}

void print_hash(Node *hash[SIZE_HASH]) {
	for (int i = 0; i < SIZE_HASH; i++) {
		Node *current = hash[i];
		current = current->next;
		while (current != NULL) {
			printf("%s\n", current->word);
			current = current->next;
		}
	}
	return;
}

void free_hash(Node *hash[SIZE_HASH]) {
	Node *temp;

	for (int i = 0; i < SIZE_HASH; i++) {
		Node *current = hash[i];
		while (current != NULL) {
			temp = current;
			current = current->next;
			free(temp);
		}
	}
	return;
}

