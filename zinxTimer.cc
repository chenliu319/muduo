std::list<player*> aoiWorld::getSrdPlayers(player* _player)
{
	std::list<player*> ret;
	
	//玩家所在的网格周围可能是这样   ，圆代表玩家所在的网格，有可能玩家所在的网格在地图边缘，周围没有网格的情况 	
	/*
	■ ■ ■		■ ■ ■
	■ ● ■		■ ■ ■
	■ ■ ■		■ ■ ●
	
	● ■ ■
	■ ■ ■
	■ ■ ■
	*/
	
	//计算当前玩家在哪个网格中,计算出网格编号
	int grid_id = (_player->getX() - x_beg)/.......
	//计算当前玩家所在网格的横坐标和纵坐标
	int x_index = grid_id % x_count;
	int y_index = grid_id / x_count;
	
	//如果当前玩家所在的网格横坐标大于0并且纵坐标也大于0则说明该坐标的左上角坐标存在
	if(x_index > 0 && y_index > 0)
	{
		//说明左上角坐标存在，将左上角坐标从开始到结束的内容拷贝到ret中
		std::list<player*> &cur_list = grids[grid_id - 1 -x_count].m_players;
		ret.insert(ret.begin(),cur_list.begin(),cur_list.end());
	}
	
	//当玩家所在的网格纵坐标大于0说明该坐标上方坐标存在
	if(y_index > 0)
	{
		std::list<player*> &cur_list = grids[grid_id -x_count].m_players;
		ret.insert(ret.begin(),cur_list.begin(),cur_list.end());
	}
	
	//右上角坐标存在需要横坐标小于横坐标最大值（-1是因为坐标是从0开始算的）纵坐标大于0
	if(x_index < x_count - 1 && y_index > 0)
	{
		std::list<player*> &cur_list = grids[grid_id -x_count + 1].m_players;
		ret.insert(ret.begin(),cur_list.begin(),cur_list.end());
	}
	
	//左边的坐标存在需要保证x>0
	if(x_index > 0)
	{
		std::list<player*> &cur_list = grids[grid_id - 1].m_players;
		ret.insert(ret.begin(),cur_list.begin(),cur_list.end());
	}
	
	//将当前玩家所在的格子添加到ret
	std::list<player*> &cur_list = grids[grid_id].m_players;
	ret.insert(ret.begin(),cur_list.begin(),cur_list.end());
	
	//右边格子存在需要x<横坐标最大值
	if(x_index < x_count -1)
	{
		std::list<player*> &cur_list = grids[grid_id +1].m_players;
		ret.insert(ret.begin(),cur_list.begin(),cur_list.end());
	}
	
	//左下角格子存在需要x大于0，y小于纵坐标的最大值
	if(x_index > 0 && y_index < y_count -1)
	{
		std::list<player*> &cur_list = grids[grid_id - 1 +x_count].m_players;
		ret.insert(ret.begin(),cur_list.begin(),cur_list.end());
	}
	
	//下面的格子存在需要y小于纵坐标最大值
	if(y_index < y_count -1)
	{
		std::list<player*> &cur_list = grids[grid_id +x_count].m_players;
		ret.insert(ret.begin(),cur_list.begin(),cur_list.end());
	}
	
	//右下角坐标存在需要x小于横坐标最大值并且y小于纵坐标最大值
	if(x_index < x_count-1&& y_index < y_count - 1)
	{
		std::list<player*> &cur_list = grids[grid_id + 1 +x_count].m_players;
		ret.insert(ret.begin(),cur_list.begin(),cur_list.end());
	}
	
	return ret;
}
