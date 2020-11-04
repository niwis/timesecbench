# Evaluating channel matrix for BHT

The branch history table tries to determine if a branch instruction will be taken or not. Usually we count how many branches were taken during the last 4 branch execution (for one branch instruction).

## Training gadget
We fill a memory region with
```
TRAINING_DATA_ADD:
    blt a0, a1, 4
    blt a0, a1, 4
    ...
    blt a0, a1, 4
    ret
```
We have as many blt as necessary to fill the BHT.

Priming is done by choosing the value for a0 and a1 then jumping to TRAINING_DATA_ADD. Whatever how the condition is resolved (true/TAKEN or false/NOT TAKEN), all branch instructions will be called with the same condition.
By priming 4 times, we can decide the state of the BHT (all taken or all not taken).

We train the gadget with 2 < 1 => Not taken

## Poking gadget
We fill a memory region with
```
POKING_DATA_ADD:
    blt a0, a1, XXX <end>
    blt a0, a1, XXX <end>
    ...
    blt a0, a1, 8 <end>
    blt a0, a1, 4 <end>
end:
    ret
```
We have as many blt as necessary to fill the BHT.


The trojan will choose one bht entry (or equivalently, one branch instruction from the poking gadget) and fill a true condition (1 < 2).

Jumping to a branch instruction in the poking gadget with a true condition is the "touch" operation.
The trojan touches 4 times to set the bht entry accordingly.

The the spy will poke one bht entry (or equivalently, one branch instruction from the poking gadget) by jumping to this branch with a true condition (1 < 2), while measuring the time it takes.

If the time is short, the trojan has touched this bht entry.