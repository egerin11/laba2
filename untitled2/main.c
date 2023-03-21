#include <stdio.h>
#include "struct.h"
#include"queue.h"
#include"tools.h"

int main() {
    char *buffer, *newWord;

    struct Node node = {NULL, NULL, 0};
    readFile(&node, "huinya.txt");
    display(&node);
    buffer = findMaxLenWord(&node);
    newWord = findMinLenWord(&node);
    printf("%s %s ",buffer,newWord);
    compress("huinya.txt", buffer, newWord);
    unCompress("File.txt");
    freeQueue(&node);
    return 0;
}
