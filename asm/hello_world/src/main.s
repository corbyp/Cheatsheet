.global _start
.intel_syntax noprefix

_start:
        # write to out
        mov rax, 1 # write syscall
        mov rdi, 1 # stdout fd
        lea rsi, [hello_world] # lea=load effected address
        mov rdx, 14 # size of the string (including \n\0)
        syscall

        # sys_exit
        mov rax, 60 # exit syscall
        mov rdi, 0 # error code
        syscall

hello_world:
        .asciz "Hello, World!\n"
