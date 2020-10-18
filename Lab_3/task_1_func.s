.global _task_1_func
_task_1_func:
    movl 4(%esp), %eax
    movl %eax, %ecx
    and $3, %eax
    subl %ecx, %eax
ret