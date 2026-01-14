#include "types.h"
#include "elf.h"
#include "x86.h"
#include "memlayout.h"

// 简单的串口输出函数
void print_str(char* str) {
  while (*str) {
    outb(0x3F8, *str++);  // 向COM1串口发送字符
  }
}

// 读取磁盘扇区的函数
void readseg(uchar*, uint, uint);

// 主引导函数
void bootmain(void) {
  // 打印进入bootmain的信息
  print_str("[BOOT] enter bootmain\r\n");
  
  struct elfhdr *elf;
  struct proghdr *ph, *eph;
  void (*entry)(void);
  uchar* pa;
  
  // ELF头部临时存放位置
  elf = (struct elfhdr*)0x10000;
  
  // 读取ELF头部
  readseg((uchar*)elf, 4096, 0);
  
  // 检查ELF魔数
  if(elf->magic != ELF_MAGIC) {
    return;  // 如果不是有效的ELF文件，则返回
  }
  
  // 打印ELF头部加载完成
  print_str("[BOOT] elf header loaded\r\n");
  
  // 加载每个程序段
  ph = (struct proghdr*)((uchar*)elf + elf->phoff);
  eph = ph + elf->phnum;
  for(; ph < eph; ph++) {
    pa = (uchar*)ph->p_pa;
    readseg(pa, ph->p_memsz, ph->p_offset);
  }
  
  // 打印内核加载完成
  print_str("[BOOT] kernel loaded\r\n");
  
  // 跳转到内核入口点
  entry = (void(*)(void))(elf->entry);
  entry();
}
