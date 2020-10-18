.globl _task_4_func
_task_4_func:
	movl 12(%esp), %eax
	movl 8(%esp), %ecx
	movl 4(%esp), %edx
	imul %edx, %ecx
	movl %eax, %edx
	addl %eax, %ecx
	subl %edx, %ecx
	ret