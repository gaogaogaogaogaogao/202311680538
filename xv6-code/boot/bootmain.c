// boot/bootmain.c - xv6启动主函数

// 打印字符串到串口
void print_str(char* str) {
  while (*str) {
    // 向COM1串口输出字符
    outb(0x3F8, *str++);
  }
}

// 主引导函数
void bootmain(void) {
  // 阶段1：进入bootmain
  print_str("[BOOT] enter bootmain\r\n");
  
  // 读取ELF头部
  struct elfhdr *elf = (struct elfhdr*)0x10000;
  readseg((uchar*)elf, 4096, 0);
  
  // 检查ELF魔数
  if(elf->magic != 0x464C457F) {  // 0x7F + 'E' + 'L' + 'F'
    return;  // 不是有效ELF文件
  }
  
  // 阶段2：ELF头部加载完成
  print_str("[BOOT] elf header loaded\r\n");
  
  // 加载程序段到内存
  struct proghdr *ph = (struct proghdr*)((uchar*)elf + elf->phoff);
  struct proghdr *eph = ph + elf->phnum;
  for(; ph < eph; ph++) {
    readseg((uchar*)ph->p_pa, ph->p_memsz, ph->p_offset);
  }
  
  // 阶段3：内核加载完成
  print_str("[BOOT] kernel loaded\r\n");
  
  // 跳转到内核入口点
  void (*entry)(void) = (void(*)(void))(elf->entry);
  entry();  // 进入内核
}
