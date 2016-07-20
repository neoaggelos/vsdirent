#include "vsdirent.h"

#include <iostream>
#include <cstring>

using std::string;

DIR*
opendir(const char* path)
{
	DIR * dir = new DIR();
	dir->ent = new struct dirent();

	/* open handle and read first file */
	string regex = string(path) + "\\*";
	dir->h = FindFirstFileA(regex.c_str(), &(dir->data));

	/* if we fail return NULL */
	if (dir->h == INVALID_HANDLE_VALUE)
	{
		delete dir;
		return NULL;
	}

	/* otherwise, prepare for readdir() */
	dir->ent->d_name = _strdup(dir->data.cFileName);
	dir->readFirstFile = true;

	return dir;
}

struct dirent*
readdir(DIR *dir)
{
	if (dir == NULL)
		return NULL;

	/* this is a hack to workaround how FindFirstFile() works */
	if (dir->readFirstFile)
	{
		dir->readFirstFile = false;
		return dir->ent;
	}

	/* we must read the next file and return it */
	if (FindNextFileA(dir->h, &(dir->data)))
	{
		dir->ent->d_name = _strdup(dir->data.cFileName);
		return dir->ent;
	}

	/* no more files */
	return NULL;
}

void
closedir(DIR *dir)
{
	if (dir == NULL)
		return;

	FindClose(dir->h);
	delete dir->ent;
	delete dir;
}

#ifndef VSDIRENT_NO_WCHAR

using std::wstring;

WDIR*
wopendir(const wchar_t* path)
{
    WDIR * dir = new WDIR();
    dir->ent = new struct wdirent();

    /* open handle and read first file */
    wstring regex = wstring(path) + L"\\*";
    dir->h = FindFirstFileW(regex.c_str(), &(dir->data));

    /* if we fail return NULL */
    if (dir->h == INVALID_HANDLE_VALUE)
    {
        delete dir;
        return NULL;
    }

    /* otherwise, prepare for readdir() */
    dir->ent->d_name = _wcsdup(dir->data.cFileName);
    dir->readFirstFile = true;

    return dir;
}

struct wdirent*
wreaddir(WDIR *dir)
{
    if (dir == NULL)
        return NULL;

    /* this is a hack to workaround how FindFirstFile() works */
    if (dir->readFirstFile)
    {
        dir->readFirstFile = false;
        return dir->ent;
    }

    /* we must read the next file and return it */
    if (FindNextFileW(dir->h, &(dir->data)))
    {
        dir->ent->d_name = _wcsdup(dir->data.cFileName);
        return dir->ent;
    }

    /* no more files */
    return NULL;
}

void
wclosedir(WDIR *dir)
{
    if (dir == NULL)
        return;

    FindClose(dir->h);
    delete dir->ent;
    delete dir;
}

#endif /* !defined (VSDIRENT_NO_WCHAR) */