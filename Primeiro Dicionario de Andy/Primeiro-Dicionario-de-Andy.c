#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 10007  // Número primo mais próximo de 10000
#define MAX_WORD_LENGTH 201

typedef struct Node {
    char word[MAX_WORD_LENGTH];
    struct Node *next;
} Node;

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

unsigned int hash(const char *str) {
    unsigned long hash = 0;
    int c;
    while ((c = *str++)) {
        hash = (hash * 31) + c;
    }
    return hash % TABLE_SIZE;
}

// Inserir palavra na tabela hash
void insert(Node *hashTable[], const char *word) {
    unsigned int index = hash(word);
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Verificar se uma palavra está na tabela hash
int search(Node *hashTable[], const char *word) {
    unsigned int index = hash(word);
    Node *current = hashTable[index];
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Liberar memória da tabela hash
void freeTable(Node *hashTable[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = hashTable[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    Node *hashTable[TABLE_SIZE] = {NULL};
    char word[MAX_WORD_LENGTH];
    int ch;
    int i = 0;

    while ((ch = getchar()) != EOF) {
        if (isalpha(ch)) {
            word[i++] = tolower(ch);
        } else {
            if (i > 0) {
                word[i] = '\0';
                if (!search(hashTable, word)) {
                    insert(hashTable, word);
                }
                i = 0;
            }
        }
    }

    // Criação de uma lista para armazenar as palavras para ordenação
    char *words[TABLE_SIZE];
    int word_count = 0;
    for (int j = 0; j < TABLE_SIZE; j++) {
        Node *current = hashTable[j];
        while (current != NULL) {
            words[word_count] = (char *)malloc(strlen(current->word) + 1);
            strcpy(words[word_count], current->word);
            word_count++;
            current = current->next;
        }
    }

    // Ordena as palavras em ordem alfabética
    qsort(words, word_count, sizeof(char *), compare);

    // Imprime as palavras ordenadas
    for (int j = 0; j < word_count; j++) {
        printf("%s\n", words[j]);
        free(words[j]);  // Libera a memória alocada
    }

    freeTable(hashTable);  // Libera a memória da tabela hash

    return 0;
}
