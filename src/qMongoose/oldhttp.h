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
        //����http����callback
        // void --> OnRspCallback
        typedef void OnRspCallback(mg_connection* c, std::string);

        // ����http����hander
        using ReqHandler = std::function<bool(std::string, std::string, mg_connection* c, OnRspCallback)>;


        //HttpServer������
        class  HttpServer
        {
        public:
            /// <summary>
            /// ���캯��
            /// </summary>
            HttpServer() {};

            /// <summary>
            /// ��������
            /// </summary>
            ~HttpServer() {};


            /// <summary>
            /// ��ʼ������
            /// </summary>
            /// <param name="port">�˿ں�</param>
            void Init(const std::string& port);

            /// <summary>
            /// ����http������
            /// </summary>
            /// <returns>�ɹ�����true�����󷵻�false</returns>
            bool Start();

            /// <summary>
            /// �ر�http������
            /// </summary>
            /// <returns>�ɹ�����true�����󷵻�false</returns>
            bool Close();

            /// <summary>
            /// ע���¼�
            /// </summary>
            /// <param name="url">API��ַ</param>
            /// <param name="req_headler">����</param>
            void AddHandler(const std::string& url, ReqHandler req_headler);

            /// <summary>
            /// �Ƴ��¼�
            /// </summary>
            /// <param name="url">API��ַ</param>
            void RemoveHandler(const std::string& url);

            /// <summary>
            /// ��ҳ��Ŀ¼
            /// </summary>
            static std::string s_web_dir;

            /// <summary>
            /// web������ѡ��
            /// </summary>
            static mg_serve_http_opts s_server_option;

            /// <summary>
            /// �ص�����ӳ���
            /// </summary>
            static std::unordered_map<std::string, ReqHandler> s_handler_map;

        private:

            /// <summary>
            /// ��̬�¼���Ӧ����
            /// </summary>
            /// <param name="connection">����</param>
            /// <param name="event_type">�¼�����</param>
            /// <param name="event_data">�¼�����</param>
            static void OnHttpWebsocketEvent(mg_connection* connection, int event_type, void* event_data);

            /// <summary>
            /// ����Http�¼�
            /// </summary>
            /// <param name="connection">����</param>
            /// <param name="http_req">http��Ϣ</param>
            static void HandleHttpEvent(mg_connection* connection, http_message* http_req);

            /// <summary>
            /// ����Http��Ϣ��
            /// </summary>
            /// <param name="connection">����</param>
            /// <param name="rsp">��Ϣ</param>
            static void SendHttpRsp(mg_connection* connection, std::string rsp);

            /// <summary>
            /// �ж��Ƿ�websocket��������
            /// </summary>
            /// <param name="connection">����</param>
            /// <returns></returns>
            static int IsWebsocket(const mg_connection* connection);

            /// <summary>
            /// �������Ӽ����Ϣ
            /// </summary>
            /// <param name="connection">����</param>
            /// <param name="event_type">�¼�����</param>
            /// <param name="ws_mgs">��Ϣ����</param>
            static void HandleWebsocketMessage(mg_connection* connection, int event_type, websocket_message* ws_msg);

            /// <summary>
            /// ������Ϣ��ָ������
            /// </summary>
            /// <param name="connection">ָ������</param>
            /// <param name="msg">��Ϣ����</param>
            static void SendWebsocketMsg(mg_connection* connection, std::string msg);

            /// <summary>
            /// ���������ӹ㲥��Ϣ
            /// </summary>
            /// <param name="msg">�㲥��Ϣ����</param>
            static void BroadcastWebsocketMsg(std::string msg);

            /// <summary>����websocket����</summary>
            static std::unordered_set<mg_connection*> s_websocket_session_set;

            /// <summary>�˿�</summary>
            std::string m_port;

            /// <summary>���ӹ�����</summary>
            mg_mgr m_mgr;

        };

    }
}