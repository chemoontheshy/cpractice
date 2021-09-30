#pragma once

#include <string>
#include <string.h>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include "common/mongoose.h"

namespace vsnc
{
    namespace vnet
    {
        //定义http返回callback
        // void --> OnRspCallback
        typedef void OnRspCallback(mg_connection* c, std::string);

        // 定义http请求hander
        using ReqHandler = std::function<bool(std::string, std::string, mg_connection* c, OnRspCallback)>;


        //HttpServer服务器
        class  HttpServer
        {
        public:
            /// <summary>
            /// 构造函数
            /// </summary>
            HttpServer() {};

            /// <summary>
            /// 析构函数
            /// </summary>
            ~HttpServer() {};


            /// <summary>
            /// 初始化设置
            /// </summary>
            /// <param name="port">端口号</param>
            void Init(const std::string& port);

            /// <summary>
            /// 启动http服务器
            /// </summary>
            /// <returns>成功返回true，错误返回false</returns>
            bool Start();

            /// <summary>
            /// 关闭http服务器
            /// </summary>
            /// <returns>成功返回true，错误返回false</returns>
            bool Close();

            /// <summary>
            /// 注册事件
            /// </summary>
            /// <param name="url">API地址</param>
            /// <param name="req_headler">请求</param>
            void AddHandler(const std::string& url, ReqHandler req_headler);

            /// <summary>
            /// 移除事件
            /// </summary>
            /// <param name="url">API地址</param>
            void RemoveHandler(const std::string& url);

            /// <summary>
            /// 网页根目录
            /// </summary>
            static std::string s_web_dir;

            /// <summary>
            /// web服务器选项
            /// </summary>
            static mg_serve_http_opts s_server_option;

            /// <summary>
            /// 回调函数映射表
            /// </summary>
            static std::unordered_map<std::string, ReqHandler> s_handler_map;

        private:

            /// <summary>
            /// 静态事件响应函数
            /// </summary>
            /// <param name="connection">连接</param>
            /// <param name="event_type">事件类型</param>
            /// <param name="event_data">事件数据</param>
            static void OnHttpWebsocketEvent(mg_connection* connection, int event_type, void* event_data);

            /// <summary>
            /// 处理Http事件
            /// </summary>
            /// <param name="connection">连接</param>
            /// <param name="http_req">http消息</param>
            static void HandleHttpEvent(mg_connection* connection, http_message* http_req);

            /// <summary>
            /// 发送Http消息？
            /// </summary>
            /// <param name="connection">连接</param>
            /// <param name="rsp">消息</param>
            static void SendHttpRsp(mg_connection* connection, std::string rsp);

            /// <summary>
            /// 判断是否websocket类型连接
            /// </summary>
            /// <param name="connection">连接</param>
            /// <returns></returns>
            static int IsWebsocket(const mg_connection* connection);

            /// <summary>
            /// 处理连接间的消息
            /// </summary>
            /// <param name="connection">连接</param>
            /// <param name="event_type">事件类型</param>
            /// <param name="ws_mgs">消息内容</param>
            static void HandleWebsocketMessage(mg_connection* connection, int event_type, websocket_message* ws_msg);

            /// <summary>
            /// 发送消息到指定连接
            /// </summary>
            /// <param name="connection">指定连接</param>
            /// <param name="msg">消息内容</param>
            static void SendWebsocketMsg(mg_connection* connection, std::string msg);

            /// <summary>
            /// 给所有连接广播消息
            /// </summary>
            /// <param name="msg">广播消息内容</param>
            static void BroadcastWebsocketMsg(std::string msg);

            /// <summary>缓存websocket连接</summary>
            static std::unordered_set<mg_connection*> s_websocket_session_set;

            /// <summary>端口</summary>
            std::string m_port;

            /// <summary>连接管理器</summary>
            mg_mgr m_mgr;

        };

    }
}