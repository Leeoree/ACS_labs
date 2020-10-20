.globl _task_1_func
divider: .int 4
_task_1_func:
    movl 4(%esp), %eax
    movl $0, %edx    
    movl %eax, %ecx
    idivl divider
    movl %edx, %eax
    subl %ecx, %eax
    ret
