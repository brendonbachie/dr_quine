global ft_strcmp
section .text
ft_strcmp:
    .loop:
        mov r8b, byte [rdi]
        mov r9b, byte [rsi]
        cmp r8b, r9b
        jne .done
        cmp r8b, 0
        je .done
        inc rdi
        inc rsi
        jmp .loop
    .done:
    movzx rax, r8b
    movzx rcx, r9b
    sub rax, rcx
    ret
