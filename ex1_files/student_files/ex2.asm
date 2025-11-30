.global _start

.section .text
_start:

    xor %rcx, %rcx
    lea exp, %rsi
    xor %r8, %r8
    xor %r9, %r9
    xor %r10, %r10
    xor %r11, %r11
    xor %r12, %r12

read_loop_HW1:
    movzbq (%rsi, %rcx, 1), %rax
    cmp $0, %al
    je done_HW1

    cmp $',', %al
    je next_char_HW1

    cmp $'0', %al
    jb check_operators_HW1

    sub $'0', %al
    mov %r11, %r12
    mov %r10, %r11
    mov %r9, %r10
    mov %r8, %r9
    mov %rax, %r8
    jmp next_char_HW1

check_operators_HW1:
    cmp $'+', %al
    je do_plus_HW1
    cmp $'-', %al
    je do_minus_HW1
    cmp $'*', %al
    je do_mult_HW1
    cmp $'/', %al
    je do_div_HW1
    jmp next_char_HW1

do_plus_HW1:
    add %r9, %r8
    jmp shift_stack_up_HW1

do_minus_HW1:
    sub %r8, %r9
    mov %r9, %r8
    jmp shift_stack_up_HW1

do_mult_HW1:
    imul %r9, %r8
    jmp shift_stack_up_HW1

do_div_HW1:
    mov %r9, %rax
    xor %rdx, %rdx
    div %r8
    mov %rax, %r8
    jmp shift_stack_up_HW1

shift_stack_up_HW1:
    mov %r10, %r9
    mov %r11, %r10
    mov %r12, %r11
    xor %r12, %r12

next_char_HW1:
    inc %rcx
    jmp read_loop_HW1

done_HW1:
    movl %r8d, res