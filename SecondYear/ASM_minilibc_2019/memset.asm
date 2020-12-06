BITS 64

SECTION .text
GLOBAL memset:function  ; void *memset(void *, int, size_t)

memset:
    push rbp
    mov rbp, rsp

    mov rax, rdi    ; ret = void *
    cmp rdi, 0      ; if (if void * == NULL)
    je .end

.loop:
    cmp rdx, 0      ; if (size_t == 0)
    je .end         ; return void *
    mov [rdi], sil  ; void *[0] = int
    inc rdi         ; ++void *
    dec rdx
    jmp .loop

.end: 
    leave           ; return
    ret             ;