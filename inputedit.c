#include "header.h"

char *copyInputString(char *str, int i)
{
    int chV;
    char *duplicate = malloc(sizeof(char) * strlen(str));

    for(;(chV = str[++i]) != '\0';)
    {
        duplicate[i] = chV;
    }
    duplicate[i] = '\0';
    return duplicate;
}


bool nullSpaceChars(char chV)
{
    if( chV == '\n' ||chV == '\r' )
        return true;
    

    else if(chV == ' ' ||chV == '\t' ||chV == '\x0b' ||chV == '\x0c')
        return true;

    else return false;
}

char *firstCharPointer(char *str, int i)
{
    char *fcp;
        for(i=0; nullSpaceChars(str[i])==true;)
        {
            i++;
        }
    fcp = str + i;
    return fcp;
}

int gettingTheInput( int k, char *str, int w)
{
    int i, chV;
    for (i = 0; i < k - 1 && (chV = getchar()) != '\n'; ++i)
    {
        if (chV == EOF)
            return -1;
        str[i] = chV;
    }
    str[i] = '\0';
    return i;
    
}

char *newStringCopy(char *str, int i)
{
    char *duplicate = malloc(sizeof(char) * strlen(str));;
    int  chV;

   
    for(;(chV = str[++i]) != '\0' && chV != '\n'; )
    {
        duplicate[i] = chV;
    }
    duplicate[i] = '\0';
    return duplicate;
}

char *timeAndDateStr(char *nsc)
{
    time_t timer = time(NULL);
    nsc=newStringCopy(ctime(&timer), -1);
    return nsc;
}

char **arguments(char *inputLine)
{
    char *duplicate = malloc(sizeof(char) * (strlen(inputLine) + 1));
    strcpy(duplicate, inputLine);

    char *arg;
    int i = 0;
    char **args = malloc(sizeof(char *));
    while ((arg = strtok(duplicate, " \t")) != NULL)
    {
        args[i] = malloc(sizeof(char) * (strlen(arg) + 1));
        strcpy(args[i], arg);
        args = realloc(args, sizeof(char *) * (++i + 1));
        duplicate = NULL;
    }
    args[i] = NULL;
    return args;
}