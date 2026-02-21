SRC = src/
INCLUDE = include/

S_FILES = $(addprefix $(SRC), main.s)

TARGET = app

all: run

compile: $(S_FILES)
	$(AS) $(S_FILES) -o $(TARGET).o

link: $(S_FILES)
	$(CC) -o $(TARGET) $(TARGET).o -nostdlib -static

build: compile link

debug: $(TARGET)
	gdb $(TARGET)

exec: $(TARGET)
	./$(TARGET)

clean: $(TARGET)
	rm $(TARGET) $(TARGET).o

run: compile link exec
rund: compile link debug

