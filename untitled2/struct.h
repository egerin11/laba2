#ifndef LABA2_STRUCT_H
#define LABA2_STRUCT_H
struct WordNode {
    char word[100];
    int countWords;
    struct WordNode *next;
    struct WordNode *prev;
};
struct Node {
    struct WordNode *head;
    struct WordNode *tail;
    int size;
};

#endif
