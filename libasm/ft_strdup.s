global ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy

section .text

ft_strdup:
    push r13
    mov r13, rdi
    call ft_strlen
    mov r8, rax
    inc r8
    mov rdi, r8
    call malloc wrt ..plt
    test rax, rax
    jz .malloc_failed
    mov rdi, rax
    mov rsi, r13
    call ft_strcpy
    pop r13
    ret
.malloc_failed:
    xor rax, rax
    pop r13
    ret
