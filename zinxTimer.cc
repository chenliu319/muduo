gameProtocol.h
class gameChannel;
class gameProtocol : public Iprotocol
{
...
public:
	gameChannel* m_channel = NULL;
}

gameProtocol.cc
#include "gameChannel.h"

gameChannel.cc
CreateTcpDataChannel(int _fd)
{
...
//绑定协议对象,双向绑定,通道层能访问到协议层，协议层能访问通道层
pProtocol->m_channel = pChannel;
}


//参数来自业务层，是待发送的消息，返回值是转换后的原始数据
response2raw(UserData& _oUserData)
{
	//消息内容长度
	int iLength = 0;
	//消息id
	int id = 0;
	//消息的具体内容
	std::string msgContent;
	
	GET_REF2DATA(gameMsg,oOutPut,_oUserData);
	id = oOutPut.enMsgType;
	msgContent = oOutPut.serialize();
	iLength = msgContent.size();
	
	auto pret = new std::string();
	/*
		为什么右移后与0xff进行&就能得到对应的字节
		假设有一个int类型的变量 iLength，它在内存中占4个字节（32位）iLength = 0x12345678,它的二进制表示是：00010010 00110100 01010110 01111000（高位在左，低位在右）
		右移操作 iLength >> n，会把所有位向右移动n位。例如：
		iLength >> 0 不变，还是原始值
		iLength >> 8 所有位右移8位，原来的第2个字节变成最低字节
		iLength >> 16 所有位右移16位，原来的第3个字节变成最低字节
		iLength >> 24 所有位右移24位，原来的第4个字节变成最低字节
		
		与0xff进行按位与（&）,0xff 的二进制是 11111111，也就是只保留最低8位，其余全部清零
		(iLength >> n) & 0xff 的作用就是：把右移n位后的最低8位保留下来，其余全部清零。
	*/
	//前4字节是int型，且是从低位到高位
	//第1个字节就是长度的最低位,取出最低8位（第1个字节）放入pret第0个位置
	pret.push_back((iLength >> 0) & 0xff);
	//取出第2个字节放入pret第1个位置
	pret.push_back((iLength >> 8) & 0xff);
	//取出第3个字节放入pret第2个位置
	pret.push_back((iLength >> 16) & 0xff);
	//取出最高字节（第4个字节）放入pret第3个位置
	pret.push_back((iLength >> 24) & 0xff);
	
	//继续将id也拼进pret
	pret.push_back((id >> 0) & 0xff);
	pret.push_back((id >> 8) & 0xff);
	pret.push_back((id >> 16) & 0xff);
	pret.push_back((id >> 24) & 0xff);
	
	//将后续的消息内容拼接到pret中
	pret->append(msgContent);
	
	return pret;
}

//返回数据发送的通道，也就是指定使用哪个通道来发送
GetMsgSender(BytesMsg& _oByte)
{
	return m_channel;
}
