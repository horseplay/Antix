#include "RobotClient.h"
#include "Messages.h"
#include <string.h>
#include "Config.h"
#include <map>
#include <vector>

#ifdef DEBUG
#include <time.h>
#endif

using namespace Network;

#ifdef DEBUG
static time_t init_sec = time(NULL);
static int Timesteps = 0;
#endif

RobotClient::RobotClient():Client()
{
}

int RobotClient::sendWrapper(TcpConnection * conn, unsigned char* buffer, int msgSize)
{
    if (conn->send(buffer, msgSize) == -1)
    {
        DEBUGPRINT("Failed to send a message.\n");
        return -1;
    }
    return 0;
}

int RobotClient::recvWrapper(TcpConnection* conn, unsigned char* buffer, int msgSize)
{
    if (conn->recv(buffer, msgSize) == -1)
    {
        DEBUGPRINT("Failed to receive a message.\n");
        return -1;
    }
    return 0;
}

int RobotClient::packHeaderMessage(unsigned char* buffer, int sender, int message)
{
    Msg_header l_Header;

    l_Header.sender = sender;
    l_Header.message = message;

    if (pack(buffer, Msg_header_format, l_Header.sender, l_Header.message) != l_Header.size)
    {
        DEBUGPRINT("Failed to pack a header message. Sender: %d, Message: %d", sender, message);
        return -1;
    }
    return 0;
}

int RobotClient::sendRobotRequests()
{
    //Create our request messages
    Msg_RequestSensorData l_Req;
    Msg_header l_Header;
    Msg_RequestMsgSize l_Size;

    //For each grid, send a message request containing all of the robot ids for that grid.
    std::vector<int>::const_iterator l_GridEnd = m_Grids.end();
    for (std::vector<int>::const_iterator it = m_Grids.begin(); it != l_GridEnd; it++)
    {
        // vector<int> l_RobotIds;
        // requestSensorData((*it), &l_RobotIds);
        
        l_Size.msgSize = 10;//REPLACE WITH ACTUAL REQUEST FOR ROBOTS(l_RobotIds.size())

        unsigned int l_MessageSize = (l_Size.msgSize*l_Req.size)+l_Header.size+l_Size.size;
        unsigned char l_Buffer[l_MessageSize];

        //Keep track of where in the buffer we are packing into.
        unsigned int l_CurrBuffIndex = 0; 

        //Add our header.
        packHeaderMessage(l_Buffer+l_CurrBuffIndex, SENDER_CLIENT, MSG_REQUESTSENSORDATA);        
        l_CurrBuffIndex += l_Header.size;

        //Add the number of elements we are sending
        pack(l_Buffer+l_CurrBuffIndex, Msg_RequestMsgSize_format, l_Size.msgSize);
        l_CurrBuffIndex += l_Size.size;
               
        for (int i = 0; i < l_Size.msgSize;i++)
        {
            l_Req.id = 1234; //REPLACE WITH ACTUAL ROBOT ID l_Req.id = l_RobotIds[i];
            if (pack(l_Buffer+l_CurrBuffIndex, Msg_RequestSensorData_format, l_Req.id) != l_Req.size)
            {
                DEBUGPRINT("Error packing sensor request into the buffer\n");
                return -1;
            }
            l_CurrBuffIndex += l_Req.size;
        }
        
        sendWrapper(m_serverList[(*it)], l_Buffer, l_MessageSize);
    } 
    return 0;
}

int RobotClient::initGrid(const char* host, const char* port)
{
    int l_GridFd = initConnection(host, port);

    if (l_GridFd < 0)
    {
        DEBUGPRINT("Failed creating connection to a grid server\n");
    }
    m_Grids.push_back(l_GridFd);

    return l_GridFd;
}

int RobotClient::initClock(const char* host, const char* port)
{
    int l_ClockFd = initConnection(host, port);

    if (l_ClockFd < 0)
    {
        DEBUGPRINT("Failed creating connection to a grid server\n");
    }
    m_ClockFd = l_ClockFd;

    return l_ClockFd;
}

int RobotClient::handler(int fd)
{
	DEBUGPRINT("Handling file descriptor: %i\n", fd);

    //Create a 'header' message and buffer to receive into.
    Msg_header l_Header;
    unsigned char l_HeaderBuffer[l_Header.size];

    //Get our TCPConnection for this socket.
    TcpConnection *l_Conn =  m_serverList[fd];
        
    //Receive the header message.
    recvWrapper(l_Conn, l_HeaderBuffer, l_Header.size);

    //Unpack the buffer into the 'header' message.
    unpack(l_HeaderBuffer, Msg_header_format, &l_Header.sender, &l_Header.message); 
    DEBUGPRINT("Received message %d from %d\n", l_Header.message, l_Header.sender);
    switch(l_Header.sender)
    {
        //Message is from clock.
        case(SENDER_CLOCK):
            switch(l_Header.message)
            {
                //Message is heart beat.
                case(MSG_HEARTBEAT) :
                {
#ifdef DEBUG
                    time_t curr_sec = time(NULL); 
                    if (curr_sec > init_sec)
                    {
                        DEBUGPRINT("Number of timesteps: %d", Timesteps);
                        init_sec = time(NULL);
                        Timesteps = 0;
                   }
                   Timesteps++;
#endif
                   DEBUGPRINT("Expecting to receive a heartbeat message from the clock.\n");
                   
                   //Create a heartbeat message and buffer to receive into.
                   Msg_HB l_HB;
                   unsigned char l_hbBuffer[l_HB.size]; 
                  
                   //Receive the heartbeat.
                   recvWrapper(l_Conn, l_hbBuffer, l_HB.size); 

                   //Unpack heartbeat message from our buffer.
                   unpack(l_hbBuffer, Msg_HB_format, &l_HB.hb);
                   DEBUGPRINT("Hearbeat character: %hd\n", l_HB.hb);
                    
                   m_HeartBeat = l_HB.hb; 
                   if (sendRobotRequests() != 0)
                   {
                       DEBUGPRINT("Error sending robot sensor requests\n");
                   }
               }
            }
            break;
        case(SENDER_GRIDSERVER):
            switch(l_Header.message)
            {
                case(MSG_ROBOTSENSORDATA) :
                {
                    
                    std::map<int, std::vector<Msg_sensedObjectGroupItem> > l_SensedInfo;

                    //Receive the total number of robots we are getting sens info for.
                    Msg_RequestMsgSize l_NumRobots;
                    unsigned char l_NumRobBuffer[l_NumRobots.size];

                    recvWrapper(l_Conn, l_NumRobBuffer, l_NumRobots.size);
                    unpack(l_NumRobBuffer, Msg_RequestMsgSize_format, &l_NumRobots.msgSize);

                    //Go through all of the robots we expect info for.
                    for (int i = 0; i < l_NumRobots.msgSize;i++)
                    {
                        //First get the header telling us how many objects are sensed and for which object.
                        Msg_sensedObjectGroupHeader l_RoboHeader;
                        unsigned char l_GroupHeaderBuff[l_RoboHeader.size];

                        recvWrapper(l_Conn, l_GroupHeaderBuff, l_RoboHeader.size);
                        unpack(l_GroupHeaderBuff, Msg_sensedObjectGroupHeader_format,
                                &l_RoboHeader.id, &l_RoboHeader.objectCount);
                        
                        std::vector<Msg_sensedObjectGroupItem> &l_Info = l_SensedInfo[l_RoboHeader.id];
                        //Receive all of our sensed items.
                        for (int a = 0; a < l_RoboHeader.objectCount; a++)
                        {
                            
                           //Receive a sensed item.
                           Msg_sensedObjectGroupItem l_SensedItem;
                           unsigned char l_SensedItemBuffer[l_SensedItem.size]; 
                            
                           //Receive and insert into our map of sensed items.
                           recvWrapper(l_Conn, l_SensedItemBuffer, l_SensedItem.size);
                           unpack(l_SensedItemBuffer, Msg_sensedObjectGroupItem_format, &l_SensedItem.robotid,
                                   &l_SensedItem.x, &l_SensedItem.y);
                           l_Info.push_back(l_SensedItem);
                        }
                    }
                    //recieveSensorData(&l_SensedInfo);

                    m_ReadyGrids++; 
                    DEBUGPRINT("Recevied sensory data from a grid\n");
                    if (m_ReadyGrids == m_Grids.size())
                    {   
                        TcpConnection* l_ClockConn = m_serverList[m_ClockFd];
                        //Prepare our 'header' message.
                        Msg_header l_Header;
                        Msg_HB l_HB = {m_HeartBeat};

                        unsigned int l_MessageSize = l_Header.size+l_HB.size;
                        unsigned char l_HBBuffer[l_MessageSize];
                        packHeaderMessage(l_HBBuffer, SENDER_CLIENT, MSG_HEARTBEAT);
                        
                        //Pack the hearbeat into the header message buffer.
                        if (pack(l_HBBuffer+l_Header.size, Msg_HB_format, l_HB.hb) != l_HB.size)
                        {
                            DEBUGPRINT("Failed to pack the HB message\n");
                            return -1;
                        }
                        sendWrapper(l_ClockConn, l_HBBuffer, l_MessageSize);

                        m_ReadyGrids = 0;
                    }
                     
                }
            }
            break;
    }


    return 0;
}

