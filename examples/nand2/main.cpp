#include "nand2.h"
#include "tb.h"


int sc_main(int, char**) {
    sc_signal<bool> a,b,f;
    sc_clock clk("Clk", 20, SC_NS);

    nand2 N2("Nand2");  N2.A(a);    N2.B(b);     N2.F(f);

    tb tb1("tb");       tb1.clk(clk);	tb1.a(a);   tb1.b(b);	tb1.f(f);
	



   // trace file creation
    sc_trace_file *tf = sc_create_vcd_trace_file("Nand2");
    sc_trace(tf,N2.A, "A");
    sc_trace(tf,N2.B, "B");
    sc_trace(tf,N2.F, "F");
    sc_trace(tf,tb1.clk, "clk");
    sc_start(200, SC_NS);
    sc_close_vcd_trace_file(tf);
    return 0;
}