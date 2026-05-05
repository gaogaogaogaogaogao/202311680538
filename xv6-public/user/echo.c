#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i;
  
  printf(1, "[USER] calling write\n");   // 任务1：用户态打印

  for(i = 1; i < argc; i++){
    write(1, argv[i], strlen(argv[i]));
    write(1, " ", 1);
  }
  write(1, "\n", 1);
  exit();
}