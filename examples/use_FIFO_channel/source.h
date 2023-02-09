#ifndef _SOURCE_H
#define _SOURCE_H

#include <systemc.h>

class source : public sc_module 
{
  public:
  sc_in_clk clk;
  sc_port<sc_fifo_out_if<char> > write_port;    
  // 类sc_port<IF,N>是所有端口的基类，它是一个模板类。
  // IF是接口类型，N是所连接的同一类型的通道数目，也就
  // 是接口数，它的缺省值是1。
  SC_HAS_PROCESS(source);

  source(sc_module_name name) : sc_module(name) {
    SC_CTHREAD(main, clk.neg());
  }

  void main();

};

#endif