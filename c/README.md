**[Back](../README.md)**

# Projects

## Data structures

### Generic api

    - add
    - delete
    - reverse
    - get
    - contains
    - insert
    - print
    - clear

    - init
    - deconstruct

- **[Binary Search Tree](./datastructures/binary_search_tree)**
- **[Linked List](./datastructures/linked_list)**
- **[Double Linked List](./datastructures/double_linked_list)**
- **[Dynamic Array](./datastructures/dynamic_array)**

# Memory layout

**[Reference](https://www.geeksforgeeks.org/c/memory-layout-of-c-program/)**

<pre>
| stack                 | <- High Address
| vvvvvvvvvvvvvvvvvvvvv |
|                       |
| ^^^^^^^^^^^^^^^^^^^^^ |
| heap                  |
| uninitialized (.bss)  |
| initialized (.data)   |
| code (.text)          | <- Low Address
</pre>

## stack

```C
void func() {

    // Stored in the stack
    int local_var = 10;
}

int main() {
    func();
    return 0;
}
```

## heap

```C
#include <stdlib.h>

int main() {

    // Create an integer pointer
    int *ptr = (int*) malloc(sizeof(int) * 10);
    return 0;
}
```

## uninitialized data segment (bss)

bss = "block started by symbol"

```C
#include <stdio.h>

// Global uninitialized variables (stored in BSS segment)
int globalVar;
char message[50];

int main()
{
    // Static uninitialized variable (also stored in BSS)
    static int staticVar;

    // Assigning values at runtime
    globalVar = 10;
    staticVar = 20;

    return 0;
}
```

## initialized data segment

```C
// Global variables (stored in initialized data segment)
int globalVar = 10;
char message[] = "Hello";

int main() {
  // Static variable (also stored in initialized data segment)
  static int staticVar = 20;

  return 0;
}
```

# Unsafe functions

| Banned by git | Type                | Deprecated           | Better                | Vulnerability                   | Explanation                                                                                                       |
| ------------- | ------------------- | -------------------- | --------------------- | ------------------------------- | ----------------------------------------------------------------------------------------------------------------- |
| n             | String Manipulation | gets()               | fgets()               | Buffer overflow                 | Buffer overflow because it does not check input length                                                            |
| y             | String Manipulation | strcpy()             | strncpy() / strlcpy() | Buffer overflow                 | Copies data into dest until it encounters \0 without checking length                                              |
| y             | String Manipulation | strcat()             | strncat() / strlcat() | Buffer overflow                 | Appends data into dest until it encounters \0 without checking length                                             |
| y             | String Manipulation | sprintf              | snprintf()            | Buffer overflow                 | Formats data into string but if string is longer than buffer -> overflow                                          |
| n             | Input               | scanf() / fscanf()   | fgets()               | Buffer overflow                 | Will read until whitespace, regardless of buffer size                                                             |
| n             | Standard Library    | memcpy() / memmove() |                       | Buffer overflow                 | With length n > length buf will write past buffer                                                                 |
| n             | Conversion          | atoi() / atol()      | strtol()              | Logical error                   | Cannot distinguish between successful conversion of 0 and failed conversion (because failed conversion returns 0) |
| n             | Conversion          | atof()               | strtod()              | Logical error                   | Cannot distinguish between successful conversion of 0 and failed conversion (because failed conversion returns 0) |
| n             |                     | system()             | execve() / fork()     | Command injection               | Invokes /bin/sh, if user can insert command can run anything in shell                                             |
| y             |                     | asctime()            | strftime()            | Thread-unsafe / Buffer Overflow | Uses buffer shared across all calls, thus not thread-safe. Also does not check for length                         |
| y             |                     | strncpy              |                       |                                 |
| y             |                     | strncat              |                       |                                 |
| y             |                     | strtok               |                       |                                 |
| y             |                     | strtok_r             |                       |                                 |
| y             |                     | vprintf              |                       |                                 |
| y             |                     | gmtime               |                       |                                 |
| y             |                     | localtime            |                       |                                 |
| y             |                     | ctime                |                       |                                 |
| y             |                     | ctime_r              |                       |                                 |
| y             |                     | asctime_r            |                       |                                 |
| y             |                     | mktemp               |                       |                                 |
