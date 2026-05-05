#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  int pid = getpid();
  int pid_plus = getpid_plus();
  printf(1, "My PID: %d, PID+1: %d\n", pid, pid_plus);
  exit();
}