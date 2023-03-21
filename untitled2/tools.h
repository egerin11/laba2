#ifndef LABA2_TOOLS_H
#define LABA2_TOOLS_H

int cycleWord(const char *token, char *temp);
void addNode(struct Node *node,char *temp);
void readFile( struct Node *node, const char *fileName);

char *findMaxLenWord(const struct Node *node);

char *findMinLenWord(const struct Node *node);

int compress(const char *fileName, const char *word, const char *newWord);

int unCompress(const char *fileName);

void deleteSymbol(char *temp);

void checkTransitionToANewLine(char *temp, const char *token);

void inputSpaces(const char *buffer, char *temp, int i);

int getMaxCount(const struct Node *node);
void token( char *buffer,char *temp,const char *word,const char *nWord);



#endif
