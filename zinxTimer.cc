while(1)
{
	....
	//位操作
	//为什么使用位操作而不使用复制或赋值，因为这里是小端字节序，低位在低位，高位在高位，有些机器默认是大端字节序，会导致低位在高位，高位在低位导致乱序
	//数据内容要求的长度
	//把4个字节拼成一个32位整数
	int iLength = 0;
	//由于szLast位是由低到高，所以szLast[0]表示最低位，左移0位（即不变），然后用按位或（|=）赋值给 iLength。第一个字节放在最低的8位（int整数的第一个字节）。
	iLength |= szLast[0] << 0;
	//取 szlast[1] 这个字节，左移8位（相当于乘以256），放到 iLength 的第8~15位（int整数的第二个字节）。
	iLength |= szLast[1] << 8;
	//取 szlast[2] 这个字节，左移16位，放到 iLength 的第16~23位（int整数的第三个字节）。
	iLength |= szLast[2] << 16;
	//取 szlast[3] 这个字节，左移24位，放到 iLength 的第24~31位（int整数的第四个字节）。
	iLength |= szLast[3] << 24;

	//数据id
	int id = 0;
	id |= szLast[4] << 0;
	id |= szLast[5] << 8;
	id |= szLast[5] << 16;
	id |= szLast[7] << 24;

	//通过读到的长度判断后续的报文是否合法,szLast.size() - 8:接收到的数据内容的长度
	//如果后续报文的长度小于规定的数据内容长度，说明发生了粘包且收到的数据内容长度小于实际的数据内容要求的长度
	if((szLast.size() - 8) < iLength)
	{
		//本条接收到的报文长度不够，啥都不干继续接收后续传来的报文
		return pRet;
	}
	
	//后续接收到的报文没有发生粘包或者发生了粘包但是接收到的数据内容长度大于实际的数据内容要求的长度
	//构造一条用户请求,szLast.substr(8,iLength)表示将收到的报文从第8位开始截取，一直截取到实际的数据内容要求的长度，这就是一条不粘包的完整报文
	gameMsg* pMsg = new gameMsg(id,szLast.substr(8,iLength));
	//如果收到的报文长度大于实际报文长度,弹出已经处理成功的报文，剩下的就是多余的报文
	szLast = szLast.substr(8+iLength,szLast.size() - 8 -iLength);
}

