#ifndef _TB_H
#define _TB_H

#include <systemc.h>

SC_MODULE(tb) {
    sc_out<bool> a,b;
    sc_in<bool> f;
    sc_in_clk clk;
    
void gen_input() {
    wait(); a=0; b=0;	  //wait 推进仿真时间， 和always差不多，wait()就是等待敏感列表上的时间，不管是哪个；wait(pos.posedge_event())等待上升沿事件
	wait(); a=0; b=1;     	  
    wait(); a=1; b=0;     	  
	wait(); a=1; b=1;	  
	wait(); a=0; b=0;	 	
	wait(); a=0; b=0;	 	
}

	void display_variable(){
		cout<<"a="<<a<<",b="<<b<<",f="<<f<<endl;
	} 

    SC_CTOR(tb) {
        SC_CTHREAD(gen_input, clk.pos()); 
        SC_METHOD(display_variable);  // 时钟上升或下降沿触发，时钟精确建模
        sensitive<<f<<a<<b;
        dont_initialize();
    }
};


#endif