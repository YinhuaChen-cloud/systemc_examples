#include <systemc.h>
#include "tb.h"

int sc_main(int argc, char *argv[]) {
	unsigned size = 16;
	Top top1("top1", size);
	
	cout << "Testbench started, the simulation result is: " << endl;

  sc_start(100000, SC_NS); // 让这次仿真运行10W ns之后停止
	cout << "\n" << endl;
  return 0;
}
