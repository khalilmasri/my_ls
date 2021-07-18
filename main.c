#include "file_functions.c"

int main(int argc, char *argv[])
{
    char option;
    option = check_option(argc, argv, 0);

    if (argc == 1)
    {
        my_ls(".", option);
    }
    else if(argc <= 3){
        int index = 1, flag =0;
        while(argv[index]){
            if(check_option(argc, argv, index) != 'N' ){
                flag++;
            }
            index++;
        }

        if(flag == argc-1)
            my_ls(".", option);
        else 
        {
            for (int i = 1; i < argc; i++)
                if (check_option(argc, argv, i) == 'N')
                    if (my_ls(argv[i], option) == 1)
                        printf("my_ls: cannot access '%s': No such file or directory\n", argv[i]);
        }
    }
    return 0;
}
