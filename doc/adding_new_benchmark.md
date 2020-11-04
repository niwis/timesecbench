# Adding a new benchmark

The TimeSecBench benchmarks are all built on the same model: measuring a channel matrix for a covert channel.
For *i* an input symbol and *o* an output symbol, the **trojan** sends *i* over the channel and we measure the timing for the **spy** trying to read *o*.

A timing dependency will show in the resulting channel matrix, proving the information leakage.

Adding a new benchmark requires to implement the following functions:
- *void initialise_benchmark (void)*, called once per benchmark.
- *void prepare_trojan(void)*, called every time before the trojan.
- *void prepare_spy(void)*, called every time before the spy.
- *void trojan (unsigned int input)*, sends a value over the covert channel.
- *unsigned int spy(unsigned int output)*, tries to read a value from the channel and return the timing for that operation.