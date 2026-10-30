# Red-Black Tree in C

A self-balancing binary search tree implemented in C using a tree ADT.
Every operation, including insertion and deletion, keeps the tree balanced
so search, insert and delete all run in **O(log n)**.

## Red-black properties maintained

1. Every node is either red or black.
2. The root is black.
3. All leaves (NIL) are black.
4. A red node never has a red child.
5. Every path from a node to its descendant NIL leaves has the same number of black nodes.

## Operations

| Option | Operation       | Function                       |
|--------|-----------------|--------------------------------|
| 1      | Insert          | `insert(tree_t **root, data_t)`|
| 2      | Delete          | `delete(tree_t **root, data_t)`|
| 3      | Find minimum    | `find_minimum(...)`            |
| 4      | Delete minimum  | `delete_minimum(...)`          |
| 5      | Find maximum    | `find_maximum(...)`            |
| 6      | Delete maximum  | `delete_maximum(...)`          |
| 7      | Search          | `search(tree_t *root, data_t)` |

All functions return `SUCCESS` or `FAILURE` (for example: duplicate insert,
deleting a missing value, or querying an empty tree).

## Build and run

```bash
make          # builds the ./rbt program
./rbt         # interactive menu
make test     # randomized stress test
make clean
```

## Sample session

The tree is printed sideways: the root is on the left, the right subtree is
on top and the left subtree is below. `(R)` is a red node and `(B)` is black.
After inserting 10, 20, 30, 40 and 50 in order:

```
        50(R)
    40(B)
        30(R)
20(B)
    10(B)
```

A plain BST would have become a straight line of 5 nodes. Here the tree
rotated and recolored itself to stay balanced.

## How it works

- **`rotate.c`**: left and right rotations, the only structural change used for balancing.
- **`insert.c`**: inserts a red node like a normal BST, then fixes a red-red violation on the way back up the recursion:
  - uncle red: recolor and push the problem up;
  - uncle black, node on the inside: rotate to make a straight line;
  - uncle black, node on the outside: rotate the grandparent and recolor.
- **`delete.c`**: removes the node (replacing a two-child node with its in-order successor). If a black leaf is removed, the subtree becomes one black node short, and the parent repairs it using the sibling's color and its children's colors (four cases: red sibling, black sibling with black children, near child red, far child red).
- **`delete_min.c` / `delete_max.c`**: find the extreme value and reuse `delete`.

The node struct has no parent pointer. Fix-ups are done during the recursion, so the call stack provides the parent and grandparent.

## Testing

`tests/test_rbt.c` runs 1.2 million random insert, delete, search and
min/max operations. After every operation it checks that the tree is a valid
BST and satisfies all red-black properties, and it compares results against a
simple presence table. The code was also run under AddressSanitizer and
UndefinedBehaviorSanitizer with no errors.

## Files

```
rbt.h          node struct, constants, prototypes
main.c         menu-driven driver
insert.c  delete.c  search.c
find_min.c  find_max.c  delete_min.c  delete_max.c
rotate.c  print_tree.c
tests/test_rbt.c
Makefile
```
