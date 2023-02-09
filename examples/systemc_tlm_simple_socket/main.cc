// Filename: tlm2_getting_started_1.cpp

// Getting Started with TLM-2.0, Tutorial Example 1

// For a full description, see http://www.doulos.com/knowhow/systemc/tlm2

// Shows the generic payload, sockets, and blocking transport interface.
// Shows the responsibilities of initiator and target with respect to the generic payload.
// Has only dummy implementations of the direct memory and debug transaction interfaces.
// Does not show the non-blocking transport interface.

#include "tb.h"

int sc_main(int argc, char* argv[])
{
  Top top("top");
  sc_start();
  return 0;
}
