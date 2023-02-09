#ifndef _TB_H
#define _TB_H

#include "systemc"

#include "Initiator.h" // 发起者模块
#include "Memory.h" // 目标模块

SC_MODULE(Top)
{
  Initiator *initiator;
  Memory    *memory;

  SC_CTOR(Top)
  {
    // Instantiate components
    initiator = new Initiator("initiator");
    memory    = new Memory   ("memory");

    // One initiator is bound directly to one target with no intervening bus

    // Bind initiator socket to target socket 把发起者套接字绑定到目标套接字上
    initiator->socket.bind( memory->socket );
  }
};

#endif