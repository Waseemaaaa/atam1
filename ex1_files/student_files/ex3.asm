.global _start

.section .text
_start:
    lea str(%rip), %rsi           
    lea enc(%rip), %rdi           
    
    xor %r8, %r8                  
    mov $1, %r9                   
    
    movzbl (%rsi), %r8d           
    cmp $0, %r8b                  
    je write_null_and_done_HW1    
    
    inc %rsi                      

RLE_loop_HW1:
    movzbl (%rsi), %eax           
    
    cmp $0, %al           
    je write_last_sequence_HW1    

    cmp %r8b, %al                 
    je increment_count_HW1        
    
    mov %r9b, %cl                 
    add $'0', %cl                 
    movb %cl, (%rdi)              
    inc %rdi                      

    movb %r8b, (%rdi)             
    inc %rdi                      

    mov %rax, %r8                 
    mov $1, %r9                   

    jmp next_iteration_HW1        

increment_count_HW1:
    inc %r9                       
    
next_iteration_HW1:
    inc %rsi                      
    jmp RLE_loop_HW1              

write_last_sequence_HW1:
    mov %r9b, %cl         
    add $'0', %cl         
    movb %cl, (%rdi)      
    inc %rdi              
    
    movb %r8b, (%rdi)     
    inc %rdi              

    jmp write_null_and_done_HW1

write_null_and_done_HW1:
    movb $0, (%rdi)