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
