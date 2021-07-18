#include "string_functions.c"
int my_checkfile(char *fileName)
{
    int index = 0;
    int flag = 0;

    char *directory = malloc(sizeof(char *) * 100);
    char *file = malloc(sizeof(char *) * 100);

    while (fileName[index])
    {
        if (fileName[index] == '/')
            flag = index;
        index++;
    }

    if (flag == 0)
    {
        directory = ".";
    }
    else
    {
        flag++;
        index = flag;
        int i = 0;
        while (fileName[index])
        {
            file[i] = fileName[index];
            index++;
            i++;
        }
        index = 0;
        while (flag != 0)
        {
            directory[index] = fileName[index];
            index++;
            flag--;
        }
        fileName = file;
    }
    if (directory)
    {
        DIR *dir = opendir(directory);
        if (dir == NULL)
            return 0;
        struct dirent *currentFile;
        currentFile = readdir(dir);
        while (currentFile != NULL)
        {
            if (my_strcmp(fileName, currentFile->d_name) == 0)
            {
                return 1;
            }
            currentFile = readdir(dir);
        }
    }
    return 0;
}

int check_hidden(char *directory)
{
    if (directory[0] == '.')
        return 1;
    return 0;
}

int count_files(char *directory, char option)
{

    DIR *dir = opendir(directory);

    struct dirent *currentDir;
    currentDir = readdir(dir);
    int count = 0;

    while (currentDir)
    {
        if (option == 't' || option == 'N')
        {
            if (check_hidden(currentDir->d_name) == 0)
                count++;
        }
        else if (option == 'b'|| option == 'a')
        {
            count++;
        }
        currentDir = readdir(dir);
    }
    return count;
}

char check_option(int argc, char *argv[], int index)
{
    char flag = 'N';
    if (index != 0)
    {
        if (argv[index][0] == '-')
        {
            return 'o';
        }
        else
            return 'N';
    }

    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            for (int j = 1; j < my_strlen(argv[i]); j++)
            {
                if (argv[i][j] == 'a' && flag != 't')
                {
                    flag = 'a';
                }
                else if (argv[i][j] == 'a' && flag == 't')
                {
                    return 'b';
                }
                if (argv[i][j] == 't' && flag != 'a')
                {
                    flag = 't';
                }
                else if (argv[i][j] == 't' && flag == 'a')
                {
                    return 'b';
                }
            }
        }
    }
    return flag;
}

void print_loxi(int size, sorted_files *file)
{
    char *temp = malloc (sizeof(char*)* 256);

    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (my_strcmp(file[i].file, file[j].file) > 0)
            {
                my_strcpy(temp, file[i].file);
                my_strcpy(file[i].file, file[j].file);
                my_strcpy(file[j].file, temp);
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        printf("%s  ", file[i].file);
    }
}

long long modify_time(char *dirName)
{
    struct stat st;
    int ret = lstat(dirName, &st);
    if (ret == -1)
        return 0;
    return((st.st_mtim.tv_sec*1e+9)+st.st_mtim.tv_nsec);
}

void my_sort(int size, sorted_files *file)
{
    long long temp;
    char tempFile[256];
    for (int i = 0; i < size; i++)
    {
         for (int j = i + 1; j < size; j++)
        {
            if (file[i].order <= file[j].order)
            {
                temp = file[i].order;
                strcpy(tempFile, file[i].file);
                file[i].order = file[j].order;
                strcpy(file[i].file, file[j].file);
                file[j].order = temp;
                strcpy(file[j].file, tempFile);
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
         for (int j = i + 1; j < size; j++)
        {
            if (file[i].order <= file[j].order && my_strcmp(file[i].file, file[j].file) > 0)
            {
                temp = file[i].order;
                my_strcpy(tempFile, file[i].file);
                file[i].order = file[j].order;
                my_strcpy(file[i].file, file[j].file);
                file[j].order = temp;
                my_strcpy(file[j].file, tempFile);
            }
        }
    }
}

void print_sorted(int size, sorted_files *files)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%s  ", files[i].file);
    }
}

int my_ls(char *dirName, char option)
{
    int index, size;
    sorted_files *sortFiles;

    DIR *dir = opendir(dirName);
    if (dir == NULL)
    {
        if (my_checkfile(dirName) == 1)
        {
            return 0;
        }
        else
            return 1;
    }
    struct dirent *currentFile;
    currentFile = readdir(dir);

    size = count_files(dirName, option);
    sortFiles = (sorted_files *)malloc(sizeof(sorted_files *) * size); 

    switch (option)
    {
    case 't':
        for (index = 0; currentFile;)
        {
            if (check_hidden(currentFile->d_name) == 0)
            {
                my_strcpy(sortFiles[index].file, dirName);
                my_strcat(sortFiles[index].file, "/");
                my_strcat(sortFiles[index].file, currentFile->d_name);
                sortFiles[index].order = modify_time(sortFiles[index].file);
                my_strcpy(sortFiles[index].file, currentFile->d_name);
                index++;
            }
            currentFile = readdir(dir);
        }
        my_sort(size, sortFiles);
        print_sorted(size, sortFiles);
        break;
    case 'a':
        for (index = 0; currentFile;index++)
        {
                my_strcpy(sortFiles[index].file, dirName);
                my_strcat(sortFiles[index].file, "/");
                my_strcat(sortFiles[index].file, currentFile->d_name);
                my_strcpy(sortFiles[index].file, currentFile->d_name);
            currentFile = readdir(dir);
        }
        print_loxi(size, sortFiles);
        break;
    case 'b':
        for (index = 0; index < size; index++)
        {
            strcpy(sortFiles[index].file, dirName);
            my_strcat(sortFiles[index].file, "/");
            my_strcat(sortFiles[index].file, currentFile->d_name);
            sortFiles[index].order = modify_time(sortFiles[index].file);
            strcpy(sortFiles[index].file, currentFile->d_name);
            currentFile = readdir(dir);
        }
        my_sort(size, sortFiles);
        print_sorted(size, sortFiles);
        break;
    default:
        for (index = 0; currentFile;)
        {
            if (check_hidden(currentFile->d_name) == 0)
            {
                my_strcpy(sortFiles[index].file, dirName);
                my_strcat(sortFiles[index].file, "/");
                my_strcat(sortFiles[index].file, currentFile->d_name);
                my_strcpy(sortFiles[index].file, currentFile->d_name);
                index++;
            }
            currentFile = readdir(dir);
        }
        print_loxi(size, sortFiles);
        break;
    }
    closedir(dir);
    printf("\n");
    return 0;
}