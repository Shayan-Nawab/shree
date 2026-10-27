#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h> //library for getting min and max values in a datatype; used for realpath()
#include <string.h>

void printUsage(){
  printf("Usage: shree [OPTIONS] [DIRECTORIES]\n");
}

int getFullPath(const char *relative_path, char *full_path){
  return realpath(relative_path, full_path) != NULL; //output is 1 on success, 0 on failure
}

int hiddenFilesFilter(const struct dirent *entry){
  if (entry->d_name[0] == '.') {
    return 0;
  }
  else{
    return 1;
  }
}

void printFile(bool is_file, bool is_last, int depth, const char *name, int *exhaustedDepths, const char *icon){
 
  const char *marker = "├───";
  if (is_last){
    marker = "└───";
  }

  exhaustedDepths[depth] = is_last;

  char depth_string[PATH_MAX] = "";
  for (int i = 1; i < depth; i++) {
    if (exhaustedDepths[i] == 0){
      strcat(depth_string, "│    ");
    }
    else{
      strcat(depth_string, "     ");
    }
  }

  if (!is_file){
    printf("%s%s %s \033[1m%s\033[0m\n", depth_string, marker, icon, name);
  }
  else{
    printf("%s%s %s %s\n", depth_string, marker, icon, name);
  }
}
void printTree(const char *parent_dir, const char *name, int depth, bool is_last, int *exhaustedDepths, const char *icon){
  char dir[PATH_MAX];
  strcpy(dir, parent_dir);
  strcat(dir, "/");
  strcat(dir, name);

  if (depth>0){
    printFile(false, is_last, depth, name, exhaustedDepths, "\033[33m\033[0m");
  }
  struct dirent **list;
  int n = scandir(dir, &list, hiddenFilesFilter, alphasort);
  if (n == -1) { perror(dir); return;}

  for (int i = 0; i < n; i++){
    if ( list[i]->d_type == DT_DIR){
      printTree(dir, list[i]->d_name, depth+1, (i == n-1), exhaustedDepths, "");
    }
    else if (list[i]->d_type == DT_REG){
      printFile(true, (i == n-1), depth+1, list[i]->d_name, exhaustedDepths, "\033[37m\033[0m");
    }
    else if (list[i]->d_type == DT_LNK){
      printFile(true, (i == n-1), depth+1, list[i]->d_name, exhaustedDepths, "\033[36m\033[0m");
    }
    else{
      perror("error\n");
    }
    free(list[i]);
  }
free(list);
}

void combine(int len_dirs, char *dirs[]) {
  for (int i = 1; i < len_dirs; i++){
    char full_path[PATH_MAX];
    if (!getFullPath(dirs[i], full_path)){
      perror(dirs[i]);
      continue;
    }
    printf("\033[33m \033[0m%s:\n", full_path);
    int exhaustedDepths[99];
    printTree("", full_path, 0, false, exhaustedDepths, "");
    printf("\n");
  }
}

//to implement:
//-d (directories only)
//--depth n

