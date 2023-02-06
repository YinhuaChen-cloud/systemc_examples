#ifndef _HELLO_H
#define _HELLO_H

#include "systemc.h"

SC_MODULE(hello) {

	SC_CTOR(hello) {
		cout << "Hello, SystemC!" << endl;
		cout << "sc version: " << sc_version() << endl;
		cout << "sc copyright: " << sc_copyright() << endl;
		cout << "sc timestamp: " << sc_time_stamp() << endl;
		cout << "sc_get_time_resolution(): " << sc_get_time_resolution() << endl;
		// cout << "sc_get_default_time_unit(): " << sc_get_default_time_unit() << endl;
		// sc_get_default_time_unit 已经被废弃
		// 参考这个网址：
		// https://forums.accellera.org/topic/1528-what-is-default-time-unit-in-systemc/
		// 可知目前SystemC已经没有默认时间单位，我们应该总是明确时间单位
		// 例如：wait(1, SC_NS);
	}

};

#endif

