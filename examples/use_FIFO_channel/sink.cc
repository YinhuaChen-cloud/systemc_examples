#include "sink.h"

void sink::main() {
  char c; 
  while (true) {
    if (rand() & 1) {
      read_port->read(c);
      cout << c;
    }

    wait();

  }
}
