#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define PATH_SIZE 1024

void changeDirectory()
{
    
}

void listFiles()
{
    struct dirent *direntPointer;
    DIR *dir = opendir(".");
    while((direntPointer = readdir(dir)) != NULL)
        if(direntPointer->d_name[0] != '.')
            printf("%s\n", direntPointer->d_name);
    closedir(dir);
}

void currentDirectory()
{
    char directory[PATH_SIZE];
    printf("$: %s\n", getcwd(directory, PATH_SIZE));
}

//clear the whole console
void clearScreen()
{
    system("clear");
}

//show describe of every command
void help()
{
    printf("---------- HELP ----------\n");
    printf("exit-terminal >> close terminal\n");
    printf("help >> show commands description\n");
    printf("clear >> clear terminal\n");
    printf("list-files >> list all files and directories in current directory\n");
    printf("current-dir >> show current path\n");
}

//check what command user used
int checkCommand(char *command)
{
    int commandIndex = 0;
    const char commandArray[][200] = {"exit-terminal", "help", "clear", "list-files", "current-dir"}; 
    for(int i = 0; i < (int)(sizeof(commandArray)/sizeof(commandArray[0])); i++)
    {
        if(strcmp(commandArray[i], command) == 0)
            commandIndex = i;
    }
    return commandIndex;
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
        case 3:
            listFiles();
            break;
        case 4:
            currentDirectory();
            break;
        default:
            break;
        }
    }
}

int main(void)
{
    mainLoop();
}