#include <iostream>
#include "vsdirent.h"

/* needed for setmode() */
#include <io.h>
#include <fcntl.h>

int main()
{
    WDIR* mydir = wopendir(L".");

    _setmode(_fileno(stdout), _O_U16TEXT);
    struct wdirent *ent = NULL;

    while ((ent = wreaddir(mydir)))
    {
        std::wcout << ent->d_name << std::endl;
    }

    wclosedir(mydir);

    system("pause");

    return 0;
}