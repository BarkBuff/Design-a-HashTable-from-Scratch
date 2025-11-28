# OpenAddressHashTable

OpenAddressHashTable is a small, fast, and predictable C library implementing a hash table with **open addressing**. No pointer forests, no abstraction fog—just direct, transparent data layout and collision handling you can actually reason about.

This library exists for engineers who want to see the machinery, not hide from it. Probing, collisions, resizing…it’s all right there, exactly where it should be. Clean structure, clean speed.

### Why use it?

* **Lightweight.** Minimal code, minimal overhead. Pull it in and go.
* **Predictable performance.** Open addressing keeps memory tight and cache-friendly.
* **No hidden magic.** Behavior is explicit. If it’s doing something clever, you can see it in the source.
* **Pure C.** Ideal for systems work, embedded environments, or anything where memory layout matters.

### Features

* Open addressing with linear or configurable probing
* Fixed or dynamic table size
* Simple API for insert, lookup, and delete
* Optional user-defined hash functions
* Compact, pointer-free data storage

### When this library makes sense

Use it when you care about:

* Cache behavior
* Deterministic data layout
* Avoiding dynamic pointer webs
* Understanding (or teaching) how hash tables behave under the hood

This isn’t a “drop it into your giant framework” tool. It’s for people who like knowing what their hash table is doing at 3 a.m. when the profiler starts whispering.
