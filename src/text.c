#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

//
#define PATH_SIZE 600
#define COMMAND_SIZE 100

//
#define FILE_NAME 150
#define LINE_SIZE 200
#define NUMBER_OF_LINES 300

//
#define DIR_NAME 200

//colors
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define WHITE "\033[0;37m"

void createDirectory(char *dirName)
{
    for (int i = 0; i < (int)strlen(dirName); i++)
    {
        if(dirName[i] == '\n')
            dirName[i] = '\0'; 
        else
            dirName[i] = dirName[i];
    }
    for (int i = 0; i < (int)strlen(dirName); i++)
    {
        if(dirName[i] == ' ')
            dirName[i] = '_'; 
        else
            dirName[i] = dirName[i];
    }
    if(mkdir(dirName, 0777) != -1)
    {
        printf("%snew folder has been created", GREEN);
        printf("%s\n", WHITE);
    }
    else
    {
        printf("%serror occurred while creating the folder", RED);
        printf("%s\n", WHITE);
    }
}

int main(void)
{
    char *komenda = malloc(200 * sizeof(char));
    char *kom = malloc(200 * sizeof(char));
    char *file = malloc(200 * sizeof(char));
    int n = 0;
    printf("Podaj komende: ");
    fgets(komenda, 200, stdin);
    for(int i = 0; i < (int)strlen(komenda); i++)
    {
        if(komenda[i] == '\n')
            komenda[i] = '\0';
        else
            komenda[i] = komenda[i];
    }
    for(int i = 0; i < (int)strlen(komenda); i++)
    {
        if(komenda[i] == ' ')
            n = 1;
        if(n == 0)
            kom[i] = komenda[i];
        if(n == 1)
            file[i - 1 - (int)strlen(kom)] = komenda[i];
    }
    n = 0;
    if(file == NULL || strcmp(file, "") == 0 || strcmp(file, " ") == 0)
    {
        printf("%smusisz podac nazwe folderu\n", RED);
    }
    else
    {
        createDirectory(file);
    }
    free(komenda);
    free(kom);
}