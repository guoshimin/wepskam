This is what the author has:

![Figure 3.10: Sequential Read Access, NPAD=0](https://static.lwn.net/images/cpumemory/cpumemory.22.png)

(https://lwn.net/Articles/252125/, figure 3.10)

The CPU of my system is Intel(R) Xeon(R) CPU E5-1650 v4 @ 3.60GHz. Here are my results:

![my result](seq_read.png)

Compared to the author, the cycles/op held constant for longer.

To compare multiple elem sizes, the author has

![Figure 3.11: Sequential Read for Several Sizes](https://static.lwn.net/images/cpumemory/cpumemory.23.png)

(https://lwn.net/Articles/252125/, Figure 3.11)

I have

![my result](seq_read_multiple_elem_sizes.png)

My CPU has the following cache sizes:

- L1D: 32 KB per core
- L2: 256 KB per core
- L3: 15 MB

We can clearly see a jump after 2^15, when the working set no longer fits in the L1D.

The next jump in only visible for elem_size=256, at 2^18, when the working set no longer fits in the L2 cache.

Then the jump happens between 2^23 and 2^24, when the working set no longer fits in the L3 cache.
