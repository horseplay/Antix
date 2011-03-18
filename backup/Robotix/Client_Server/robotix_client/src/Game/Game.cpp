#include "Game/Game.h"
#include "Game/Robot.h"
#include "Game/Team.h"
#include "Math/Position.h"
#include "Math/Math.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

using namespace Game;

//Static initializers.
Robotix* Robotix::m_Instance = NULL;
int Robotix::m_TotalTeamCount = 0;
int Robotix::m_TotalPuckCount = 0;
float Robotix::m_WorldSize = 0.0;
uint64_t Robotix::m_MaxUpdates = 0;
uint64_t Robotix::m_Updates = 0;
int Robotix::m_SleepMsec = 0;
bool Robotix::m_GamePaused = false;
bool Robotix::m_ShowData = false;
int Robotix::m_WindowSize = 0;
int Robotix::m_RobotOffset = 0;

void Robotix::init()
{
    //Seed our number generator.
    srand48(time(NULL));

    m_GamePaused = false;

    //Graphics details.
    m_ShowData = false;
    
    m_Updates = 0;
    m_MaxUpdates = 0;

    m_SleepMsec = 10; 

    //Generate pucks at random locations.
    for (int i = 0; i <m_TotalPuckCount; i++)
    {
       //Get a random location.
       Math::Position* l_PuckPos = Math::Position::randomPosition(m_WorldSize);

       //Create the puck.
       Puck* l_Puck = new Puck(l_PuckPos);
       m_Pucks.push_back( l_Puck );
    }
  
    //Generate the teams. 
    for (int i = 0; i < m_TotalTeamCount; i++)
    {
       Team* l_Team = new Team();
       m_Teams.push_back( l_Team ); 
    }
}

Robotix::~Robotix()
{
    //Note: The delete of the robot population is the responsiblity of the team object.
   
    //Delete the teams.
    for(std::list<Team*>::iterator it = m_Teams.begin(); it != m_Teams.end(); it++)
    {
        delete (*it);
    }

    //Delete the pucks.
    for(std::list<Puck*>::iterator it = m_Pucks.begin(); it != m_Pucks.end(); it++)
    {
        delete (*it);
    }
}

void Robotix::update()
{
    //If we've set max update, then check if we've done enough updates.
    if (m_MaxUpdates > 0 && m_Updates > m_MaxUpdates)
        exit(1);
    
    //Send the rob positions only for the client's robots.
    int l_TeamPop = Robotix::getInstance()->getRobPop()+Robotix::getInstance()->getRobOffset();
   
    //Main AI loop.
    if (!m_GamePaused)
    { 
         for(int i = Robotix::getInstance()->getRobOffset(); i < l_TeamPop; i++ )
         {
            Robotix::getInstance()->getRobotAtIndex(i)->updatePosition();
         }

        for(int i = Robotix::getInstance()->getRobOffset(); i < l_TeamPop; i++ )
        {
            Robotix::getInstance()->getRobotAtIndex(i)->updateSensors();
        }

        for(int i = Robotix::getInstance()->getRobOffset(); i < l_TeamPop; i++ )
        {
            Robotix::getInstance()->getRobotAtIndex(i)->updateController();
        }
    }

    m_Updates++;

    if ( m_SleepMsec > 0 )
        usleep (m_SleepMsec*1e3);
}

void Robotix::addRobotToPop(Robot* robot)
{
    this->m_Population.push_back(robot);
}

Robotix* Robotix::getInstance()
{
    if (!m_Instance)
    {
        m_Instance = new Robotix();
    }

    return m_Instance;
}

std::list<Puck*>::iterator Robotix::getFirstPuck()
{
    return m_Pucks.begin();
}

std::list<Puck*>::iterator Robotix::getLastPuck()
{
    return m_Pucks.end();
}

std::list<Team*>::iterator Robotix::getFirstTeam()
{
    return m_Teams.begin();
}

std::list<Team*>::iterator Robotix::getLastTeam()
{
    return m_Teams.end();
}

std::vector<Robot*>::iterator Robotix::getFirstRobot()
{
    return m_Population.begin();
}

std::vector<Robot*>::iterator Robotix::getLastRobot()
{
    return m_Population.end();
}

const int& Robotix::getWindowSize() const
{
    return m_WindowSize;
}

const float& Robotix::getWorldSize() const
{
    return m_WorldSize;
}

const int& Robotix::getTeamCount() const
{
    return m_TotalTeamCount;
}

const int& Robotix::getPuckCount() const
{
    return m_TotalPuckCount;
}

const float& Robotix::getRobFOV() const
{
    return Robot::m_FOV;
}

const float& Robotix::getRobRadius() const
{
    return Robot::m_Radius;
}

const float& Robotix::getRobSensorRange() const
{
    return Robot::m_SensorRange;
}

const float& Robotix::getRobPickupRange() const
{
    return Robot::m_PickupRange;
}

const float& Robotix::getHomeRadius() const
{
    return Home::m_Radius;
}

const int& Robotix::getRobPop() const
{
    return Team::m_RobotPopCount;
}
void Robotix::setWindowSize(const int& windowSize)
{
    m_WindowSize = windowSize;
}
void Robotix::setWorldSize(const float& worldSize)
{
    m_WorldSize = worldSize;
}
    
void Robotix::setTeamCount(const int& teamCount)
{
    m_TotalTeamCount = teamCount;
}
void Robotix::setPuckCount(const int& puckCount)
{
    m_TotalPuckCount = puckCount;
}
void Robotix::setRobFOV(const float& robFOV)
{
    Robot::m_FOV = robFOV;
}
void Robotix::setRobRadius(const float& robRadius)
{
    Robot::m_Radius = robRadius;
}
void Robotix::setRobSensorRange(const float& robSRange)
{
    Robot::m_SensorRange = robSRange;
}
void Robotix::setRobPickupRange(const float& robPRange)
{
    Robot::m_PickupRange = robPRange;
}
void Robotix::setHomeRadius(const float& homeRadius)
{
    Home::m_Radius = homeRadius;
}
void Robotix::setRobPop(const int& robPop)
{
    Team::m_RobotPopCount = robPop;
}
void Robotix::setRobOffset(const int& team)
{
    m_RobotOffset = team;
}

const int& Robotix::getRobOffset() const
{
    return m_RobotOffset;
}

Robot* Robotix::getRobotAtIndex(int index)
{
    return m_Population[index];
}

