# Evaluating channel matrix for L1D

This program tries to establish a communication channel between a trojan and a spy.
The communication channel is:
- trojan choose a L1D set among the ones available (prime)
- spy choose a L1D set and establish if it is the same as the trojan (probe), by timing a lw instruction.

This implementation switches between hardware security context to prevent leakage.
If the core does not support HSC, the HSC switch will be replaced by a nop.