/*
 * File: support.h
 * Project: support
 * Created Date: Wednesday November 4th 2020
 * Author: Embench
 * -----
 * Last Modified: Wednesday, 26th May 2021 3:03:11 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef SUPPORT_H
#define SUPPORT_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define REPETITION_FACTOR 1

/* Include board support header if we have one */

// #ifdef HAVE_BOARDSUPPORT_H
#include "boardsupport.h"
// #endif

// #ifdef HAVE_CHIPSUPPORT_H
#include "chipsupport.h"
// #endif


/* Standard functions implemented for each board */

void initialise_board (void);

/* Every benchmark implements this for one-off data initialization.  This is
   only used for initialization that is independent of how often benchmark ()
   is called. */

void initialise_benchmark (void);

/* Every benchmark implements this as its entry point. Don't allow it to be
   inlined! */

void benchmark (void) __attribute__ ((noinline));

/*
This function is used to communicate one result. It is called multiple times per benchmark.
Must be implemented by the board support.
*/
void transmit(WORD input, WORD output, WORD timing);



/*
Call this function to denote the end of the benchmark (required since the number of transmit() call is variable).
*/
void end_benchmark(void);

/*
For chip that include support for hardware security domains.
*/
void security_domain_switch(WORD domain_id);

/*
A fence that ensure that modified data are reflected in the fetched instructions
*/
void instructions_fence(void);

/*
   Set the chip state before the trojan transmission.
*/
void prepare_trojan(void);

/*
   Set the chip state before the spy attempt at reading a value.
*/
void prepare_spy(void);

/*
   The trojan sends the [input] value.
*/
void trojan (WORD input);

/*
   The spy return the timing required to read the [output] value.
*/
TIMECOUNT spy(WORD output);

// /*
//    Read the timer value.
// */
// volatile inline unsigned int read_time(void);// __attribute__((always_inline));


WORD get_input_symbols_count();
WORD get_output_symbols_count();



#endif /* SUPPORT_H */

/*
   Local Variables:
   mode: C
   c-file-style: "gnu"
   End:
*/
