#include "vsdirent.h"

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
