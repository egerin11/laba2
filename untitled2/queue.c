#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"struct.h"

void create(struct Node *node, char *buffer) {
    struct WordNode *word = (struct WordNode *) malloc(sizeof(struct WordNode));
    if (strlen(buffer) > 100) {
        return;
    } else {
        strcpy(word->word, buffer);
    }
    word->countWords = 1;
    word->next = NULL;
    word->prev = node->tail;
    if (node->head == NULL) {
        node->head = word;
        node->tail = word;
    } else {
        node->tail->next = word;
        word->prev = node->tail;
        node->tail = word;
    }
    node->size++;
}
void display( struct Node *node) {
    struct WordNode *word = node->head;

    while (word != NULL) {
        printf("%s %d\n", word->word, word->countWords);
        word = word->next;

    }

}

void freeQueue(struct Node *node) {
    struct WordNode *current = node->head;
    while (current != NULL) {
        struct WordNode *next = current->next;
        free(current);
        current = next;
    }
    node->head = NULL;
    node->tail = NULL;
    node->size = 0;
}
