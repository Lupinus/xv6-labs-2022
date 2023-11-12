#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

void find(char *path, char *name) {
  char buf[512], *p;
  int fd;
  // dir descriptor
  struct dirent de;
  // file descriptor
  struct stat st;

  if ((fd = open(path, 0)) < 0) {
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) == -1) {
    fprintf(2, "find: cannot fstat %s\n", path);
    close(fd);
    return;
  }
  // printf("switch to '%s'\n", path);
  switch (st.type) {

  case T_DEVICE:
  case T_FILE:
    fprintf(2, "find: %s not a path value.\n", path);
    close(fd);
    // printf("==='%s' is a File\n", path);
    break;
  case T_DIR:
    // printf("==='%s' is a dir\n", path);
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
      printf("ls: path too long\n");
      break;
    }
    // create full path
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    // read dir infomation for file and dirs
    while (read(fd, &de, sizeof(de)) == sizeof de) {
      if (de.inum == 0)
        continue;
      if (strcmp(".", de.name) == 0 || strcmp("..", de.name) == 0)
        continue;
      // copy file name to full path
      memmove(p, de.name, DIRSIZ);
      // create a string with zero ending.
      p[DIRSIZ] = '\0';
      // stat each of files
      if (stat(buf, &st) == -1) {
        fprintf(2, "find: cannot stat '%s'\n", buf);
        continue;
      }
      // printf("===file:'%s'\n", buf);
      if (st.type == T_DEVICE || st.type == T_FILE) {
        if (strcmp(name, de.name) == 0) {
          printf("%s\n", buf);
          // for (int i = 0; buf[i] != '\0'; ++i) {
          //     printf("'%d'\n", buf[i]);
          // }
        }
      } else if (st.type == T_DIR) {
        find(buf, name);
      }
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(2, "Usage: find path file.\n");
    exit(0);
  }
  char *path = argv[1];
  char *name = argv[2];
  // printf("path is '%s'\n", path);
  find(path, name);
  exit(0);
}