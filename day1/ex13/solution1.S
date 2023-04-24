.intel_syntax noprefix

# https://filippo.io/linux-syscall-table/
# https://man7.org/linux/man-pages/man2/syscall.2.html


.global exploit
exploit:
    push rbp
    mov rbp, rsp
    push r15
    sub rsp, 1660 # buffer size (bigger than /etc/passwd)

    # Open file
    mov rax, 2
    lea rdi, .FILE[rip]
    mov rsi, 0
    mov rdx, 0
    syscall

    mov r15, rax # this is the FD

    # read the file
    mov rax, 0
    mov rdi, r15
    mov rsi, rsp
    mov rdx, 1651 # File size of /etc/passwd
    syscall


    # write file
    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 1651
    syscall


    # close the file
    mov rax, 3
    mov rdi, r15
    syscall

    pop r15
    leave
    ret



.FILE:
    .string "/etc/passwd"