Aggelos Kolaitis
vsdirent: A minimum <dirent.h> implementation for Visual Studio

Example:

	....
	#include "vsdirent.h"
	....
	
	DIR *dir = opendir(path);
	struct dirent *ent;
	
	while( ent = readdir(dir) ) {
		cout << ent->d_name << endl;
	}
	
	closedir(dir);
	