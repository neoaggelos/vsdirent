#include <iostream>
#include "vsdirent.h"

int main()
{
    DIR* mydir = opendir(".");

    struct dirent *ent = NULL;

    while ((ent = readdir(mydir)))
    {
        std::cout << ent->d_name << std::endl;
    }

    closedir(mydir);
}