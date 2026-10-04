#include "main.h"

int view_mp3(char *argv[])
{
    int i;
    FILE *fp;
    int count = 0;

    char tag[5];
    unsigned char tagsize[5];
    
    int size;

    if(validate_mp3(argv[2]) == FAILURE)
    {
        return FAILURE;
    }
    fp = fopen(argv[2] , "r");

    if(fp == NULL)
    {
        perror(RED"ERROR "RESET);
        return FAILURE;
    }
    fseek(fp , 10 , SEEK_SET);                       //skip 10 bytes of header bytes

    printf("\n");
    for(i = 0 ; i < 30 ; i++)
    {
        printf("-");
    }
    printf("SELECTED VIEW OPTION");
    for(i = 0 ; i < 30 ; i++)
    {
        printf("-");
    }
    printf("\n\n");

    for(i = 0 ; i < 20 ; i++)
    {
        printf("-");
    }
    printf("MP3 TAG READER AND EDITOR FOR ID3v2");
    for(i = 0 ; i < 25 ; i++)
    {
        printf("-");
    }
    printf("\n\n");


    while(count < 6)
    {

        fread(tag , 1 , 4 , fp);                         //read first tag of 4 bytes and store as a string
        tag[4] = '\0';
        // printf("%s\n",tag);
        

        fread(tagsize , 1 , 4 , fp);                     //read the size which is in syncsafe and store in string
        tagsize[4] = '\0';

        size = ((unsigned int)tagsize[0] << 24)|                        //convert big endian to little endian
                ((unsigned int)tagsize[1] << 16)|
                ((unsigned int)tagsize[2] << 8)|
                ((unsigned int)tagsize[3]);

        // printf("\n%d",size);




        if((strcmp(tag , "TIT2") == 0) ||
           (strcmp(tag , "TPE1") == 0) ||
           (strcmp(tag , "TALB") == 0) ||
           (strcmp(tag , "TYER") == 0) ||
           (strcmp(tag , "TCON") == 0) ||
           (strcmp(tag , "TCOM") == 0))
        {
            char titlename[size];
            fseek(fp , 2 , SEEK_CUR);                          //skip 2 bytes of flag

            fseek(fp , 1 , SEEK_CUR);                          //skip encoding byte(first byte) in the given size

            fread(titlename , 1 , size - 1 , fp);
            titlename[size - 1] = '\0';
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
            printf("%s\n",titlename);
            count++;
        }
        else
        {
            fseek(fp, 2, SEEK_CUR);      // skip flags
            fseek(fp, size, SEEK_CUR);   // skip unwanted data
        }
    }
    
    fclose(fp);


    for(i = 0 ; i < 60 ; i++)
    {
        printf("-");
    }
    for(i = 0 ; i < 20 ; i++)
    {
        printf("-");
    }
    printf("\n\n");
    for(i = 0 ; i < 25 ; i++)
    {
        printf("-");
    }
    printf("DETAILS DISPLAYED SUCCESSFULLY");
    for(i = 0 ; i < 25 ; i++)
    {
        printf("-");
    }
    printf("\n\n");
    return SUCCESS;
}