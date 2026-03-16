SRC = src/
INCLUDE = include/

C_FILES = $(addprefix $(SRC), *.c)

TARGET = app

all: run

# normal
compile: $(C_FILES)
	$(CC) -I$(INCLUDE) $(C_FILES) -o $(TARGET)

exec: $(C_FILES)
	./$(TARGET)

# debug
compiled: $(C_FILES)
	$(CC) -I$(INCLUDE) $(C_FILES) -o $(TARGET) -g

execd: $(C_FILES)
	gdb $(TARGET)

# general
clean: $(TARGET)
	rm -rf .cache $(TARGET)

run: compile exec clean
debug: compiled execd clean