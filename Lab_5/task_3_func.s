.globl _task_3_func
_task_3_func:
    fldl  4(%esp)
	fldl  12(%esp)
	fldz					
	fadd  %st(1), %st(0)						
	fmul  %st(1), %st(0)
	fmulp %st(0), %st(2)		
	faddp %st(0), %st(1)		
	fcos
	ret
