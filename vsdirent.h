#ifndef _vsdirent_h
#define _vsdirent_h

#include <Windows.h>

extern "C" {

    /* We only implement d_name */
    struct dirent {
        const char *d_name;
    };

    /* The DIR struct */
    typedef struct {
        /* WinAPI specifics */
        HANDLE h;
        WIN32_FIND_DATAA data;

        /* We are responsible for allocating-freeing the dirent memory */
        struct dirent *ent;

        /* This is to not lose file data from FindFirstFile() */
        bool readFirstFile;
    } DIR;

    /* The implemented functions */
    DIR *opendir(const char* path);
    struct dirent* readdir(DIR *dir);
    void closedir(DIR* dir);


#ifndef VSDIRENT_NO_WCHAR

#include <cwchar>

    struct wdirent {
        const wchar_t *d_name;
    };

    typedef struct {
        HANDLE h;
        WIN32_FIND_DATAW data;

        struct wdirent *ent;

        bool readFirstFile;
    } WDIR;

    WDIR *wopendir(const wchar_t *path);
    struct wdirent* wreaddir(WDIR* dir);
    void wclosedir(WDIR *dir);

}

#endif /* !defined (VSDIRENT_NO_WCHAR) */

#endif /* _vsdirent_h */