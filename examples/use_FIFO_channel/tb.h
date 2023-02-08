#ifndef _TB_H
#define _TB_H

#include "source.h"
#include "sink.h"
#define PERIOD 20

class Top: public sc_module {

	public:
	sc_clock clk;
	sc_fifo<char> fifo1;
	source source1;
	sink sink1;    

	Top(sc_module_name name, int size): 
	sc_module(name), 
	fifo1("FIFO1", size), 
	source1("source1"),
	sink1("sink1"),
	clk("Clk", PERIOD, SC_NS)
	{
		cout << "Hello, SystemC!" << endl;
		source1.write_port(fifo1);        
		source1.clk(clk);
		sink1.read_port(fifo1);
		sink1.clk(clk);
		cout << "Goodbye, SystemC!" << endl;
	}

};

#endif

