.global _start

.section .text
_start:
    xor     %rcx, %rcx          # i = 0
    xor     %rbx, %rbx          # count = 0

loop_HW1:                       
    movzbq  str(%rcx), %rax     
    cmp     $0, %al
    je      end_HW1           

    cmp     $'a', %al
    je      inc_count_HW1
    cmp     $'e', %al
    je      inc_count_HW1
    cmp     $'i', %al
    je      inc_count_HW1
    cmp     $'o', %al
    je      inc_count_HW1
    cmp     $'u', %al
    je      inc_count_HW1
    cmp     $'A', %al
    je      inc_count_HW1
    cmp     $'E', %al
    je      inc_count_HW1
    cmp     $'I', %al
    je      inc_count_HW1
    cmp     $'O', %al
    je      inc_count_HW1
    cmp     $'U', %al
    je      inc_count_HW1    

    jmp     next_char_HW1      

inc_count_HW1:                 
    inc     %rbx

next_char_HW1:                
    inc     %rcx
    jmp     loop_HW1

end_HW1:                        
    movl    %ebx, count