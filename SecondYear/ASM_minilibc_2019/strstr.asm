BITS 64

SECTION .text
GLOBAL strstr:function  ; char * strstr(char * str1, char *str2)

strstr:
    push rbp
    mov rbp, rsp

    mov rax, 0    ; ret = void *
    cmp rdi, 0      ; if (if str1 == NULL)
    je .end
    cmp rsi, 0      ; if (if str2 == NULL)
    je .end
    mov r11, rsi

.loop:
    cmp byte [rdi], 0
    je .end
    cmp byte [rsi], 0
    je .found
    mov r8b, [rdi]
    mov r9b, [rsi]
    cmp r8b, r9b          ; if (size_t == 0)
    je .assign             ; return void *
    jne .notRight

.notRight:
    mov rsi, r11
    inc rdi
    jmp .loop

.assignBegin:
    mov r10, rdi
    inc rdi
    inc rsi
    jmp .loop

.assign:
    cmp r11, rsi
    je .assignBegin
    inc rdi
    inc rsi
    jmp .loop

.found:
    mov rax, r10

.end:
    leave           ; return
    ret             ;