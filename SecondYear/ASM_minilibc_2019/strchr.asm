BITS 64

GLOBAL strchr:function
SECTION .text

;; void *strchr(const char * str, int c)

strchr:
    push rbp        ; PROLOGUE
    mov rbp, rsp    ; (== enter)

    mov rax, 0
    cmp rdi, 0      ; if (str == NULL)
    je .end    ; return NULL;
    cmp sil, 0      ; if (c == 0)
    je .end    ; return NULL;

.loop:                    ; while
    cmp byte [rdi], 0     ; str[i] == 0
    je .end
    cmp byte [rdi], sil   ; str[i] == param2
    je .found             ; return res
    inc rdi               ; ++i
    jmp .loop             ; loop

.found:
    mov rax, rdi
    jmp .end

.end:
    leave           ; return
    ret             ;