ASM = nasm
LD = ld
TARGET = app
SRC = src/

S_FILES = $(addprefix $(SRC), main.asm)

all: run

# normal
compile: $(S_FILES)
	$(ASM) -f elf64 $(S_FILES) -o $(TARGET).o

exec: $(TARGET)
	./$(TARGET)

# debug
compiled: $(S_FILES)
	$(ASM) -f elf64 -g -F dwarf $(S_FILES) -o $(TARGET).o

execd: $(TARGET)
	gdb $(TARGET)

# general
link: $(S_FILES)
	$(LD) -o $(TARGET) $(TARGET).o

clean:
	rm $(TARGET) $(TARGET).o

build: compile link
buildd: compile_debug link
run: build exec clean
rund: buildd execd clean