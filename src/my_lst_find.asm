global my_lst_find
extern mystrcmp

section .text

; -------------------------------------
; Args:
; rdi - node
; rsi - s
;
; Returns
; rax - node
; -------------------------------------
my_lst_find:
    push rbx
    mov rbx, rdi
    jmp my_lst_find_cond

    my_lst_find_loop:
    mov rdi, QWORD [rbx]
    call mystrcmp

    test rax, rax
    je my_lst_find_continue

    mov rax, rbx
    pop rbx
    ret 

    my_lst_find_continue:
    mov rbx, QWORD [rbx + 8]
    
    my_lst_find_cond:
    test rbx, rbx
    jne my_lst_find_loop

    xor rax, rax
    pop rbx
    ret