#include <Windows.h>

/* For our implementation we only need ent->d_name */
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