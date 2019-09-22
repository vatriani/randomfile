#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

unsigned int generateRandomNumber () {
 	unsigned int randval;
	FILE* file;

	file = fopen ("/dev/random", "r");
	if(!fread (&randval, sizeof (randval), 1, file))
		puts("error in generateRandomNumber");

	fclose (file);

	return randval;
}

int main () {
	DIR *dp;
	struct dirent *ep;
	register unsigned int count;
	register unsigned int random;

	count = 0;
	random = 0;
	dp = opendir (".");

	while ( (ep = readdir (dp)) != NULL )
		++count;

	rewinddir (dp);

	do {
		random = generateRandomNumber () % (count-1);

		while ( (ep = readdir (dp) ) && (random != 0) )
			--random;

	} while ( !strcmp (ep->d_name, ".") || !strcmp (ep->d_name, "..") );

	puts (ep->d_name);

	closedir (dp);

	return 0;
}
