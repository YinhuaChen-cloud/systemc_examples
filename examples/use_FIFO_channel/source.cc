#include "source.h"

void source::main() {
  int i = 0; 
  const char str [] = "For any problems,feel free to contact the author via Email:chenxiee @mails.tsinghua.edu.cn!\n";      
 
  wait(); 
  while (true){  
    if (rand() & 1) { 
      if (str[i]) {
        write_port->write(str[i++]); // 每个周期发送一个字符
      } 
    }
    wait();
  } 
}
