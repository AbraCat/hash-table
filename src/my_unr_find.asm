global my_unr_find
extern mystrcmp

section .text

; -------------------------------------
; Args:
; rdi - node
; rsi - s
;
; Returns:
; eax - result
;
; Destroys:
; rcx
; -------------------------------------
my_unr_find:
    push rbx
    mov rbx, rdi
    jmp my_unr_find_cond

    my_unr_find_loop:
    xor rcx, rcx

    my_unr_find_inner_loop:
    mov rdi, rcx
    shl rdi, 5
    add rdi, QWORD [rbx]

    ; mystrcmp inlined
    vmovdqa ymm0, [rsi]
    vpxor   ymm0, ymm0, [rdi]
    xor     eax, eax
    vptest  ymm0, ymm0
    setne   al
    vzeroupper

    test rax, rax
    jne my_unr_find_continue

    mov eax, 1
    pop rbx
    ret

    my_unr_find_continue:
    inc rcx
    cmp rcx, 4
    jne my_unr_find_inner_loop

    mov rbx, QWORD [rbx + 8]
    my_unr_find_cond:
    test rbx, rbx
    jne my_unr_find_loop

    xor eax, eax
    pop rbx
    ret