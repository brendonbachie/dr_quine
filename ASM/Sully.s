global main
extern fopen
extern fprintf
extern fclose
extern sprintf
extern system
section .text
main:
    push rbp
    mov rbp, rsp
    mov r13d, [rel num]
    dec r13d
    lea rdi, [rel filename]
    lea rsi, [rel name]
    movsx rdx, r13d
    xor eax, eax
    call sprintf wrt ..plt
    lea rdi, [rel filename]
    lea rsi, [rel mode]
    call fopen wrt ..plt
    mov r12, rax
    mov rdi, r12
    lea rsi, [rel quine]
    mov rdx, 10
    mov rcx, 10
    mov r8, 10
    mov r9, 10
    sub rsp, 8
    push 10
    push 10
    push 10
    push 10
    push 10
    push 34
    lea rax, [rel quine]
    push rax
    push 34
    push 10
    push 34
    push 34
    push 10
    push 34
    push 34
    push 10
    push 34
    push 34
    push 10
    push 34
    push 34
    push 10
    push 10
    movsx rax, r13d
    push rax
    %rep 80
        push 10
    %endrep
    xor eax, eax
    call fprintf wrt ..plt
    mov rdi, r12
    call fclose wrt ..plt
    lea rdi, [rel command]
    lea rsi, [rel cmd]
    movsx rdx, r13d
    movsx rcx, r13d
    movsx r8, r13d
    movsx r9, r13d
    xor eax, eax
    call sprintf wrt ..plt
    lea rdi, [rel command]
    call system wrt ..plt
    cmp r13d, 0
    jl .done
    lea rdi, [rel runbuf]
    lea rsi, [rel runfmt]
    movsx rdx, r13d
    xor eax, eax
    call sprintf wrt ..plt
    lea rdi, [rel runbuf]
    call system wrt ..plt
.done:
    xor eax, eax
    leave
    ret
section .data
num: dd 5
section .rodata
name: db "Sully_%d.s", 0
mode: db "w", 0
cmd: db "nasm -f elf64 Sully_%d.s -o Sully_%d.o && gcc Sully_%d.o -o Sully_%d", 0
runfmt: db "./Sully_%d", 0
quine: db "global main%cextern fopen%cextern fprintf%cextern fclose%cextern sprintf%cextern system%csection .text%cmain:%c    push rbp%c    mov rbp, rsp%c    mov r13d, [rel num]%c    dec r13d%c    lea rdi, [rel filename]%c    lea rsi, [rel name]%c    movsx rdx, r13d%c    xor eax, eax%c    call sprintf wrt ..plt%c    lea rdi, [rel filename]%c    lea rsi, [rel mode]%c    call fopen wrt ..plt%c    mov r12, rax%c    mov rdi, r12%c    lea rsi, [rel quine]%c    mov rdx, 10%c    mov rcx, 10%c    mov r8, 10%c    mov r9, 10%c    sub rsp, 8%c    push 10%c    push 10%c    push 10%c    push 10%c    push 10%c    push 34%c    lea rax, [rel quine]%c    push rax%c    push 34%c    push 10%c    push 34%c    push 34%c    push 10%c    push 34%c    push 34%c    push 10%c    push 34%c    push 34%c    push 10%c    push 34%c    push 34%c    push 10%c    push 10%c    movsx rax, r13d%c    push rax%c    %%rep 80%c        push 10%c    %%endrep%c    xor eax, eax%c    call fprintf wrt ..plt%c    mov rdi, r12%c    call fclose wrt ..plt%c    lea rdi, [rel command]%c    lea rsi, [rel cmd]%c    movsx rdx, r13d%c    movsx rcx, r13d%c    movsx r8, r13d%c    movsx r9, r13d%c    xor eax, eax%c    call sprintf wrt ..plt%c    lea rdi, [rel command]%c    call system wrt ..plt%c    cmp r13d, 0%c    jl .done%c    lea rdi, [rel runbuf]%c    lea rsi, [rel runfmt]%c    movsx rdx, r13d%c    xor eax, eax%c    call sprintf wrt ..plt%c    lea rdi, [rel runbuf]%c    call system wrt ..plt%c.done:%c    xor eax, eax%c    leave%c    ret%csection .data%cnum: dd %d%csection .rodata%cname: db %cSully_%%d.s%c, 0%cmode: db %cw%c, 0%ccmd: db %cnasm -f elf64 Sully_%%d.s -o Sully_%%d.o && gcc Sully_%%d.o -o Sully_%%d%c, 0%crunfmt: db %c./Sully_%%d%c, 0%cquine: db %c%s%c, 0%csection .bss%cfilename: resb 128%ccommand: resb 256%crunbuf: resb 128%c", 0
section .bss
filename: resb 128
command: resb 256
runbuf: resb 128
