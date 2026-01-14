# xv6 启动流程实践报告

## 学号：202311680538
## 姓名：[你的名字]

## 一、启动流程分析

### 1. BIOS阶段
- CPU从0xFFFF0开始执行BIOS固件代码
- BIOS进行硬件自检（POST）
- 加载主引导记录（MBR）到内存0x7C00处

### 2. Bootloader阶段
- **bootasm.S**（实模式）：
  - 关中断（cli）
  - 清空段寄存器
  - 启用A20地址线
  - 加载全局描述符表（GDT）
  - 切换到保护模式
  - 设置栈指针，跳转到bootmain

- **bootmain.c**（保护模式）：
  - 读取ELF文件头部
  - 验证魔数（0x7F + 'ELF'）
  - 加载程序段到内存0x100000处
  - 跳转到内核入口点

### 3. 内核初始化阶段
- **entry.S**：
  - 设置栈指针（esp = 0x8000）
  - 清除eflags寄存器
  - 调用main函数

- **main.c**：
  - 初始化控制台
  - 初始化内存管理
  - 初始化页表
  - 初始化中断
  - 启动第一个进程

## 二、关键代码修改

### 1. 添加启动信息输出
在 `boot/bootmain.c` 中添加：
```c
void print_str(char* str) {
    while (*str) {
        outb(0x3F8, *str++);
    }
}

void bootmain(void) {
    print_str("[BOOT] enter bootmain\r\n");
    // ... 原有代码
    print_str("[BOOT] elf header loaded\r\n");
    print_str("[BOOT] kernel loaded\r\n");
}
