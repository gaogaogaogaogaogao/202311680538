// kernel/main.c - 内核主函数

#include "types.h"

// 内核入口函数
int main(void) {
  // 打印内核启动信息
  cprintf("[KERNEL] main() started\n");
  
  // 以下是xv6内核的实际初始化步骤：
  // 1. 初始化控制台
  // 2. 初始化内存管理
  // 3. 初始化页表
  // 4. 初始化中断控制器
  // 5. 创建第一个进程
  // 6. 启动调度器
  
  // 实际main函数不会返回
  // 这里返回0仅用于演示
  return 0;
}
