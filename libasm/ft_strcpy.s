global ft_strcpy
section .text
ft_strcpy:
    mov rax, rdi
    .loop:
        mov r8b, byte [rsi]
        mov byte [rdi], r8b
        cmp r8b, 0
        je .done
        inc rdi
        inc rsi
        jmp .loop
    .done:
    ret