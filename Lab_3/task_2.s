.data
printf_format:
    .string "%d\n"
.globl _main
_main:
    movl $13, %eax
    movl %eax, %edx
    and $3, %eax
    subl %edx, %eax
    pushl %eax
    pushl $printf_format
    call _printf
    addl $8, %esp
    xor %eax, %eax
    xor %edx, %edx
    ret