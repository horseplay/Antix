#ifndef CLIENT_H
#define CLIENT_H

#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include "TcpConnection.h"

namespace Network
{
	
	class client
	{
	public:
		client();
		int init(char * host, char * port);
		~client();
		
		virtual int handler() = 0;
		
	private:
		char m_host[INET6_ADDRSTRLEN];
		char m_port[MAX_PORT_LENGTH];
		struct addrinfo m_info;
		TcpConnection m_conn;
	};

}

#endif