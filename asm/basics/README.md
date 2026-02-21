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

legend: l = lower, h = higher

# Data types

| Name        | In register | Type  | Bits | Bytes | Defining |
| ----------- | ----------- | ----- | ---- | ----- | -------- |
| Byte        | b           | int8  | 8    | 1     | .byte    |
| Word        | w           | int16 | 16   | 2     | .short   |
| Double Word | d           | int32 | 32   | 4     | .int     |
| Quad Word   |             | int64 | 64   | 8     | .quad    |
| Single      |             | float | 32   | 10    | real4    |
| Double      |             | float | 64   | 8     | real8    |
| Extended    |             | float | 128  | 16    | real10   |

legend: b = byte (8b), w = word (16b), d = double word (32b), q = quad word (64b), l = lower, h = higher

# Segments

| Name                    | In asm  | Explanation                                                  |
| ----------------------- | ------- | ------------------------------------------------------------ |
| Code                    | .text   | Executable machine instructions (Read-Only/Exec)             |
| Data                    | .data   | Global/Static variables with initial values (Read/Write)     |
| Read-only data          | .rodata | Constants, strings, and look-up tables (Read-Only)           |
| Block started by symbol | .bss    | Reserved space for variables; automatically zeroed by the OS |

# Instructions

# Syscalls

https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/

# File Descriptors

0 stdin
1 stdout
2 stderr
