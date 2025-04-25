#include "Channel.h"

const int Channel::Knonevent = 0;
//|（按位或操作符）: 用于组合多个事件标志，使得文件描述符可以同时监听多个事件。
//按位与操作符 (&) 在这种情况下是不合适的，因为它用于检查两个标志是否同时存在
//文件描述符既可以监听普通可读数据事件，也可以监听紧急数据事件。
const int Channel::KReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::KWriteEvent = EPOLLOUT;

Channel::Channel(EventLoop *loop,int fd)
    : loop_(loop)
    , fd_(fd)
    , events_(0)
    , revents_(0)
    , index_(-1)
    ,tied_(false)
{}

Channel::~Channel()
{
}

//防止当channel被手动remove掉，channel还在执行回调操作
void Channel::tie(const std::share_ptr<void> &obj)
{
    //将 obj 所指向的对象赋给 tie_，使得 tie_ 成为一个弱引用。这样做的好处是可以避免循环引用，同时仍然能够检查对象是否已经被销毁
    tie_ = obj;
    //已经绑定到tie_,将tied置为true
    tied_=true;
}
