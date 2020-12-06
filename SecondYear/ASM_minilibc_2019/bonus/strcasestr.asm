BITS 64

SECTION .text
GLOBAL strcasestr:function  ; char * strcasestr(char * str1, char *str2)

strcasestr:
    push rbp
    mov rbp, rsp

    mov rax, 0    ; ret = void *
    cmp rdi, 0      ; if (if str1 == NULL)
    je .end
    cmp rsi, 0      ; if (if str2 == NULL)
    je .end
    mov r11, rsi
    jmp .cmp1

.add1:
    add r8b, 32
    jmp .cmp2

.add2:
    add r9b, 32
    jmp .loop

.cmp1:
	mov r8b, [rdi]
	cmp r8b, 65
	jl .cmp2
	cmp r8b, 90
	jl .add1

.cmp2:
	mov r9b, [rsi]
	cmp r9b, 65
	jl .loop
	cmp r9b, 90
	jl .add2

.loop:
    cmp byte [rdi], 0
    je .end
    cmp byte [rsi], 0
    je .found
    cmp r8b, r9b          ; if (size_t == 0)
    je .assign             ; return void *
    jne .notRight

.notRight:
    mov rsi, r11
    inc rdi
    jmp .cmp1

.assignBegin:
    mov r10, rdi
    inc rdi
    inc rsi
    jmp .cmp1

.assign:
    cmp r11, rsi
    je .assignBegin
    inc rdi
    inc rsi
    jmp .cmp1

.found:
    mov rax, r10

.end:
    leave           ; return
    ret             ;