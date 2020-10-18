.data
format_out: .string "a = %d, b = %d, c = %d\nx = %d\ny = %d"
.globl _main
_main:
	pushl $10
	pushl $8
	pushl $2
	call _task_4_func
	add $4*3, %esp
	pushl %edx
	pushl %eax
	pushl $2
	pushl $8
	pushl $10
	pushl $format_out
	call _printf
	add $4*5, %esp
	xor %eax, %eax
	xor %ecx, %ecx
	xor %edx, %edx
	ret