.intel_syntax noprefix

.global main
main:
    push rbp
    mov rbp, rsp

    lea rdi, format[rip]
    mov rsi, [rsi + 8]
    call printf

    leave
    ret

format:
    .string "%s\n"