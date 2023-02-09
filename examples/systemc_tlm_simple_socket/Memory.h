#ifndef _MEMORY_H
#define _MEMORY_H

#include "systemc"
using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
// 这个宏在使用TLM-2.0的某些工具时需要定义，比如simple sockets，
// 原因是这些特定的套接字会产生动态processes
#define SC_INCLUDE_DYNAMIC_PROCESSES

// Target module representing a simple memory
struct Memory: sc_module
{
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_target_socket<Memory> socket;

  enum { SIZE = 256 };

  int mem[SIZE];

  SC_CTOR(Memory)
  : socket("socket")
  {
    // Register callback for incoming b_transport interface method call
    // 目标类需要在构造函数内为自己的目标套接字注册b_trasport函数
    // 意思是：当发起者套接字调用b_transport时，目标模块要采取的行为逻辑
    socket.register_b_transport(this, &Memory::b_transport);

    // Initialize memory with random data
    for (int i = 0; i < SIZE; i++)
      mem[i] = 0xAA000000 | (rand() % 256); // 这里的mem是一个结构体内部变量，定义在后面
  }

  // TLM-2 blocking transport method
  virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& delay )
  {
    // 把发起者套接字发送过来的trans给接收、解析。
    tlm::tlm_command cmd = trans.get_command();
    sc_dt::uint64    adr = trans.get_address() / 4;
    unsigned char*   ptr = trans.get_data_ptr();
    unsigned int     len = trans.get_data_length();
    unsigned char*   byt = trans.get_byte_enable_ptr();
    unsigned int     wid = trans.get_streaming_width();

    // Obliged to check address range and check for unsupported features,
    //   i.e. byte enables, streaming, and bursts
    // Can ignore DMI hint and extensions
    // Using the SystemC report handler is an acceptable way of signalling an error

    if (adr >= sc_dt::uint64(SIZE) || byt != 0 || len > 4 || wid < len)
      SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");

    // Obliged to implement read and write commands
    if ( cmd == tlm::TLM_READ_COMMAND )
      memcpy(ptr, &mem[adr], len); // 如果是读命令，把内存中的数据拷贝到ptr指针上
    else if ( cmd == tlm::TLM_WRITE_COMMAND )
      memcpy(&mem[adr], ptr, len); // 如果是写命令，把ptr指针上的数据拷贝到内存上

    // Obliged to set response status to indicate successful completion
    trans.set_response_status( tlm::TLM_OK_RESPONSE );
  }

};

#endif