# xv6 读书实践周实验报告

## 实验内容说明

- **第一层**  
  - 任务1：系统调用路径跟踪 – 在 `echo.c` 添加 `[USER] calling write`，在 `syscall.c` 添加内核入口打印，在 `sys_write` 添加调用打印  
  - 任务2：调度过程观察 – 在 `scheduler()` 添加 `[SCHED] switch to pid=...`  
  - 任务3：内存分配观察 – 在 `kalloc()` 添加 `[MEM] alloc page at ...`

- **第二层**  
  - 任务1：新增系统调用 `getpid_plus` – 返回 `pid + 1`，并编写用户测试程序 `test_getpid`

## 一项任务的实现过程（以第二层任务1为例）

### 新增系统调用 `getpid_plus`

**步骤**：
1. 在 `syscall.h` 中分配系统调用号 `SYS_getpid_plus 23`
2. 在 `syscall.c` 中添加外部声明和函数指针
3. 在 `sysproc.c` 中实现 `sys_getpid_plus(void)`
4. 在 `user.h` 中添加 `int getpid_plus(void);`
5. 在 `usys.S` 中添加 `SYSCALL(getpid_plus)`
6. 编写 `test_getpid.c` 并在 Makefile 中添加编译规则

## 遇到的问题及解决方法

- **问题1**：编译时提示 `sys_getpid_plus` 未定义  
  **解决**：检查 `syscall.c` 中是否添加了 `extern int sys_getpid_plus(void);` 以及 `syscalls` 数组注册。
- **问题2**：`cprintf` 输出太多干扰  
  **解决**：可以按需注释部分日志，但为了展示效果保留全部。

## 实践心得

通过本次实践，我深刻理解了操作系统系统调用的完整路径：从用户程序调用库函数，到触发软中断，再到内核根据系统调用号分发执行。在 `echo.c` 中添加的打印让我看到用户态与内核态的分界线。调度器的日志让我直观感受到时间片轮转如何实现多个进程“同时”运行。内存分配日志展示了简单的空闲链表管理，分配地址往往是连续的，释放后会被复用。

新增系统调用 `getpid_plus` 的过程让我体会到内核扩展的基本步骤，虽然只是简单的返回 pid+1，但涉及从用户态到内核态的完整流程。通过修改 Makefile 添加用户程序，也熟悉了 xv6 的编译体系。

这次实验让我明白，操作系统不是一个黑盒，而是一个可以逐步拆解、修改、观察的复杂系统。每一次打印日志都能帮助理解内核行为，这为我后续学习 Linux 内核打下了坚实基础。