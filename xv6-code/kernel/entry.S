# kernel/entry.S - 内核入口点

.globl entry
entry:
  # 设置栈指针（为C函数调用做准备）
  movl    $0x8000, %esp       # 栈顶地址=0x8000
  
  # 清除标志寄存器
  pushl   $0                  # 压入0值
  popf                        # 弹出到eflags
  
  # 跳转到C语言的main函数
  call    main                # 进入内核主函数
  
  # 不应该到达这里（main函数不返回）
  jmp .                       # 无限循环
