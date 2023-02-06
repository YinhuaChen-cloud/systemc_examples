#include <systemc.h>
#include "hello.h"

SC_MODULE(SYSTEM) {
  // Module declarations
  hello *hello0;
  // Local signal declarations

	// rst and clock signals

  SC_CTOR(SYSTEM) {
    // Module instance signal connections
    hello0 = new hello("hello0");
  }
  ~SYSTEM() {
    // Destructor
    delete hello0;
  }
};

// 以上代码仅仅只是定义了顶层模块，我们还需要定义执行入口
// C++的函数入口是main，SystemC中，则是sc_main
SYSTEM *top = NULL;

int sc_main(int argc, char *argv[]) {
  top = new SYSTEM("top");
  sc_start();
  return 0;
}

