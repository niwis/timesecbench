/*
 * File: support.h
 * Project: support
 * Created Date: Wednesday November 4th 2020
 * Author: Embench
 * -----
 * Last Modified: Friday, 6th November 2020 10:33:22 am
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */

#ifndef SUPPORT_H
#define SUPPORT_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

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
void transmit(unsigned int input, unsigned int output, unsigned int timing);

/*
Call this function to denote the end of the benchmark (required since the number of transmit() call is variable).
*/
void end_benchmark(void);


void security_domain_switch(unsigned int domain_id);

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
void trojan (unsigned int input);

/*
   The spy return the timing required to read the [output] value.
*/
unsigned int spy(unsigned int output);

// /*
//    Read the timer value.
// */
// volatile inline unsigned int read_time(void);// __attribute__((always_inline));


unsigned int get_input_symbols_count();
unsigned int get_output_symbols_count();

#endif /* SUPPORT_H */

/*
   Local Variables:
   mode: C
   c-file-style: "gnu"
   End:
*/
