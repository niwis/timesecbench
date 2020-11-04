/*
 * File: main.c
 * Project: support
 * Created Date: Wednesday November 4th 2020
 * Author: Embench
 * -----
 * Last Modified: Wednesday, 4th November 2020 5:01:53 pm
 * Modified By: Ronan (ronan.lashermes@inria.fr>)
 * -----
 * Copyright (c) 2020 INRIA
 */


#include "support.h"

//INPUT_SYMBOLS and OUTPUT_SYMBOLS must be defined in a benchmark file (both unsigned integers).

void benchmark() {
   for(unsigned int o = 0; o < OUTPUT_SYMBOLS; o++) {
      for(unsigned int i = 0; i < INPUT_SYMBOLS; i++) {
         prepare_trojan();
         trojan(i);

         prepare_spy();
         unsigned int t = spy(o);

         transmit(i, o, t);
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
  
   return 0;
}				/* main () */


/*
   Local Variables:
   mode: C
   c-file-style: "gnu"
   End:
*/
