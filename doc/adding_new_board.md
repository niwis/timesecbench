# Adding a new board

Adding a board is required to set up a mechanism to transmit the benchmark results.

The following function must be implemented:
- *void transmit(unsigned int input, unsigned int output, unsigned int timing)*, transmits input, output and timing to an entity than can exploit it (over UART, registers, ...).
- *unsigned int read_time(void)*