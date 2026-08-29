;quine in ASM
global main
extern printf
aux:
    xor eax, eax
    ret
section .text
main:
    ;routine
    push rbp
    mov rbp, rsp
    sub rsp, 8
    lea rdi, [rel msg]
    mov rsi, 10
    mov rdx, 10
    mov rcx, 10
    mov r8, 10
    mov r9, 10
    mov rax, 10
    push rax
    mov rax, 34
    push rax
    lea rax, [rel msg]
    push rax
    mov rax, 34
    push rax
    %rep 30
        push 10
    %endrep
    call aux
    call printf wrt ..plt
    call aux
    leave
    ret
section .rodata
msg: db ";quine in ASM%cglobal main%cextern printf%caux:%c    xor eax, eax%c    ret%csection .text%cmain:%c    ;routine%c    push rbp%c    mov rbp, rsp%c    sub rsp, 8%c    lea rdi, [rel msg]%c    mov rsi, 10%c    mov rdx, 10%c    mov rcx, 10%c    mov r8, 10%c    mov r9, 10%c    mov rax, 10%c    push rax%c    mov rax, 34%c    push rax%c    lea rax, [rel msg]%c    push rax%c    mov rax, 34%c    push rax%c    %%rep 30%c        push 10%c    %%endrep%c    call aux%c    call printf wrt ..plt%c    call aux%c    leave%c    ret%csection .rodata%cmsg: db %c%s%c%c"
