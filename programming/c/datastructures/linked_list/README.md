**[Back](../README.md)**

# Binary Search Tree

Implementation with a double linked list

## API

- bt_add(Tree\* tree, int val); -> Adds val to tree
- bt_remove(Tree\* tree, int val); -> Removes val from tree
- bt_print(Tree\* tree); -> Prints tree
- bt_max(Tree\* tree); -> Returns max value in tree
- bt_min(Tree\* tree); -> Returns min value in tree
- bt_contains(Tree\* tree, int val); -> Returns 1 if val in tree, else 0

### Print

Printing is done in a directory-style tree like this

<pre>
|  |- 15
|  |  |  |- 14
|  |  |- 13
|  |  |  |  |- 12
|  |  |  |  |  |- 11
|  |  |  |  |  |  |- 10
|  |  |  |- 9
|  |  |  |  |- 8
|- 7
|  |  |- 6
|  |- 5
|  |  |  |- 4
|  |  |- 3
|  |  |  |  |- 2
|  |  |  |  |  |- 1
|  |  |  |- 0
</pre>

### Remove

<pre>
  2    -1    2
 / \  --->    \
1   4          4

  2    -4    2
 / \  --->  / \
1   4      1   3
   /
  3

  2      -4    2
 / \    --->  / \
1   4        1   5
     \
      5

  2    -2    3          3
 / \  --->  / \  --->  / \
1   4      1   4      1   4
   /          /
  3          2
</pre>
