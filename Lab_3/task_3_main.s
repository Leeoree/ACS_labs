.globl _main
_main:
	push $1
	push $7
	call _task_3_func
	add $8, %esp
	xor %eax, %eax
	ret