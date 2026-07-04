# Advanced C Roadmap 🔧

A hands-on journey through advanced C programming concepts, built from scratch with zero shortcuts. Every project was written without copying tutorials — debugged, verified with Valgrind, and understood deeply before moving on.

---

## Why This Exists

After finishing the basics of C (variables, loops, functions, arrays), I wanted to go deeper — not just learn syntax, but actually understand how memory works, how data structures are built from the ground up, and how systems-level programs operate. This repo documents that journey across 10 concepts, each with a real project.

---

## Concepts & Projects

### 1. Pointers
**Constraint:** No array indexing (`[]`) allowed — pointer arithmetic only.

Built a mini string library from scratch:
- `my_strlen` — pointer traversal + subtraction to count characters
- `my_strcpy` — dual-pointer lockstep copy including null terminator
- `my_memcpy` — raw byte copying via `void *` and `unsigned char *` casting

**Key lessons:** pointer vs value distinction, `*ptr` vs `ptr`, off-by-one edge cases, `do-while` vs `while` for null terminator handling.

---

### 2. Dynamic Memory Management
**Tool:** Valgrind (`--leak-check=full`) as success criterion — zero leaks required.

Built a dynamic array (vector) that grows automatically:
- `create` — heap allocates initial block for 2 elements
- `push` — writes element, doubles capacity when full via `malloc` → `memcpy` → `free` cycle
- `get` — index-based element access
- `cleanup` — frees heap block, nulls pointer to prevent use-after-free

**Key lessons:** stack vs heap, `malloc`/`realloc`/`free`, dangling pointers, amortized O(1) growth.

---

### 3. Structs & Memory Layout
**Tool:** `#pragma pack(1)` to control struct padding for binary file parsing.

Built a BMP image header parser:
- Maps C structs directly onto raw binary file bytes
- Reads width, height, file size, bits per pixel from any `.bmp` file
- Verified parsed values against actual file properties

**Key lessons:** struct padding and alignment, `fread` into structs, `offsetof`, why `char *` can't be serialized to disk.

---

### 4. Linked Data Structures
**Project:** Command history manager (like terminal up/down arrow navigation).

Built a doubly linked list with:
- `add` — appends new command node to tail, handles empty and non-empty list cases
- `back` / `forward` — navigate through history via `prev`/`next` pointers
- `print_all` — walks list from head to tail
- `cleanup` — frees every node and its string, saves `next` before freeing

**Key lessons:** pointer stitching, heap-allocated structs, `->` notation, use-after-free prevention.

---

### 5. File I/O & Binary Data
**Project:** Key-value binary database that persists between program runs.

- Fixed-size `Record` structs (`char key[32]`, `char value[64]`) written as raw bytes
- `save` — `fwrite` all records to binary file
- `load` — `fread` records back on startup, `count` set from return value
- `get` — linear scan by key using `strcmp`
- `memset` to zero unused struct bytes before writing (fixes Valgrind warnings)

**Key lessons:** why `char[]` works for serialization but `char *` doesn't, `fopen`/`fread`/`fwrite`/`fclose`, binary vs text mode.

---

### 6. Trees & Recursion
**Project:** BST-based autocomplete dictionary.

Built a binary search tree with:
- `insert` — recursive, returns updated root so parent can reconnect
- `search` — recursive O(log n) lookup, returns 1/0
- `print_all` — in-order traversal (left → print → right) produces alphabetical output
- `autocomplete` — traverses entire tree, prints all words matching a prefix via `strncmp`
- `cleanup` — post-order recursive free (children before parent)

**Key lessons:** recursive struct pointers, in-order vs post-order traversal, why cleanup order matters, `strncmp` for prefix matching.

---

### 7. Hash Tables
**Project:** Hash map with chaining for collision resolution.

Built from scratch:
- `hash` — djb2-style function using prime 31, `unsigned int` to prevent negative indices
- `create_table` — `malloc`s slot array, initializes all to `NULL`
- `insert` — hashes key, prepends new entry to chain at that slot
- `get` — hashes key, walks chain with `strcmp`
- `cleanup` — frees keys, values, entry nodes, then slot array

**Key lessons:** hash collisions, chaining via linked lists, why `unsigned int` matters for modulo, O(1) average lookup vs O(n) linear scan.

---

### 8. Bitwise Operations
**Project:** Bitmap memory allocator — tracks 64 "pages" using a single `unsigned long long`.

- `allocate` — finds first free bit, sets it with `bitmap |= (1ULL << n)`, returns page number
- `free_page` — clears bit with `bitmap &= ~(1ULL << n)`
- `is_allocated` — checks bit with `bitmap & (1ULL << n)`
- `print_map` — prints all 64 bits showing free/allocated state

**Key lessons:** bit masking, `1ULL` vs `1` for 64-bit shifts, set/clear/check patterns, memory efficiency (1 bit per page vs 1 byte).

---

### 9. Multi-file Projects & Build Systems
**Project:** Refactored hash table into proper multi-file structure.

```
hash_table_project/
├── entry.h          — Entry struct with header guards
├── entry.c          — Entry include
├── hash_table.h     — HashTable struct + function declarations
├── hash_table.c     — All function implementations
├── main.c           — main() only
└── Makefile         — incremental build rules
```

**Key lessons:** `.h` for interfaces, `.c` for implementations, header guards (`#ifndef`/`#define`/`#endif`), `gcc -c` for object files, incremental compilation with `make`.


## Tools Used

| Tool | Purpose |
|------|---------|
| `gcc` | Compilation |
| `valgrind --leak-check=full` | Memory leak and error detection |
| `make` | Incremental build system |
| WSL (Ubuntu) | Linux environment on Windows |
| VS Code | Editor |

---

## What I Learned

Every project in this repo was built without copying implementations from tutorials. The process was:
1. Understand the concept
2. Write the code from my own logic
3. Debug real failures (segfaults, memory leaks, off-by-ones)
4. Verify with Valgrind before moving on

The recurring bug patterns I learned to recognize and fix:
- Forgetting to advance pointers in loops
- Off-by-one errors with null terminators
- Freeing memory before reading it (use-after-free)
- Stack vs heap allocation lifetime
- `unsigned` vs signed for bit operations and hash functions

---

## Running Any Project

Each concept has its own folder. For single-file projects:
```bash
gcc -o output file.c
valgrind --leak-check=full ./output
```

For multi-file projects (hash table, shell):
```bash
make
valgrind --leak-check=full ./program
```

---

*Built as part of a self-directed advanced C learning roadmap.*
