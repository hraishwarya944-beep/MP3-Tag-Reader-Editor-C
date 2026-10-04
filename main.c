#include "main.h"

int main(int argc , char *argv[])
{
    int i;
    if(argc == 1)
    {
        invalid_command();
        return FAILURE;
    }
    else
    {
        if(strcasecmp(argv[1],"--help") == 0)
        {
            display_help();
            return FAILURE;
        }
        else if(strcasecmp(argv[1],"-v") == 0)
        {
            if(view_mp3(argv) == FAILURE)
                return FAILURE;
        }
        else if(strcasecmp(argv[1],"-e") == 0)
        {
            edit_mp3(argc , argv);
            return FAILURE;
        }
        else
        {
            invalid_command();
            return FAILURE;
        }
    }
    
}