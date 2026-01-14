#include "asm.h"
#include "memlayout.h"
#include "mmu.h"

# 启动入口点
.globl start
start:
  .code16                     # 16位实模式代码
  cli                         # 关闭中断，防止在设置过程中被中断
  
  # 清空段寄存器
  xorw    %ax,%ax             # 将AX寄存器清零
  movw    %ax,%ds             # 数据段寄存器清零
  movw    %ax,%es             # 附加段寄存器清零
  movw    %ax,%ss             # 堆栈段寄存器清零
  
  # 启用A20地址线，突破1MB内存限制
seta20.1:
  inb     $0x64,%al           # 读取8042状态端口
  testb   $0x2,%al            # 检查输入缓冲区是否为空
  jnz     seta20.1            # 如果不为空，则等待
  movb    $0xd1,%al           # 发送写命令到8042
  outb    %al,$0x64
  
seta20.2:
  inb     $0x64,%al
  testb   $0x2,%al
  jnz     seta20.2
  movb    $0xdf,%al           # 写入A20启用信号
  outb    %al,$0x60
  
  # 加载全局描述符表（GDT），切换到保护模式
  lgdt    gdtdesc             # 加载GDT
  movl    %cr0, %eax          # 读取CR0寄存器
  orl     $CR0_PE, %eax       # 设置保护模式使能位
  movl    %eax, %cr0          # 写回CR0，进入保护模式
  
  # 跳转到保护模式代码
  ljmp    $(SEG_KCODE<<3), $start32

.code32
start32:
  # 设置保护模式下的数据段寄存器
  movw    $(SEG_KDATA<<3), %ax
  movw    %ax, %ds
  movw    %ax, %es
  movw    %ax, %ss
  movw    $0, %ax
  movw    %ax, %fs
  movw    %ax, %gs
  
  # 设置栈指针
  movl    $start, %esp
  
  # 调用bootmain函数
  call    bootmain

# 无限循环，防止跑飞
spin:
  jmp spin
