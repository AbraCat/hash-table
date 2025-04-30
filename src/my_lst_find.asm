global my_lst_find
extern mystrcmp

section .text

; -------------------------------------
; Args:
; rdi - node
; rdi - s
;
; Returns
; rax - node
; -------------------------------------
my_lst_find:

    jmp my_lst_find_cond

    my_lst_find_loop:
    mov rdi, rdi

    push rdi
    push rsi
    call mystrcmp
    pop rsi
    pop rdi

    test rax, rax
    je my_lst_find_continue
    mov rax, rdi
    ret 

    my_lst_find_continue:
    mov rdi, QWORD [rdi]
    my_lst_find_cond:
    test rdi, rdi
    jne my_lst_find_loop

    xor rax, rax
    ret