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

//create directory
void createDirectory()
{
    char *dirName = malloc(FILE_NAME * sizeof(char));
    printf("$:dirname ");
    fgets(dirName, FILE_NAME, stdin);
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
        printf("%serror occurred while creating the folder", RED);
        printf("%s\n", WHITE);
}

//delete file
void deleteFile()
{
    char *fileName = malloc(FILE_NAME * sizeof(char));
    printf("$:filename ");
    fgets(fileName, FILE_NAME, stdin);
    for (int i = 0; i < (int)strlen(fileName); i++)
    {
        if(fileName[i] == '\n')
            fileName[i] = '\0'; 
        else
            fileName[i] = fileName[i];
    }
    if(remove(fileName) == 0)
    {
        printf("%sfile has been deleted", GREEN);
        printf("%s\n", WHITE);
    }
    else
    {
        printf("%sfile does not exist or cannot be deleted", RED);
        printf("%s\n" WHITE);
    }
}

//write to file
void writeToFile()
{
    char *fileName = malloc(FILE_NAME * sizeof(char));
    char *lineContent = malloc(LINE_SIZE * sizeof(char));
    printf("$:filename ");
    fgets(fileName, FILE_NAME, stdin);
    for (int i = 0; i < (int)strlen(fileName); i++)
    {
        if(fileName[i] == '\n')
            fileName[i] = '\0'; 
        else
            fileName[i] = fileName[i];
    }
    FILE *file;
    file = fopen(fileName, "r");
    if(file != NULL)
    {
        file = fopen(fileName, "w");
        printf("$:content ");
        fgets(lineContent, LINE_SIZE, stdin);
        fgets(lineContent, LINE_SIZE, file);
        fprintf(file, "%s", lineContent);
        fclose(file);
        printf("%ssave changes in file", GREEN);
        printf("%s\n", WHITE);
    }
    else
    {
        printf("%sfile does not exist", RED);
        printf("%s\n", WHITE);
    }
}

//read file content
void readFile()
{
    char *fileName = malloc(FILE_NAME * sizeof(char));
    printf("$:filename ");
    fgets(fileName, FILE_NAME, stdin);
    for (int i = 0; i < (int)strlen(fileName); i++)
    {
        if(fileName[i] == '\n')
            fileName[i] = '\0'; 
        else
            fileName[i] = fileName[i];
    }
    FILE *file;
    file = fopen(fileName, "r");
    char *fileContent[NUMBER_OF_LINES];
    __uint16_t index = 0;
    for (__uint16_t i = 0; i < NUMBER_OF_LINES; i++)
        fileContent[i] = malloc(LINE_SIZE * sizeof(char));
    if(file != NULL)
    {
        while (fgets(fileContent[index], NUMBER_OF_LINES, file))
            index++;
        for (__uint16_t i = 0; i < NUMBER_OF_LINES; i++)
            if(strcmp(fileContent[i], "") != 0)
                printf("%d  %s", i, fileContent[i]);
        fclose(file);
        printf("\n");
    }
    else
    {
        printf("%sfile does not exist", RED);
        printf("%s\n", WHITE);
    } 
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
    for (int i = 0; i < (int)strlen(fileName); i++)
    {
        if(fileName[i] == ' ')
            fileName[i] = '_'; 
        else
            fileName[i] = fileName[i];
    }
    FILE *file = fopen(fileName, "r");
    if(file != NULL)
    {
        fclose(file);
        printf("%sfile already exists", RED);
        printf("%s\n", WHITE);
    }
    else
    {
        file = fopen(fileName, "w");
        fclose(file);
        printf("%sfile has been created", GREEN);
        printf("%s\n", WHITE);
    }  
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
        {
            if(direntPointer->d_type == 8)
            {
                printf("%s  ", direntPointer->d_name);
                printf("%s%s", GREEN, "file");
                printf("%s\n", WHITE);
            }
            else if(direntPointer->d_type == 4)
            {
                printf("%s  ", direntPointer->d_name);
                printf("%s%s", BLUE, "directory");
                printf("%s\n", WHITE);
            }
            else
            {
                printf("%s  ", direntPointer->d_name);
                printf("%s%s", RED, "unknown");
                printf("%s\n", WHITE);
            }
        }
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
    printf("read-file >> read file\n");
    printf("wrt-file >> overwrite file\n");
    printf("dlt-file >> delete file\n");
    printf("crt-dir >> create directory\n");
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
    const char *commandArray[] = {"exit-terminal", "help", "clear", "list-files", "current-dir", "change-dir", "crt-file", "read-file", "wrt-file", "dlt-file", "crt-dir"}; 
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
            readFile();
            break;
        case 8:
            writeToFile();
            break;
        case 9:
            deleteFile();
            break;
        case 10:
            createDirectory();
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