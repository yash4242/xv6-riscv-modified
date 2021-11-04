#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int n_proc = 10;

int
main(void) 
{

  set_priority(5, getpid());
  for (int i = 0; i < n_proc; i++) {
    int pid = fork();

    if (!pid) {
      for (volatile int i = 0; i < 1000000000; i++) {
        ;
      }
      printf("Ded %d\n", i);
      exit();
    } else {
      set_priority(60 - i, pid);
      printf("Index: %d Pid: %d\n", i, pid);
    }
  }

  for (int i = 0; i < n_proc; i++) {
    wait();
  }

  exit(0);
}