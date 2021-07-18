#include "structs_includes.c"

int my_strlen(char *str)
{
    int index = 0;
    while (str[index] != '\0')
        index++;
    return index;
}

char *my_strcat(char *path, char *dirName)
{
    int size, index = 0;
    size = my_strlen(path);
    while (dirName[index])
    {
        path[size + index] = dirName[index];
        index++;
    }
    path[size + index] = '\0';
    return path;
}

char *my_strcpy(char *dest, char *src)
{
    int index = 0;
    while (src[index])
    {
        dest[index] = src[index];
        index++;
    }
    dest[index] = '\0';
    return dest;
}

int my_strcmp(char *string, char *compare)
{
    while (*string && (*string == *compare))
    {
        string++;
        compare++;
    }
    return (*string - *compare);
}