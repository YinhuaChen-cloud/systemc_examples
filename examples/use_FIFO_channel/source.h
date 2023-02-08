#ifndef _SOURCE_H
#define _SOURCE_H

#include <systemc.h>

class source : public sc_module 
{
  public:
  sc_in_clk clk;
  sc_port<sc_fifo_out_if<char> > write_port;    
  SC_HAS_PROCESS(source);

  source(sc_module_name name) : sc_module(name) {
    SC_CTHREAD(main, clk.neg());
  }

  void main();

};

#endif