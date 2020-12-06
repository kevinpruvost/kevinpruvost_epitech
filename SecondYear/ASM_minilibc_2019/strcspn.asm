BITS 64

SECTION .text
GLOBAL strcspn:function  ; size_t strpbrk(char * str1, char *str2)

strcspn:
    push rbp
    mov rbp, rsp

    mov rax, 0    ; ret = 0
    cmp rdi, 0      ; if (if str1 == NULL)
    je .end
    cmp rsi, 0      ; if (if str2 == NULL)
    je .end
    mov r11, rsi

.loop:
    cmp byte [rdi], 0
    je .end
    cmp byte [rsi], 0
    je .reset
    mov r8b, [rdi]
    mov r9b, [rsi]
    cmp r8b, r9b          ; if (size_t == 0)
    je .end             ; return void *
    inc rsi
    jmp .loop

.reset:
    mov rsi, r11
    inc rdi
    inc rax
    jmp .loop

.end:
    leave           ; return
    ret             ;