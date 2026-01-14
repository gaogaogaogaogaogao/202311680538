# 内核入口点文件

.globl entry
entry:
  # 设置栈指针，为C代码执行做准备
  movl    $0x8000, %esp       # 栈顶地址为0x8000
  
  # 清除eflags寄存器
  pushl   $0                  # 压入0
  popf                        # 弹出到eflags寄存器
  
  # 调用main函数，进入内核主函数
  call    main                # 跳转到C语言的主函数
  
  # 无限循环（正常情况下main函数不会返回）
  jmp .                       # 跳转到当前位置，形成死循环
