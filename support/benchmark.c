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
