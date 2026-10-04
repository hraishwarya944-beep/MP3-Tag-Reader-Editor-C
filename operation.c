#include "main.h"

int invalid_command()
{
    printf(RED"\nERROR : ./a.out : INVALID ARGUMENTS\n");
    printf("USAGE :\nTo view please pass like :  ./a.out -e -t/-a/-A/-m/-y/-c  changing_text mp3filename\n");
    printf("To get help pass like :  ./a.out --help\n\n"RESET);
    return FAILURE;
    
}

int display_help()
{
    int i;
    printf(YELLOW"\n");
    for(i = 0 ; i < 20 ; i++)
    {
        printf("-");
    }
    printf("HELP MENU");
    for(i = 0 ; i < 20 ; i++)
    {
        printf("-");
    }
    printf("\n\n");

    printf("1. -v -> To view mp3 file contents\n2. -e -> to view mp3 file contents\n");
    printf("\t2.1. -t -> to edit song title\n\t2.2. -a -> to edit artist name\n"
            "\t2.3. -A -> to edit album name\n"
            "\t2.4. -y -> to edit year\n"
            "\t2.5. -m -> to edit content\n"
            "\t2.6. -c -> to edit comment\n\n");

    for(i = 0 ; i < 50 ; i++)
    {
        printf("-");
    }
    printf("\n\n"RESET);
    return SUCCESS;
}

int validate_mp3(char *argv)
{
    char file[4];
    char version[3];
    FILE *fp;
    fp = fopen(argv , "r");
    if(fp == NULL)
    {
        perror(RED"ERROR "RESET);
        return FAILURE;
    }

    //To check if it has ID3 at the beginning
    fread(file , 1 , 3 , fp);
    file[3] = '\0';
    // printf("%s\n",file);
    
    if(strcmp(file , "ID3") != 0)
    {
        return FAILURE;
    }


    //To check the version if it is 03 00
    fread(version , 1 , 2 , fp);
    version[2] = '\0';
    if(!(version[0] == 0x03 && version[1] == 0x00))
    {
        return FAILURE;
    }


    //To check if it has .mp3 extension
    if(strstr(argv,".mp3") == NULL)
    {
        return FAILURE;
    }

    fclose(fp);
    return SUCCESS;

}