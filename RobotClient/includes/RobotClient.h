#ifndef ROBOT_CLIENT_H_ 
#define ROBOT_CLIENT_H_

#include "Client.h"
#include "Messages.h"
#include "Packer.h"
#include <vector>
#include <map>

namespace Network
{

class RobotClient: public Client
{
public:
    RobotClient();
    virtual int handler(int fd);
    int sendRobotRequests();
    int initGrid(const char * host, const char * port);
    int initClock(const char * host, const char * port);
    int packHeaderMessage(unsigned char* buffer, int sender, int message);
    int recvWrapper(TcpConnection* conn, unsigned char* buffer, int msgSize);
    int sendWrapper(TcpConnection* conn, unsigned char* buffer, int msgSize);

private:
	std::vector<int> m_Grids;
    uint16_t m_HeartBeat;
    int m_ClockFd;
    unsigned int m_ReadyGrids;
    
};
}

#endif

