BITS 64

SECTION .text
GLOBAL strcmp:function  ; int strcmp(void *, void *)

strcmp:
    push rbp
    mov rbp, rsp

    mov rax, 0    ; ret = void *
    cmp rdi, 0      ; if (if void * == NULL)
    je .les
    cmp rsi, 0      ; if (if void * == NULL)
    je .sup

.loop:
    mov r8b, [rdi]
    mov r9b, [rsi]
    cmp r8b, r9b          ; if (size_t == 0)
    jg .sup             ; return void *
    jl .les
    cmp byte [rdi], 0
    je .end
    cmp byte [rsi], 0
    je .end
    inc rdi             ; ++void *
    inc rsi             ; ++void *
    jmp .loop

.sup:
    mov rax, 1
    cmp rdi, 0
    je .eq
    jmp .end

.les:
    mov rax, -1
    cmp rsi, 0
    je .eq
    jmp .end

.eq:
    mov rax, 0
    jmp .end

.end:
    leave           ; return
    ret             ;