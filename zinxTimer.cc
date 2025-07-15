#include "msg.pb.h"

class gameMsg : public UserData{
public:
    gameMsg();
    virtual ~gameMsg();
    //用户的请求信息
    google::protobuf::Message *pMsg = nullptr;
    enum MSG_TYPE
    {
        //玩家上线
        MSG_TYPE_LOGIN_ID_NAME = 1,
        //聊天内容
        MSG_TYPE_CHAT_CONTENT = 2,
        //玩家新位置
        MSG_TYPE_NEW_POSTION = 3,
        //广播
        MSG_TYPE_BROADCAST = 200,
        //玩家下线
        MSG_TYPE_LOGIN_OFF = 201,
        //周围玩家位置
        MSG_TYPE_SRD_POSTION = 202,
    } enMsgType;
	//已知消息内容创建消息对象
	gameMsg(MSG_TYPE _type,google::protobuf::Message* _pMsg);
	//将字节流内容转换成消息结构
	gameMsg(MSG_TYPE _type,std::string _stream);
	
	//序列化消息
	std::string serialize();
};

gameMsg.cc

//已知消息内容创建消息对象
gameMsg::gameMsg(MSG_TYPE _type,google::protobuf::Message* _pMsg)
	:enMsgType(_type)
	,pMsg(_pMsg)
{

}

//将字节流内容转换成消息结构
gameMsg::gameMsg(MSG_TYPE _type,std::string _stream)
{

}


msg.proto
syntax="proto3";
package pb;
//无关选项，用于客户端
option csharp_namespace="Pb";

//消息结构
message syncPid
{
	//玩家id
	int32 pid = 1;
	//玩家姓名
	string username = 2;
}

//玩家信息
message player
{

	int32 pid = 1;
	//玩家坐标
	position p =2;
	string username = 3;
}

message syncPlayers
{
	//嵌套多个子消息类型player的消息，repeated相当于数组
	repeated player ps = 1;
}

//坐标
message position
{
	float x=1;
	float y = 2;
	float z = 3;
	float v = 4;
	//血量
	int32 bloodValue = 5;
}

message movePackege
{
	position p = 1;
	int32 actionData = 2;
}

message broadCast
{
	int32 pid=1;
	int32 tp=2;
	//根据tp不同，broadCast消息会包含：聊天内容（content）或初始位置（p）或新位置p
	//oneof:和union类似，string content = 3;position p =4;int32 actionData=5;三选一
	oneof data
	{
		string content = 3;
		position p =4;
		//actionData暂时预留
		int32 actionData=5;
	}
	string username=6;
}
