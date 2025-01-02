#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

#define FILE_NAME 50
#define LINE_LENGTH 200
#define NUMBERS_OF_LINES 300

#define BLUE "\e[0;34m"

int main(void)
{
    char *fileName = malloc(sizeof(char) * FILE_NAME);
    char *fileContent[NUMBERS_OF_LINES];
    for(__uint16_t i = 0; i < NUMBERS_OF_LINES; i++)
        fileContent[i] = malloc(LINE_LENGTH * sizeof(char));
    __uint16_t index = 0;
    printf("File name: ");
    scanf("%s", fileName);
    FILE *file;
    file = fopen(fileName, "r");
    if(file != NULL)
        while (fgets(fileContent[index], LINE_LENGTH, file))
            index++;
    for(__uint16_t i = 0; i < LINE_LENGTH; i++)
        if(strcmp(fileContent[i], "") != 0)
            printf("%d   %s",i ,fileContent[i]);
    printf("\n");
}