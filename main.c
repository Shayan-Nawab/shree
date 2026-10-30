#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "shree.h"

int main(int argc, char *argv[]) {
  
  int numDirs = 0;
  char *dirs[argc];
  int maxDepth = 99;
  bool dirsOnly = false;

  parseInput(argc, argv, dirs, &numDirs, &dirsOnly, &maxDepth);
  combine(numDirs, dirs, maxDepth, dirsOnly);
  exit(0);
}
