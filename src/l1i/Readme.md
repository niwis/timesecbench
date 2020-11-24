# Evaluating channel matrix for L1I

For this attack, we fill parts of memory, (that can fit the whole L1I cache) with "ret" instructions: one (L1I-sized) block at the start of the memory, one block at the end.


In this attack, the trojan choose a L1I set. We prime the attack by filling L1I with "ret" from the end of the memory.
Then we touch one set by jumping to a return instructions from the block at the start of the memory (therefore invalidating one line, previously filled by data from the end of the memory).

The spy determines if a set has been touched or not by timing a jump to the block at the start.