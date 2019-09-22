#include "string.h"
#include "output.h"
#include "file.h"
#include "lists.h"

#include <getopt.h>



#define EXIT_SUCCESS 0
extern void exit (int);

#ifdef WIN
extern void srand (unsigned int);
extern int rand (void);
extern long int time (long int*);
#endif

static list_t* fileList;



static void clearListElement (void *tmp) {
	freeChar ((char**)&tmp);
	free(tmp);
}



static void foundFile (char *name) {
	char* fileName = 0;
	strmcat (&fileName, name);
	insert_list_element (fileList, fileList, fileName);
}



static unsigned int generateRandomNumber() {
	unsigned int randval;
#ifndef WIN
	FILE *f;
	
	f = fopen ("/dev/urandom", "r");
	
	if (fread (&randval, sizeof (randval), 1, f) == 0)
		outerr ("fopen bug\n");
	
	fclose (f);
#else
	srand (time (0));
	randval = rand ();
#endif
	
	return randval;
}



int main (int argc, char** argv) {
	list_t* iterator;
	int num = 0;

///--- opt management
	while (1) {
		int opt;
		static struct option long_options[] =
		{
			{ "help", no_argument, 0, 'h'},
			{ "version", no_argument, 0, 'v'},
			{ 0, 0, 0, 0},
		};
		int option_index = 0;

		opt = getopt_long (argc, argv, "hv", long_options, &option_index);

		if (opt == -1) break;

		switch (opt) {
			case 'h':
				showHelp (argv[0], "");
				exit (EXIT_SUCCESS);
			case 'v':
				showVersion ("randomFile",  "0.8");
				exit (EXIT_SUCCESS);
		}
	}

///--- creates an filelist of given folder
	fileList = new_list ();
	iterator = fileList;

	if (optind < argc) {
		while (optind < argc)
			dirWalk (argv[optind++], foundFile);
	} else {
		dirWalk (".", foundFile);
	}

///--- generate random number
	num = generateRandomNumber() % list_size (fileList);

///--- running thru list of diritems
	for (	register unsigned int i = 0;
			i < num + 1 && i < list_size (fileList);
			++i) {
		iterator = iterator->next;
	}

///--- output random selected direntry
	outplain (iterator->val);
	outplain ("\n");

///--- tidy up memory
	clear_list (fileList, clearListElement);

	exit (EXIT_SUCCESS);
}
