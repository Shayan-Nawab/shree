#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#include "shree.h"


// Input can have any no. of directories, all of them can be tree'd one after another
int main(int argc, char *argv[]) {
  if (argc == 1) { // 'shree' functionally equivalent to 'shree .'
    char *cwd[] =  {"filler", "."};
    combine(2, cwd);
  }
  else {
    combine(argc, argv);
  }
  exit(0);
}

