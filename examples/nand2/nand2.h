#include <systemc.h>
#include <math.h>

SC_MODULE(nand2) {
    sc_in<bool> A,B;
    sc_out<bool> F;

    void do_nand() {
        F = !(A&B);
    }

    SC_CTOR(nand2) {
        SC_METHOD(do_nand);      // do_nand为进程， method用来描述组合逻辑不能包含无限循环和wait
        sensitive<<A<<B;         // do nand进程敏感列表
    }
};