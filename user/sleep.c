#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(2, "Usage: sleep times\n");
  }
  int time = atoi(argv[1]);
  if (sleep(time) != 0) {
    fprintf(2, "Error in sys_call sleep!\n");
  }
  exit(0);
}