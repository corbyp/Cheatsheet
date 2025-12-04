SRC = src/
INCLUDE = ./include -lcrypto

C_FILES = $(addprefix $(SRC), main.c)

TARGET = app

all: run

compile: $(C_FILES)
	$(CC) -I$(INCLUDE) $(C_FILES) -o $(TARGET)

run_compile: $(C_FILES)
	./$(TARGET) $(ARGS)

run: compile run_compile

compile_debug: $(C_FILES)
	$(CC) -I$(INCLUDE) $(C_FILES) -o $(TARGET) -g

run_debug: $(C_FILES)
	gdb $(TARGET)

debug: compile_debug run_debug

clean: $(TARGET)
	rm $(TARGET)
