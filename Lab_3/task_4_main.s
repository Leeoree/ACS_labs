.data
format_out: .string "a = %d, b = %d, c = %d\nx = %d\ny = %d"
.globl _main
_main:
	pushl $10
	pushl $8
	pushl $2
	call _task_4_func
	addl $4*3, %esp
	pushl %edx
	pushl %eax
	pushl $2
	pushl $8
	pushl $10
	pushl $format_out
	call _printf
	addl $4*6, %esp
	xorl %eax, %eax
	xorl %ecx, %ecx
	xorl %edx, %edx
	ret
