BITS 64

SECTION .text
GLOBAL memcpy:function  ; void *memcpy(void *, void *, size_t)

memcpy:
    push rbp
    mov rbp, rsp

    mov rax, rdi    ; ret = void *
    cmp rdi, 0      ; if (if void * == NULL)
    je .end
    cmp rsi, 0      ; if (if void * == NULL)
    je .end

.loop:
    cmp rdx, 0          ; if (size_t == 0)
    je .end             ; return void *
    mov r8b, [rsi]
    mov [rdi], r8b      ; void *[0] = int
    inc rdi             ; ++void *
    inc rsi             ; ++void *
    dec rdx
    jmp .loop

.end:
    leave           ; return
    ret             ;