#ifndef SHREE_H
#define SHREE_H

void printUsage();
void combine(int len_dirs, char *dirs[], int maxDepth, bool dirsOnly);
void parseInput(int argc, char **argv, char **dirs, int *numDirs, bool *dirsOnly, int *maxDepth);

#endif
