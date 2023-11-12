#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

void new_proc(int p[2]) {
  int primer;
  close(p[1]);
  if (read(p[0], &primer, 4) == 4) {
    printf("prime %d\n", primer);
    int new_p[2];
    pipe(new_p);
    if (fork() != 0) {
      close(new_p[0]);
      int num;
      while (read(p[0], &num, 4) == 4)
        if (num % primer)
          write(new_p[1], &num, 4);
      close(p[0]);
      close(new_p[1]);
      exit(0);
    } else {
      new_proc(new_p);
    }
  }
}

int main() {
  int p[2];
  pipe(p);
  if (fork() == 0) {
    new_proc(p);
  } else {
    close(p[0]);
    for (int i = 2; i <= 35; i++) {
      write(p[1], &i, 4);
    }
    close(p[1]);
    exit(0);
  }
  return 0;
}