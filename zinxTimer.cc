

IzinxMsg* TmerOutMsg::InterelHandle(IZinxmsg& _oInput)
{
	//移动刻度
	cur_index++;
	//让刻度取余，防止刻度超过时间片轮转的刻度10
	cur_index %= 10;
	//遍历当前刻度的所有节点，指向处理函数或圈数-1
	/*
	时间片轮转调度经常需要在遍历任务队列时，将已完成或超时的任务从队列中删除。
	范围for循环（auto for）在遍历容器时，不允许在循环体内直接删除当前元素，否则会导致迭代器失效或抛出异常。
	迭代器遍历时，可以安全地在遍历过程中删除当前元素（如it = container.erase(it)），不会导致遍历出错。
	
	范围for循环内部自动维护着一个隐式的迭代器，每次循环结束后会自动++，但如果你在循环体内删除了当前元素，这个隐式迭代器就失效了，下一次++操作会导致未定义行为
	用普通迭代器遍历时可以手动控制迭代器的递增，保证每次删除后都能正确指向下一个元素，避免失效。
	*/
	for(auto it = m_timer_wheel[cur_index].begin();it != m_timer_wheel[cur_index].end();)
	{
		//当前圈数小于或等于0时，调用处理函数
		if((*it)->iCount <=0)
		{
			(*it)->proc();
			//删除当前任务，当容器在删除当前迭代器的时候会返回当前迭代器的下一个迭代器，将下一个迭代器赋值给it，就不会造成使用范围for循环所出现的问题了
			auto ptmp = *it;
			it = m_timer_wheel[cur_index].erase(it);
			//将删除的定时器任务放回时间片轮转中
			AddTask(ptmp);
		}else
		{
			(*it)->iCount--;
			++it;
		}
	}
}
