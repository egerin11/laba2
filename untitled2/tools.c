#include<stdio.h>
#include <string.h>
#include"struct.h"
#include"queue.h"
#include<stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include<stdbool.h>

void readFile(const struct Node *node, const char *fileName) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("open error");
        return;
    }
    char buffer[100];
    char temp[100];
    while (fgets(buffer, 100, fp) != NULL) {
        temp[0] = '\0';
        char *token = strtok(buffer, " \t\n");
        while (token != NULL) {
            int i = 0;
            for (int j = 0; token[j]; j++) {
                if (isalnum(token[j])) {
                    temp[i++] = tolower(token[j]);
                }
            }
            if (temp[i - 1] == '\n') {
                temp[i - 1] = '\0';
                i--;
            }
            temp[i] = '\0';
            if (i > 0) {
                struct WordNode *iter = node->head;
                while (iter != NULL) {
                    if (strcmp(iter->word, temp) == 0) {
                        iter->countWords++;
                        break;
                    }
                    iter = iter->next;
                }
                if (iter == NULL) {
                    create(node, temp);
                }
            }
            token = strtok(NULL, " \t\n");
        }
    }
    fclose(fp);
}

char *findMaxLenWord(const struct Node *node) {
    if (node == NULL || node->head == NULL) return NULL;
    int maxCount = 0;
    char *tempArray = NULL;
    struct WordNode *iter = node->head;
    while (iter != NULL) {
        if (strlen(iter->word) > 3 && iter->countWords >= maxCount) {
            maxCount = iter->countWords;
            tempArray = iter->word;
        }
        iter = iter->next;
    }
    if (tempArray == NULL) return "*";
    return tempArray;
}

int getMaxCount(const struct Node *node) {
    int maxCount = 0;
    struct WordNode *iter = node->head;
    while (iter != NULL) {
        if (iter->countWords > maxCount) {
            maxCount = iter->countWords;
        }
        iter = iter->next;
    }
    return maxCount;
}

char *findMinLenWord(const struct Node *node) {
    if (node == NULL || node->head == NULL) return NULL;
    int minCount = node->head->countWords + 1;
    char *tempArray = NULL;
    struct WordNode *iter = node->head;
    while (iter != NULL) {
        if (strlen(iter->word) < 2 && iter->countWords <= minCount && iter->countWords < getMaxCount(node)) {
            minCount = iter->countWords;
            tempArray = iter->word;
        }
        iter = iter->next;
    }
    if (tempArray == NULL) return "&";
    return tempArray;
}

void deleteSymbol(char *temp) {
    while (strlen(temp) > 0 && !isalpha(temp[strlen(temp) - 1]) && (temp[strlen(temp) - 1] != '.' &&
                                                                    temp[strlen(temp) - 1] != ',')) {
        temp[strlen(temp) - 1] = '\0';
    }
}

void checkTransitionToANewLine(char *temp, char *token) {
    bool hasNewline;
    if (token[strlen(token) - 1] != '\n') {
        strcat(temp, " ");
    } else {
        temp[strlen(temp) - 1] = '\0';
        hasNewline = true;
    }


    if (token == NULL && !hasNewline) {
        strcat(temp, "\n");
    }
}

void inputSpaces(const char *buffer, char *temp, int i) {
    int numSpaces = 0;

    while (buffer[i] != '\0' && isspace(buffer[i])) {
        if (!isalpha(buffer[i])) {
            numSpaces++;
        }
        i++;
    }
    for (int i = 0; i < numSpaces; i++) {
        strcat(temp, " ");
    }

}
void token( char *buffer,char *temp,const char *word,const char *newWord)
{
    char *token = strtok(buffer, " \t\n");
    while (token != NULL) {
        int len = strlen(token);
        if (len > 0) {

            char lastChar = token[len - 1];
            if (!isalnum(lastChar)) {
                char *wordOnly = malloc(len);
                strncpy(wordOnly, token, len - 1);
                wordOnly[len - 1] = '\0';
                if (strcmp(wordOnly, word) == 0) {
                    strcat(temp, newWord);

                } else if (strcmp(token, newWord) == 0) {
                    strcat(temp, word);

                } else {
                    strcat(temp, token);
                }
                free(wordOnly);
            } else {
                if (strcmp(token, newWord) == 0) {
                    strcat(temp, word);
                } else if (strcmp(token, word) == 0) {
                    strcat(temp, newWord);
                } else {

                    strcat(temp, token);

                }
            }


            checkTransitionToANewLine(temp, token);
            token = strtok(NULL, " \t\n");
        }

    }
}


void compress(const char *fileName, const char *word, const char *newWord) {
    if (word == NULL || newWord == NULL) {
        printf("Error: word or newWord is NULL\n");
        return;
    }
    FILE *oldFile = fopen(fileName, "r");
    FILE *newFile = fopen("File.txt", "w");
    if (oldFile == NULL || newFile == NULL) {
        printf("open error \n");

        fclose(oldFile);
        fclose(newFile);
        return;
    }
    fprintf(newFile, "%s %s ", word, newWord);
    char buffer[1000];
    while (fgets(buffer, 1000, oldFile) != NULL) {
        char *temp = (char *) calloc(1000, sizeof(char));
        inputSpaces(buffer, temp, 0);
        token(buffer,temp,word,newWord);
        deleteSymbol(temp);
        strcat(temp, "\n");
        temp = (char *) realloc(temp, (strlen(temp) + 2) * sizeof(char));
        fprintf(newFile, "%s", temp);
        free(temp);
    }

    fclose(oldFile);
    fclose(newFile);
}


void unCompress(const char *fileName) {

    FILE *oldFile = fopen(fileName, "r");
    FILE *newFile = fopen("newFile.txt", "w");
    if (oldFile == NULL || newFile == NULL) {
        printf("open error\n");
        fclose(oldFile);
        fclose(newFile);
        return;
    }

    char buffer[1000];
    char word[100];
    char newWord[100];
    fscanf(oldFile, "%s", word);
    fscanf(oldFile, "%s", newWord);
    while (fgets(buffer, 1000, oldFile) != NULL) {
        char *temp = (char *) calloc(1000, sizeof(char));
        inputSpaces(buffer, temp, 1);
        token(buffer,temp,newWord,word);
        deleteSymbol(temp);
        strcat(temp, "\n");
        temp = (char *) realloc(temp, (strlen(temp) + 2) * sizeof(char));
        fprintf(newFile, "%s", temp);
        free(temp);

    }

    fclose(oldFile);
    fclose(newFile);
}



