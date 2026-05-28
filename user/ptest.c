#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 3){
    printf("usage: ptest pid priority\n");
    exit(1);
  }

  int pid = atoi(argv[1]);
  int priority = atoi(argv[2]);

  int ret = setpriority(pid, priority);

  if(ret == 0)
    printf("setpriority success: pid=%d priority=%d\n", pid, priority);
  else
    printf("setpriority failed\n");

  exit(0);
}
