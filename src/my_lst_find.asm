global my_lst_find
extern mystrcmp

section .text

; -------------------------------------
; Args:
; rdi - node
; rsi - s
;
; Returns
; eax - result
; -------------------------------------
my_lst_find:
    push rbx
    mov rbx, rdi
    jmp my_lst_find_cond

    my_lst_find_loop:
    mov rdi, QWORD [rbx]

    ; mystrcmp inlined
    vmovdqa ymm0, [rsi]
    vpxor   ymm0, ymm0, [rdi]
    xor     eax, eax
    vptest  ymm0, ymm0
    setne   al
    vzeroupper

    test rax, rax
    je my_lst_find_continue

    mov eax, 1 ; mov rax, rbx
    pop rbx
    ret 

    my_lst_find_continue:
    mov rbx, QWORD [rbx + 8]
    
    my_lst_find_cond:
    test rbx, rbx
    jne my_lst_find_loop

    xor eax, eax
    pop rbx
    ret