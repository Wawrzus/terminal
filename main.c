#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

#define PATH_SIZE 1024
#define COMMAND_SIZE 200

//change working directory
void changeDirectory()
{
    char dirName[COMMAND_SIZE];
    printf("$:dirname: ");
    fgets(dirName, sizeof(dirName), stdin);
    for (int i = 0; i < (int)strlen(dirName); i++)
    {
        if(dirName[i] == '\n')
            dirName[i] = '\0'; 
        else
            dirName[i] = dirName[i];
    }
    chdir(dirName);
}

//list content of current directory
void listFiles()
{
    struct dirent *direntPointer;
    DIR *dir = opendir(".");
    while((direntPointer = readdir(dir)) != NULL)
        if(direntPointer->d_name[0] != '.')
            printf("%s\n", direntPointer->d_name);
    closedir(dir);
}

//check current direcotry path
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
    printf("list-files >> list current directory content\n");
    printf("current-dir >> show current path\n");
    printf("change-dir >> change working directory\n");
}

//check what command user used
int checkCommand(char *command)
{
    for (int i = 0; i < (int)strlen(command); i++)
    {
        if(command[i] == '\n')
            command[i] = '\0'; 
        else
            command[i] = command[i];
    }
    int commandIndex = 0;
    const char commandArray[][200] = {"exit-terminal", "help", "clear", "list-files", "current-dir", "change-dir"}; 
    for(int i = 0; i < (int)(sizeof(commandArray)/sizeof(commandArray[0])); i++)
    {
        if(strcmp(commandArray[i], command) == 0)
            commandIndex = i;
    }
    return commandIndex;
}

void mainLoop()
{
    char command[COMMAND_SIZE];
    while (strcmp("exit-terminal", command) != 0)
    {
        char directory[PATH_SIZE];
        printf("%s $: ", getcwd(directory, PATH_SIZE));
        fgets(command, sizeof(command), stdin);
        checkCommand(command);
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
        case 5:
            changeDirectory();
            break;
        default:
            break;
        }
    }
}

int main(void)
{
    mainLoop();
    return 0;
}