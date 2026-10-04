#include "main.h"

int edit_mp3(int argc , char *argv[])
{
    int i;
    FILE *fp;
    FILE *tp;

    unsigned char memory[1024];
    size_t bytes;

    char search_tag[5];
    char tagsize[4];
    int size;
    char flag[2];
    unsigned char encode;
    

    char new_name[30];
    unsigned char new_tag[4];
    int new_size;
    char tag[5];

    
    int pending;

    if(argc < 5)
    {
        printf(RED"Pass tag with the new field name...!\n"RESET);
        return FAILURE;
    }

    if(validate_mp3(argv[4]) == FAILURE)
    {
        printf(RED"MP3 file is not valid...!"RESET);
        return FAILURE;
    }

    
    fp = fopen(argv[4] , "r+");
    tp = fopen("temp.mp3","w+");

    if(fp == NULL && tp == NULL)
    {
        perror(RED"ERROR :"RESET);
    }


    fread(memory , 1 , 10 , fp);
    fwrite(memory , 1 , 10 , tp);

    
    printf("\n");
    for(i = 0 ; i < 15 ; i++)
    {
        printf("-");
    }
    printf("SELECTED EDIT OPTION");
    for(i = 0 ; i < 15 ; i++)
    {
        printf("-");
    }
    printf("\n\n");

    int id3_size;

    id3_size = ((memory[6] & 0x7F) << 21) |
            ((memory[7] & 0x7F) << 14) |
            ((memory[8] & 0x7F) << 7)  |
            (memory[9] & 0x7F);

    long int id3_end = 10 + id3_size;

    for(i = 0 ; i < 10 ; i++)
    {
        printf("-");
    }
    if(strcmp(argv[2] , "-t") == 0)
    {
        strcpy(tag,"TIT2");
        printf("CHANGE THE TITLE");
    }
    else if(strcmp(argv[2] , "-a") == 0)
    {
        strcpy(tag,"TPE1");
        printf("CHANGE THE ARTIST");
    }
    else if(strcmp(argv[2] , "-A") == 0)
    {
        strcpy(tag,"TALB");
        printf("CHANGE THE ALBUM");
    }
    else if(strcmp(argv[2] , "-y") == 0)
    {
        strcpy(tag,"TYER");
        printf("CHANGE THE YEAR");
    }
    else if(strcmp(argv[2] , "-m") == 0)
    {
        strcpy(tag,"TCON");
        printf("CHANGE THE CONTENT");
    }
    else if(strcmp(argv[2] , "-c") == 0)
    {
        strcpy(tag,"TCOM");
        printf("CHANGE THE COMMENT");
    }
    else
    { 
        printf(RED"Send the valid TAG...!"RESET);
        return FAILURE;
    }
    for(i = 0 ; i < 10 ; i++)
    {
        printf("-");
    }
    strcpy(new_name , argv[3]);

    new_size = strlen(new_name) + 1;

    new_tag[0] = (new_size >> 24) & 0xFF;
    new_tag[1] = (new_size >> 16) & 0xFF;
    new_tag[2] = (new_size >> 8) & 0xFF;
    new_tag[3] = new_size & 0xFF;


    while(ftell(fp) < id3_end)
    {
        fread(search_tag , 1 , 4 , fp);
        search_tag[4] = '\0';

        fread(tagsize , 1 , 4 , fp);

        size = (unsigned char)tagsize[0] << 24 |
                (unsigned char)tagsize[1] << 16 |
                (unsigned char)tagsize[2] << 8 |
                (unsigned char)tagsize[3] ;

        pending = size - 1;

        fread(flag , 1 , 2 , fp);
        fread(&encode , 1 , 1 , fp);

        if(strcmp(search_tag , tag) == 0)
        {
            fwrite(search_tag , 1 , 4 , tp);
            fwrite(new_tag , 1 , 4 , tp);
            fwrite(flag , 1 , 2 , tp);
            fwrite(&encode , 1 , 1 , tp);
            fwrite(new_name , 1 , strlen(new_name) , tp);

            fseek(fp, size - 1, SEEK_CUR);
        }
        else
        {
            fwrite(search_tag , 1 , 4 , tp);
            fwrite(tagsize , 1 , 4 , tp);
            fwrite(flag , 1 , 2 , tp);
            fwrite(&encode , 1 , 1 , tp);
            while(pending > 0)
            {
                bytes = fread(memory , 1 , size > 1024 ? 1024 : pending , fp);
                fwrite(memory , 1 , bytes , tp);
                pending = pending - bytes;
            }
            
        }
        
    }


    while ((bytes = fread(memory, 1, sizeof(memory), fp)) > 0)
    {
        fwrite(memory, 1, bytes, tp);
    }
    printf("\n\n");

    if(strcmp(tag , "TIT2") == 0)
    {
        printf("%-10s","TITLE");
    }
    if(strcmp(tag , "TPE1") == 0)
    {
        printf("%-10s","ARTIST");
    }
    if(strcmp(tag , "TALB") == 0)
    {
        printf("%-10s","ALBUM");
    }
    if(strcmp(tag , "TYER") == 0)
    {
        printf("%-10s","YEAR");
    }
    if(strcmp(tag , "TCON") == 0)
    {
        printf("%-10s","CONTENT");
    }
    if(strcmp(tag , "TCOM") == 0)
    {
        printf("%-10s","COMMENT");
    }
    printf(" : ");
    printf("%s\n\n",new_name);
    for(i = 0 ; i < 10 ; i++)
    {
        printf("-");
    }
    
    printf("SUCCESSFULLY MADE CHANGES...!");
    for(i = 0 ; i < 10 ; i++)
    {
        printf("-");
    }
    printf("\n\n");

    fclose(fp);
    fclose(tp);


    remove(argv[4]);
    rename("temp.mp3", argv[4]);
    
    return SUCCESS;
}