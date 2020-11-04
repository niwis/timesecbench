# Evaluating channel matrix for BTB

The branch target buffer remembers the last destination for direct jumps (jal, j).

The BTB and the BHT interacts, but we will disregard it since an attacker does not usually have this kind of information.

## The training_btb gadget

We set up two destinations for our jumps called "ret_zero" and "ret_one".
The training_btb gadget is

```
training_btb:
    j ret_zero
    j ret_zero
    ...
    j ret_zero
```
With as many jumps as necessary to fill the btb.
The jumps can be rewritten with "j ret_one" when necessary (we precompute the corresponding opcode at the start of the attack).
As a consequence, since we miss the FenceI instruction (at the time of writing this), we reduce the size of the L1I cache.

## Prime

We firt setup the btb by calling twice all the jumps in the training_btb gadget.

## Touch

The trojan then touch one of the jumps:
- first the attacker rewrite the jump with "j ret_one"
- the jump is called
- the jump is reseted to "j ret_zero"

## Poke

The spy then tries to determine which jump has been touched.
It selects a jump, call it and measure the time it takes to return.