BITS 64

SECTION .text
GLOBAL rindex:function  ; char * rindex(char * str, int c)

rindex:
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
    je .assign             ; return void *
    inc rdi             ; ++str
    jmp .loop

.assign:
    mov rax, rdi
    inc rdi
    jmp .loop

.end:
    leave           ; return
    ret             ;