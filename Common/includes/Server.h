#ifndef NETWORK_SERVER_H_
#define NETWORK_SERVER_H_

#include "TcpConnection.h"
#include "fcntl.h"
#include <map>
#include "sys/epoll.h"

namespace Network
{

typedef std::map<int, TcpConnection*> TcpMap;

class Server
{
public:
    Server();
    virtual int handler(int fd) = 0;
	virtual int handleNewConnection(int fd) = 0;
	virtual int allConnectionReadyHandler() = 0;
	virtual int initConnection(const char * host, const char * port);
    virtual int init(const char* port, int maxConnections=-1);
	int start();
	
private:
	int modifyHandler(int fd, unsigned int events);
	int addHandler(int fd, unsigned int events, TcpConnection * connection);
	int setnonblock(int fd);
    int handle_epoll(int epfd, int op, int fd, epoll_event* event);

	int m_epfd; // epoll file descriptor
	
    char m_Port[MAX_PORT_LENGTH];
protected:
    TcpConnection m_ServerConn;
    TcpMap m_Clients;
	bool m_ready;
	int m_servers_total;
	int m_servers_connected;
};

}


#endif
