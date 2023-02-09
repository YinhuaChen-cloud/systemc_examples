# 关于这个样例

这是SystemC-TLM的一个简单使用案例，使用了simple socket

这里的模型主要分为两个模块，一个内存模块（目标/target）和 一个读写内存的模块（发起者/Initiator）。发起者使用套接字，发送 trans payload 给目标模块，其中包括一个整数指针。目标模块接收到 trans playload 后，首先判断发起者发送的命令是读命令还是写命令，若是读命令，则将内存数据拷贝到整数指针上，若是写命令，则将整数指针指向的数据拷贝到内存上。

---

## 学到的东西

我认为想要理解这个样例，还是必须阅读源码，我已力所能及添加注释。

更多的详细解释可以参考这个网页：https://www.doulos.com/knowhow/systemc/tlm-20/tutorial-1-sockets-generic-payload-blocking-transport/




