SRC = src/
INCLUDE = include/

C_FILES = $(addprefix $(SRC), main.c printf.c)

TARGET = printf

all: run

compile: $(C_FILES)
	$(CC) -I$(INCLUDE) $(C_FILES) -o $(TARGET)

run_compile: $(C_FILES)
	./$(TARGET)

compile_debug: $(C_FILES)
	$(CC) -I$(INCLUDE) $(C_FILES) -o $(TARGET) -g

run_debug: $(C_FILES)
	gdb $(TARGET)

run: compile run_compile
rund: compile_debug run_debug

clean: $(TARGET)
	rm $(TARGET)
