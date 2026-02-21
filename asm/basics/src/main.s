.data
        myByte: .byte 0x67
        myWord: .quad 123

.text
.global _start
.intel_syntax noprefix # %rax -> rax

_start:
        mov rax, -1
        # mov eax, 0
        mov ax, 0xaaaa
        mov al, 0xbb

        ret
