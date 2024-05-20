/**
 * spagetti.c - returns a random file from given or actual direcory
 * Copyright © 2014 - Niels Neumann  <vatriani.nn@googlemail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#ifdef _WIN32
	#include <stdlib.h> 
	#include <time.h>
#endif	


// getting random number from /dev/random or on an windows enviroment from srand
unsigned int generateRandomNumber () {
  unsigned int randval;

#ifdef _WIN32  // Windows definition
  srand ( time( NULL ) ); // seed the random number generator
  randval = rand ( );
#else
  FILE* file;

  file = fopen ( "/dev/random", "r" );

  if ( !fread ( &randval, sizeof ( randval ), 1, file ) )
    puts ( "error in generateRandomNumber" );

  fclose ( file );
#endif

	return randval;
}

int main ( int argc, char** argv ) {
  DIR *dp;
  struct dirent *ep;
  register unsigned int count;
  register unsigned int random;

  count = 0;
  random = 0;

  if ( argc > 1 ) dp = opendir ( argv[1] );
  else dp = opendir ( "." );

  while ( (ep = readdir ( dp )) != NULL ) ++count;

  rewinddir ( dp );

  do {
    random = generateRandomNumber () % ( count -1 );

    while ( ( ep = readdir ( dp ) ) && ( random != 0 ) ) --random;

  } while ( !strcmp ( ep->d_name, "." ) || !strcmp ( ep->d_name, ".." ) );

  puts ( ep->d_name );

  closedir ( dp );

  return 0;
}
