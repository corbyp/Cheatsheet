**[Back](../README.md)**

# Projects

- **[Binary Search Tree](./binary_search_tree)**
- **[Linked List](./linked_list)**

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
