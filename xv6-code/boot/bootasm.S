# boot/bootasm.S - xv6启动汇编代码

# 启动入口点，BIOS加载到0x7C00处
.globl start
start:
  .code16                     # 16位实模式
  cli                         # 关中断
  
  # 清零段寄存器
  xorw    %ax,%ax             # AX=0
  movw    %ax,%ds             # 数据段=0
  movw    %ax,%es             # 附加段=0
  movw    %ax,%ss             # 堆栈段=0
  
  # 启用A20地址线（突破1MB内存限制）
seta20:
  inb     $0x64,%al           # 读键盘控制器状态
  testb   $0x2,%al            # 检查输入缓冲区是否空
  jnz     seta20              # 不空则等待
  movb    $0xd1,%al           # 发送写命令
  outb    %al,$0x64
  
  # 进入保护模式
  lgdt    gdtdesc             # 加载GDT
  movl    %cr0, %eax          # 读CR0
  orl     $0x1, %eax          # 设置保护模式位
  movl    %eax, %cr0          # 写回CR0
  
  # 跳转到32位代码段
  ljmp    $0x8, $start32

.code32
start32:
  # 设置段寄存器
  movw    $0x10, %ax
  movw    %ax, %ds
  movw    %ax, %es
  movw    %ax, %ss
  
  # 设置栈指针并调用bootmain
  movl    $0x7c00, %esp
  call    bootmain

# 无限循环（防止跑飞）
spin:
  jmp spin
