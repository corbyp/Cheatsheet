**[Back](../README.md)**

# Description

- [󰗃 Tutorial](https://youtube.com/playlist?list=PLKK11Ligqitg9MOX3-0tFT1Rmh3uJp7kA&si=rk7nkWYtIG3cl8ud)
- [󰊤 Tutorial](https://github.com/luamfb/intro_x86-64/blob/master/0_basic.asm)

## Syscall table

https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/

```sh
ausyscall --dump
man syscalls
man 2 <syscall_name>
```

# Important file descriptors

- 0 stdin
- 1 stdout
- 2 stderr

# Registers

<pre>
1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 64 Bit
[                                     rax                                     ] 64 Bit
                                        [                 eax                 ] 32 Bit
                                                            [       ax        ] 16 Bit
                                                            [  ah   ] [  al   ]  8 Bit
</pre>

| Name                | Register | 8Bit lower | 8 Bit higher | 16Bit | 32Bit  | 64Bit  |
| ------------------- | -------- | ---------- | ------------ | ----- | ------ | ------ |
| Accumulator         | 0        | al         | ah           | ax    | eax    | rax    |
| Base                | 1        | bl         | bh           | bx    | ebx    | rbx    |
| Counter             | 2        | cl         | ch           | cx    | ecx    | rcx    |
| Data                | 3        | dl         | dh           | dx    | edx    | rdx    |
| Source index        | 4        | sil        |              | si    | esi    | rsi    |
| Destination index   | 5        | dil        |              | di    | edi    | rdi    |
| Stack pointer       | 6        | spl        |              | sp    | esp    | rsp    |
| Base pointer        | 7        | bpl        |              | bp    | ebp    | rbp    |
| Instruction pointer | 8        |            |              |       | eip    | rip    |
| R8                  | 9        | r8b        |              | r8w   | r8d    | r8     |
| R9                  | 10       | r9b        |              | r9w   | r9d    | r9     |
| R10                 | 11       | r10b       |              | r10w  | r10d   | r10    |
| R11                 | 12       | r11b       |              | r11w  | r11d   | r11    |
| R12                 | 13       | r12b       |              | r12w  | r12d   | r12    |
| R13                 | 14       | r13b       |              | r13w  | r13d   | r13    |
| R14                 | 15       | r14b       |              | r14w  | r14d   | r14    |
| R15                 | 16       | r15b       |              | r15w  | r15d   | r15    |
| Flags               |          |            |              | flags | eflags | rflags |
| code segment        |          |            |              | cs    |        |        |
| data segment        |          |            |              | ds    |        |        |
| extra segment       |          |            |              | es    |        |        |
| stack segment       |          |            |              | ss    |        |        |
|                     |          |            |              | fs    |        |        |
|                     |          |            |              | gs    |        |        |

legend:

- l = lower, h = higher
- b = byte (8b=1B), w = word (16b=2B), d = doule word (32b = 4B)

# Data types

```asm
section .data ; global variables
        byte_1 db 0x12               ; db = declare byte (1 byte)
        byte_2 dw 0x1234             ; dw = declare word (2 bytes)
        byte_4 dd 0x12345678         ; dd = declare doubleword (4 bytes)
        byte_8 dq 0x1234567812345678 ; dq = declare quadword (8 bytes)

section .rodata ; gloal constants
        string: db "Hello, World!", 0xa, 0 ; array of bytes, 0xa=newline, 0=nullbyte

section .bss ; space reserved at program startup
section .text ; CPU instructions
global _start ; exports _start for linker to find
_start: ; label stores addresses, _start is special program entry point
        mov rax, 0 ; mov DEST, SOURCE
        inc rax
        dec rax
        add rax, rbx ; rax += rbx
        sub rax, rbx ; rax -= rbx

        mov rax, 60 ;
        mov rdi, 0
        syscall
```
