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
};
