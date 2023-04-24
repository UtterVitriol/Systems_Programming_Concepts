.intel_syntax noprefix

.global fibonacci
fibonacci:
    push rbp
    mov rbp, rsp

    push r15
    push r14

    cmp rdi, 1
    mov rax, 1
    jbe .END

    mov r15, rdi
    mov r14, rdi
    sub r15, 1
    mov rdi, r15
    call fibonacci
    mov r15, rax

    sub r14, 2
    mov rdi, r14
    call fibonacci

    add rax, r15

.END:

    pop r14
    pop r15
    pop rbp
    ret


.global get_rip
get_rip:
    push rbp
    mov rbp, rsp

    lea rdi, hexprf[rip]
    mov rsi, [rbp + 8]
    call printf
    pop rbp
    ret

.global dump_regs
dump_regs:
    # never finished this
    push rbp
    mov rbp, rsp
    sub rsp, 128

    mov [rsp], rax
    mov [rsp + 8], rbx
    mov [rsp + 16], rcx
    mov [rsp + 24], rdx
    mov [rsp + 32], rsi
    mov [rsp + 40], rdi
    mov [rsp + 48], rsp
    mov [rsp + 50], rbp
    mov [rsp + 64], r8
    mov [rsp + 72], r9
    mov [rsp + 80], r10
    mov [rsp + 88], r11
    mov [rsp + 96], r12
    mov [rsp + 104], r13
    mov [rsp + 112], r14
    mov [rsp + 120], r15

    mov rdi, .RAX[rip]
    mov rsi, [rsp]      #, rax
    call printf

    # mov rdi, .RBX[rip]
    # mov rsi, [rsp + 8]  #, rbx
    # call printf

    # mov rdi, .RCX[rip]
    # mov rsi, [rsp + 16] #, rcx
    # call printf

    # mov rdi, .RDX[rip]
    # mov rsi, [rsp + 24] #, rdx
    # call printf

    # mov rdi, .RSI[rip]
    # mov rsi, [rsp + 32] #, rsi
    # call printf

    # mov rdi, .RDI[rip]
    # mov rsi, [rsp + 40] #, rdi
    # call printf

    # mov rdi, .RSP[rip]
    # mov rsi, [rsp + 48] #, rsp
    # call printf

    # mov rdi, .RBP[rip]
    # mov rsi, [rsp + 56] #, rbp
    # call printf

    # mov rdi, .R8[rip]
    # mov rsi, [rsp + 64] #, r8
    # call printf

    # mov rdi, .R9[rip]
    # mov rsi, [rsp + 72] #, r9
    # call printf

    # mov rdi, .R10[rip]
    # mov rsi, [rsp + 80] #, r10
    # call printf

    # mov rdi, .R11[rip]
    # mov rsi, [rsp + 88] #, r11
    # call printf

    # mov rdi, .R12[rip]
    # mov rsi, [rsp + 96] #, r12
    # call printf

    # mov rdi, .R13[rip]
    # mov rsi, [rsp + 104]#, r13
    # call printf

    # mov rdi, .R14[rip]
    # mov rsi, [rsp + 112]#, r14
    # call printf

    # mov rdi, .R15[rip]
    # mov rsi, [rsp + 120]#, r15
    # call printf
    

    leave
    ret


hexprf:
    .string "RIP: 0%lx\n"


thing:
    .string "Value: %dx\n"

.RAX:
    .string "rax: %lu"
.RBX:
    .string "rbx: %lu"
.RCX:
    .string "rcx: %lu"
.RDX:
    .string "rdx: %lu"
.RSI:
    .string "rsi: %lu"
.RDI:
    .string "rdi: %lu"
.RSP:
    .string "rsp: %lu"
.RBP:
    .string "rbp: %lu"
.R8:
    .string "r8: %lu"    
.R9:
    .string "r9: %lu"
.R10:
    .string "r10: %lu"
.R11:
    .string "r11: %lu"
.R12:
    .string "r12: %lu"
.R13:
    .string "r13: %lu"
.R14:
    .string "r14: %lu"
.R15:
    .string "r15: %lu"