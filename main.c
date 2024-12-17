#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void mainLoop()
{
    char choseCommand[100];
    while (strcmp("exit-terminal", choseCommand) != 0)
    {
        printf("%s", "Wpisz komende: ");
        scanf("%s", choseCommand);
    }
}

int main()
{
    mainLoop();
}