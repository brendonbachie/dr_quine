global ft_write
extern __errno_location
section .text
ft_write:
    push r13
    mov rax, 1
    syscall
    mov r13, rax
    cmp r13, 0
    jl .error
    mov rax, r13
    pop r13
    ret
.error:
    neg r13
    call __errno_location wrt ..plt
    mov dword [rax], r13d
    mov rax, -1
    pop r13
    ret