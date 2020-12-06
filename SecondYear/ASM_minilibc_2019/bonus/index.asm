BITS 64

SECTION .text
GLOBAL index:function  ; char * index(char * str, int c)

index:
    push rbp
    mov rbp, rsp

    mov rax, 0    ; ret = void *
    cmp rdi, 0      ; if (if str == NULL)
    je .end
    cmp esi, 0      ; if (if c < 0)
    jl .end

.loop:
    cmp byte [rdi], 0
    je .end
    cmp byte [rdi], sil          ; if (size_t == 0)
    je .found             ; return void *
    inc rdi             ; ++str
    jmp .loop

.found:
    mov rax, rdi

.end:
    leave           ; return
    ret             ;