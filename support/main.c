/*
 * File: main.c
 * Project: support
 * Created Date: Wednesday November 4th 2020
 * Author: Embench
 * -----
 * Last Modified: Wednesday, 26th May 2021 3:06:31 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */


#include "support.h"

//INPUT_SYMBOLS and OUTPUT_SYMBOLS must be defined in a benchmark file (both unsigned integers).

void benchmark() {

   unsigned int ic = get_input_symbols_count();
   unsigned int oc = get_output_symbols_count();

   for(unsigned int r = 0; r < REPETITION_FACTOR; r++) {
      for(unsigned int o = 0; o < oc; o++) {
         for(unsigned int i = 0; i < ic; i++) {
            prepare_trojan();
            trojan(i);

            prepare_spy();
            unsigned int t = spy(o);

            transmit(i, o, t);
         }
      }
   }
}

int __attribute__ ((used))
main (int argc __attribute__ ((unused)),
      char *argv[] __attribute__ ((unused)))
{
   
   initialise_board ();
   initialise_benchmark ();

   benchmark ();
   end_benchmark();
  
   return 0;
}				/* main () */


/*
   Local Variables:
   mode: C
   c-file-style: "gnu"
   End:
*/
