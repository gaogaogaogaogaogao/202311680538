# xv6 启动流程实践报告

**学号：202311680538**  
**姓名：高欣雨**  
**班级：23计1**

## 一、已完成的修改

### 1. 代码注释
- boot/bootasm.S：添加详细中文注释，解释实模式到保护模式转换
- boot/bootmain.c：添加中文注释，解释ELF文件加载过程
- kernel/entry.S：添加中文注释，解释内核入口设置

### 2. 启动可视化
- boot/bootmain.c：添加3个打印语句：
  - `[BOOT] enter bootmain`
  - `[BOOT] elf header loaded`
  - `[BOOT] kernel loaded`
- kernel/main.c：添加1个打印语句：
  - `[KERNEL] main() started`

## 二、xv6启动流程

1. **BIOS阶段**：加载MBR到0x7C00
2. **bootasm.S**：实模式初始化→启用A20→进入保护模式
3. **bootmain.c**：读取ELF头部→验证魔数→加载内核
4. **entry.S**：设置栈指针→跳转到main()
5. **main.c**：初始化内核→启动第一个进程

## 三、提交记录
1. 第一次提交：创建README.md
2. 第二次提交：添加bootasm.S
3. 第三次提交：添加bootmain.c
4. 第四次提交：添加entry.S和main.c

## 四、学习总结
理解了x86启动流程、ELF文件格式、操作系统初始化过程。
