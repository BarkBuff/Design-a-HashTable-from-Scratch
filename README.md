OpenAddressHashTable is a compact C library that keeps data exactly where it belongs without making a scene. It’s fast, quiet, and built around open addressing, so every key slides into its slot without leaving a breadcrumb trail of pointers behind it.

The whole point is simple: clean structure leads to clean speed. No abstractions hovering overhead, no frameworks whispering in the background. Just raw mechanics doing what they’re supposed to do. C was chosen because it shows the machinery-memory, collisions, probing—all the fun stuff most languages politely hide.

It’s made for engineers who like understanding the trick without explaining the trick. Everything works the way it looks like it should work, and anything clever stays between the lines, out of sight.

Lightweight to pull in, extremely predictable, and just suspicious enough to feel powerful without revealing exactly why.
