BITS 64

SECTION .text
GLOBAL strcasecmp:function  ; int strcasecmp(void *, void *)

strcasecmp:
    push rbp
    mov rbp, rsp

    mov rax, 0    ; ret = void *
    cmp rdi, 0      ; if (if void * == NULL)
    je .les
    cmp rsi, 0      ; if (if void * == NULL)
    je .sup
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
    cmp r8b, r9b          ; if (size_t == 0)
    jg .sup             ; return void *
    jl .les
    cmp r8b, 0
    je .end
    cmp r9b, 0
    je .end
    inc rdi             ; ++void *
    inc rsi             ; ++void *
    jmp .cmp1

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