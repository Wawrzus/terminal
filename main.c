#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

#define PATH_SIZE 600
#define COMMAND_SIZE 100
#define FILE_NAME 150
#define READ_FILE_SIZE 300

//writing to file
void viewFile()
{
    char fileName[FILE_NAME];
    printf("$:filename to view: ");
    fgets(fileName, FILE_NAME, stdin);
    for (int i = 0; i < (int)strlen(fileName); i++)
    {
        if(fileName[i] == '\n')
            fileName[i] = '\0'; 
        else
            fileName[i] = fileName[i];
    }

    FILE *file = fopen(fileName, "r");
    char *fileContent[READ_FILE_SIZE];
    for(int i = 0; i < READ_FILE_SIZE; i++)
    {
        fileContent[i] = malloc(READ_FILE_SIZE * sizeof(char));
        if(fileContent == NULL)
            printf("blad alokacji pamieci\n");
    }
    int index = 0;
    if(file != NULL)
    {
        while (fgets(fileContent[index], READ_FILE_SIZE, file)){index++;}
        for(int i = 0; i < (int)(sizeof(fileContent)/sizeof(fileContent[0])); i++)
        {
            if(fileContent[i] != NULL)
                printf("%s", fileContent[i]);
        }
    }
    else
    {
        printf("nie mozna otworzyc pliku");
    }
    printf("\n");
    fclose(file);
}

//creating file
void createFile()
{
    char fileName[FILE_NAME];
    printf("$:filename: ");
    fgets(fileName, FILE_NAME, stdin);
    for (int i = 0; i < (int)strlen(fileName); i++)
    {
        if(fileName[i] == '\n')
            fileName[i] = '\0'; 
        else
            fileName[i] = fileName[i];
    }

    FILE *file = fopen(fileName, "r");
    if(file != NULL)
    {
        fclose(file);
        printf("taki plik juz istnieje\n");
        return;
    }

    if(file == NULL)
    {
        printf("blad podczas otwierania pliku");
        return;
    }

    file = fopen(fileName, "w");
    fclose(file);
    printf("plik utworzony pomyslnie\n");
}

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
    printf("crt-file >> create file\n");
    printf("view-file >> edit file\n");
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
    const char *commandArray[] = {"exit-terminal", "help", "clear", "list-files", "current-dir", "change-dir", "crt-file", "view-file"}; 
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
        case 6:
            createFile();
            break;
        case 7:
            viewFile();
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