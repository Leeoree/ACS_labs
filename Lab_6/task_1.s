.data

x: .double 11.0
printf_format: .string "y(x) = %.15lf\n"

.globl _main
_main:
movl x, %eax
subl $13, %eax  
cmpl $0, %eax  #если меньше
jg _func
movl x, %eax
addl $1, %eax 
jmp _end

#3,x,1
_func: 

movl $3, %edx
fldl 4(%edx)

movl x, %eax
neg %eax
fldl 8(%eax)

fld1

fdivr  #-x/3, 1
faddp 
fstpl %eax


_end:

pushl %eax
pushl $printf_format
call _printf
addl $8, %esp
xor %eax, %eax

ret