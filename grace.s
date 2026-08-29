;Grace
global main
extern fprintf
extern fopen
extern fclose
%macro A 0
    lea rdi, [rel filename]
    lea rsi, [rel mode]
    call fopen wrt ..plt
    mov r12, rax
%endmacro
%macro B 0
    mov rdi, r12
    lea rsi, [rel msg]
    mov rdx, 10
    mov rcx, 10
    mov r8, 10
    mov r9, 10
    mov rax, 34
    push rax
    lea rax, [rel msg]
    push rax
    mov rax, 34
    push rax
    mov rax, 10
    push rax
    mov rax, 34
    push rax
    mov rax, 34
    push rax
    mov rax, 10
    push rax
    mov rax, 34
    push rax
    mov rax, 34
    push rax
    %rep 53
        push 10
    %endrep
    xor eax, eax
    call fprintf wrt ..plt
%endmacro
%macro C 0
    mov rdi, r12
    call fclose wrt ..plt
%endmacro
section .text
main:
    push rbp
    mov rbp, rsp
    A
    B
    C
    xor eax, eax
    leave
    ret
section .rodata
filename: db "Grace_kid.s", 0
mode: db "w", 0
msg: db ";Grace%cglobal main%cextern fprintf%cextern fopen%cextern fclose%c%%macro A 0%c    lea rdi, [rel filename]%c    lea rsi, [rel mode]%c    call fopen wrt ..plt%c    mov r12, rax%c%%endmacro%c%%macro B 0%c    mov rdi, r12%c    lea rsi, [rel msg]%c    mov rdx, 10%c    mov rcx, 10%c    mov r8, 10%c    mov r9, 10%c    mov rax, 34%c    push rax%c    lea rax, [rel msg]%c    push rax%c    mov rax, 34%c    push rax%c    mov rax, 10%c    push rax%c    mov rax, 34%c    push rax%c    mov rax, 34%c    push rax%c    mov rax, 10%c    push rax%c    mov rax, 34%c    push rax%c    mov rax, 34%c    push rax%c    %%rep 53%c        push 10%c    %%endrep%c    xor eax, eax%c    call fprintf wrt ..plt%c%%endmacro%c%%macro C 0%c    mov rdi, r12%c    call fclose wrt ..plt%c%%endmacro%csection .text%cmain:%c    push rbp%c    mov rbp, rsp%c    A%c    B%c    C%c    xor eax, eax%c    leave%c    ret%csection .rodata%cfilename: db %cGrace_kid.s%c, 0%cmode: db %cw%c, 0%cmsg: db %c%s%c, 0", 0