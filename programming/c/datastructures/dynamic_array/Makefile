INCLUDE = include/
C_FILES = $(wildcard src/*.c)

TEST_INCLUDE = tests/
TEST_FILES = $(wildcard tests/*.c)

TARGET = app

CFLAGS = -I$(INCLUDE) -Wall -Wextra
CFLAGS_RELEASE = -O2 -DNDEBUG
CFLAGS_DEBUG = -g -O0
CFLAGS_TEST = -I$(TEST_INCLUDE) -lunity
CFLAGS_SANITIZE = -fsanitize=address,undefined,leak -g

.PHONY: all run trun drun srun compile tcompile dcompile scompile exec dexec texec valgrind clean

all: trun

# production
compile:
	$(CC) $(C_FILES) $(CFLAGS) $(CFLAGS_RELEASE) -o $(TARGET)

exec:
	./$(TARGET)

# debug
dcompile:
	$(CC) $(C_FILES) $(CFLAGS) $(CFLAGS_DEBUG) -o $(TARGET)

dexec:
	gef $(TARGET)

# test
tcompile:
	$(CC) $(C_FILES) $(TEST_FILES) $(CFLAGS) $(CFLAGS_TEST) -o $(TARGET)

texec:
	./$(TARGET)

#sanitize
scompile:
	$(CC) $(C_FILES) $(TEST_FILES) $(CFLAGS) $(CFLAGS_SANITIZE) $(CFLAGS_TEST) -o $(TARGET)

valgrind:
	valgrind ./$(TARGET)

# general
clean:
	rm -rf .cache $(TARGET)

run: compile exec clean
trun: tcompile texec clean
drun: dcompile dexec clean
srun: scompile exec clean tcompile valgrind clean
