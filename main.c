#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

void clearScreen()
{
    system("clear");
}

void help()
{
    printf("---------- HELP ----------\n");
    printf("1. exit-terminal >> zamkniecie konsoli\n");
    printf("2. help >> wyswietlenie opisu komend\n");
}

int checkCommand(char *command)
{
    const char commandArray[][200] = {"exit-terminal", "help", "clear"};
    for(int i = 0; i < sizeof(commandArray)/sizeof(commandArray[0]); i++)
    {
        if(strcmp(commandArray[i], command) == 0)
            return i;
    }
}

void mainLoop()
{
    char command[200];
    while (strcmp("exit-terminal", command) != 0)
    {
        printf("$: ");
        scanf("%s", command);
        switch (checkCommand(command))
        {
        case 0:
            break;
        case 1:
            help();
            break;
        case 2:
            clearScreen();
            break;
        default:
            break;
        }
    }
}

int main()
{
    mainLoop();
}