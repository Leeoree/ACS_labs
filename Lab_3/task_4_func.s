.globl _task_4_func
_task_4_func:
	movl 12(%esp), %eax
	movl 8(%esp), %edx
	movl 4(%esp), %ecx
	imul %edx, %ecx
	movl %eax, %edx
	addl %ecx, %eax
	subl %ecx, %edx
	ret
