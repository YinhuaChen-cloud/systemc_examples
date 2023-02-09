#ifndef _INITIATOR_H
#define _INITIATOR_H

#include "systemc"
using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
// 这个宏在使用TLM-2.0的某些工具时需要定义，比如simple sockets，
// 原因是这些特定的套接字会产生动态processes
#define SC_INCLUDE_DYNAMIC_PROCESSES

// Initiator module generating generic payload transactions
struct Initiator: sc_module
{

  // TLM-2 socket, defaults to 32-bits wide, base protocol
  // TODO: 似乎有除了Base protocol之外的协议?
  // 定义一个简单发起者套接字作为成员变量
  tlm_utils::simple_initiator_socket<Initiator> socket;

  // Internal data buffer used by initiator with generic payload
  int data;

  SC_CTOR(Initiator)
  : socket("socket")  // Construct and name socket
  {
    SC_THREAD(thread_process); // SC_THREAD只在模拟开始的时候执行一次，不过我们可以
    // 在SC_THREAD中写无限循环来让它持续执行
  }

  void thread_process()
  {
    // TLM-2 generic payload transaction, reused across calls to b_transport
    // trans是一个数据结构，用来存放将要传输的payload
    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
    sc_time delay = sc_time(10, SC_NS); // 延迟设定为10ns

    // Generate a random sequence of reads and writes
    for (int i = 32; i < 96; i += 4)
    {

      tlm::tlm_command cmd = static_cast<tlm::tlm_command>(rand() % 2);
      // 这里使用的data是一个结构体内部变量
      if (cmd == tlm::TLM_WRITE_COMMAND) data = 0xFF000000 | i;
      // tlm_command 一共有三种命令：TLM_READ_COMMAND, TLM_WRITE_COMMAND, TLM_IGNORE_COMMAND
      // 使用 rand()%2 来获取 tlm_command，表示仅仅获取 读、写 两种命令

      // Initialize 8 out of the 10 attributes, byte_enable_length and extensions being unused
      trans->set_command( cmd );
      trans->set_address( i );
      trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
      trans->set_data_length( 4 );
      trans->set_streaming_width( 4 ); // = data_length to indicate no streaming
      trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
      trans->set_dmi_allowed( false ); // Mandatory initial value // 强制的初始值
      trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

      // 每个一个delay, 传输一个trans，这个方法调用表示：把trans通过套接字传输
      socket->b_transport( *trans, delay );  // Blocking transport call

      // Initiator obliged to check response status and delay
      // 如果传输过程出现错误，则报错
      if ( trans->is_response_error() )
        SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

      cout << "trans = { " << (cmd ? 'W' : 'R') << ", " << hex << i
           << " } , data = " << hex << data << " at time " << sc_time_stamp()
           << " delay = " << delay << endl;

      // Realize the delay annotated onto the transport call
      // 等待一个delay
      wait(delay);
    }
  }

};

#endif