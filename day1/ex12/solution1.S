.intel_syntax noprefix

.global main
main:
    push rbp
    mov rbp, rsp

	mov	rdi, [rsi + 8]			# num from argv[1]
	mov	rsi, 0				    # NULL
	mov	rdx, 10				    # base 10
	call	strtol

    lea rdi, format[rip]
    mov rsi, rax                # num from strtol
    call printf

    leave
    ret

format:
    .string "%d\n"