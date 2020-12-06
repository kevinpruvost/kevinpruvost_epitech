BITS 64

SECTION .text
GLOBAL memmove:function  ; void *memmove(void *, void *, size_t)

memmove:
    push rbp
    mov rbp, rsp

    mov rax, rdi    ; ret = void *
    cmp rdi, 0      ; if (if void * == NULL)
    je .end
    cmp rsi, 0      ; if (if void * == NULL)
    je .end
    mov r8, rdi
    sub r8, rsi
    cmp r8, 0
    jge .loop

.preloop0:
    mov rcx, 0

.loop0:
    cmp rdx, rcx          ; if (size_t == 0)
    je .end             ; return void *
    mov r8b, [rsi+rcx]
    mov [rdi+rcx], r8b      ; void *[0] = int
    inc rcx
    jmp .loop0

.loop:
    dec rdx
    cmp rdx, 0          ; if (size_t == 0)
    jl .end             ; return void *
    mov r8b, [rsi+rdx]
    mov [rdi+rdx], r8b  ; void *[0] = int
    jmp .loop

.end:
    leave           ; return
    ret             ;