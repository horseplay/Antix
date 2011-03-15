#include "GridGame.h"
#include "Robot.h"
#include "Team.h"
#include "Position.h"
#include "GameObject.h"
#include "MathAux.h"


#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <math.h>
using namespace Game;

#define MILLISECS_IN_SECOND 1000
#define AND_OPERATOR 1000

typedef std::pair<int, GameObject*> ObjectIDPair;
typedef std::pair<int, std::vector<sensed_item> > ObjectPair;

GridGame::GridGame()
{

    //Robot configurations.
    robot_FOV = Math::dtor(90.0);
    robot_Radius = 0.01;
    robot_SensorRange = 0.1;
    robot_PickupRange = robot_SensorRange/5.0;

    printf("\n%d\n", robot_FOV);

    //Home radius.
    home_Radius = 0.1;

    m_WorldSize = 10;
	m_NumGrids = 2;
    m_GridId = 1;

    m_PuckTotal = 100;

    m_Population.clear();

    int high_puck_range = (m_PuckTotal/m_NumGrids)*m_GridId;
    int low_puck_range = (m_PuckTotal/m_NumGrids)*(m_GridId-1);
    
    //Generate pucks at random locations.
    for (uint i = low_puck_range; i <= high_puck_range; i++)
    {
       //Get a random location.
       Math::Position* l_PuckPos = Math::Position::randomPosition(m_WorldSize, m_NumGrids, m_GridId);

       //Create the puck.
       Puck* l_Puck = new Puck(l_PuckPos, i);
       m_Population.push_back( l_Puck );
    }

    // Sort generated pucks
    sortPopulation();

    /*
  
    //Generate the teams. 
    for (uint i = 0; i < m_TotalTeamCount; i++)
    {
       Team* l_Team = new Team();
       m_Teams.push_back( l_Team ); 
    }

    if (m_loggingEnabled)
    {
        std::ostringstream s;
        s << "Home=" << m_TotalTeamCount << ", Population=" << Team::m_RobotPopCount;
    }

    */

}

GridGame::~GridGame()
{
    //Note: The delete of the robot population is the responsiblity of the team object.
   
    //Delete the Robots.
    for(std::vector<GameObject*>::iterator it = m_Population.begin(); it != m_Population.end(); it++)
    {
        delete (*it);
    }

}

void GridGame::sortPopulation()
{
    //Sort on the x axis.
    int i;
    GameObject* l_Key;
    for(unsigned int j = 1; j < m_Population.size(); j++)
    {
        l_Key = m_Population[j];
        i = j - 1;
        while(i >= 0 && m_Population[i]->getPosition()->getY() > l_Key->getPosition()->getY())
        {
            m_Population[i+1] =m_Population[i];
            --i;
        }

        m_Population[i+1] = l_Key;
    }
}

/*
void GridGame::sortRobots()
{
    //Sort on the x axis.
    int i;
    Robot* l_Key;
    for(unsigned int j = 1; j < m_Population.size(); j++)
    {
        l_Key = m_Population[j];
        i = j - 1;
        while(i >= 0 && m_Population[i]->getPosition()->getY() > l_Key->getPosition()->getY())
        {
            m_Population[i+1] =m_Population[i];
            m_YRobs[m_Population[i+1]] = i+1;
            --i;
        }

        m_Population[i+1] = l_Key;
        m_YRobs[l_Key] = i+1;
    }
}


void GridGame::sortPucks()
{
    //Sort on the x axis.
    int i;
    Puck* l_Key;
    for(unsigned int j = 1; j < m_Pucks.size(); j++)
    {
        l_Key = m_Pucks[j];
        i = j - 1;
        while(i >= 0 && m_Pucks[i]->getPosition()->getY() > l_Key->getPosition()->getY())
        {
            m_Pucks[i+1] =m_Pucks[i];
            --i;
        }

        m_Pucks[i+1] = l_Key;
    }
}
*/


int GridGame::initializeTeam(std::vector<int> teams, std::vector<robot_info>* robot_info_vector)
{

        //TODO: Will load team_size from the config
        int team_size = 100;
        std::vector<int>::iterator end = teams.end();

        std::vector<robot_info> l_robot_info_vector;

        for(std::vector<int>::iterator it = teams.begin(); it != end; it++){
            // get range of robot ids based on team id and team size
            int firstid = (*it)*team_size;
            int lastid = firstid + team_size - 1;


            for (int i = firstid; i <= lastid; i++)
            {
                Math::Position* l_RobotPosition = Math::Position::randomPosition(m_WorldSize, m_NumGrids, m_GridId);
                Game::Robot* l_Robot = new Robot(l_RobotPosition, i, robot_FOV, robot_Radius, robot_PickupRange, robot_SensorRange);
                addObjectToPop(l_Robot);

                robot_info temp;
                temp.id = i;
                temp.x_pos = l_RobotPosition->getX();
                temp.y_pos = l_RobotPosition->getY();

                l_robot_info_vector.push_back(temp);
            }
        }
        robot_info_vector = &l_robot_info_vector;

        return 1;
}

int GridGame::registerRobot(robot_info robot)
{
    // create a new position object for the new robot
    Math::Position* l_RobotPosition = new Position(robot.x_pos, robot.y_pos, robot.angle);

    // create new robot based on info from robot_info struct
    Game::Robot* l_Robot = new Robot(l_RobotPosition, robot.id, robot_FOV, robot_Radius, robot_PickupRange, robot_SensorRange);
			
    // add robot to the population
    addObjectToPop(l_Robot);

    //TODO: Sort robots at this point?

    return 1;
    
}

int GridGame::unregisterRobot(unsigned int robotid)
{

    int removeResult = removeObjectFromPop(robotid);    


    return removeResult;



}

int GridGame::returnSensorData(std::vector<int> robot_ids_from_client, std::map<int, std::vector<sensed_item> >* sensed_items_map)
{

    std::vector<GameObject*>::iterator populationend = m_Population.end();
    // TODO: Currently returning all items on grid. Will be optimized to only send what is around
    //       its bounding box
    std::vector<sensed_item>  l_sensed_items;
    for(std::vector<GameObject*>::iterator robotit = m_Population.begin(); robotit != populationend; robotit++){
                sensed_item tempsensed;
                tempsensed.id = (**robotit).m_id;
                tempsensed.x = (*robotit)->getX();
                tempsensed.y = (*robotit)->getY();
                l_sensed_items.push_back(tempsensed);
    }
    

    // TODO: Implement with hash key to robot value being index of robot population in vector
    //       that way, we don't have to iterate through the nested forloop to find the robots
    std::map<int, std::vector<sensed_item> > l_sensed_items_map;
  

    std::vector<int>::iterator clientend = robot_ids_from_client.end();

    for(std::vector<int>::iterator it = robot_ids_from_client.begin(); it != clientend; it++)
    {


        for(std::vector<GameObject*>::iterator robotit = m_Population.begin(); robotit != populationend; robotit++)
            if ( (**robotit).m_id == (*it)  )
            {
                //l_sensed_items_map.insert(RobotPair( (**robotit).m_id , l_sensed_items ));
            }
    }

    sensed_items_map = &l_sensed_items_map;


    return 1;

}



int GridGame::addObjectToPop(GameObject* object)
{

    this->m_MapPopulation.insert( ObjectIDPair((*object).m_id, object) );

    this->m_Population.push_back(object);

    this->m_YObjects[object] = m_Population.size();
    
    //TODO: Sort robots at this point?
    
    sortPopulation();

    return 0;
}

int GridGame::removeObjectFromPop(GameObject* object)
{

    int returnval = removeObjectFromPop((*object).m_id);

    return returnval;

}

int GridGame::removeObjectFromPop(int objectid)
{

    GameObject* obj = (m_MapPopulation.find(objectid))->second;

    m_MapPopulation.erase( objectid );

    m_YObjects.erase( obj );
    
    std::vector<GameObject*>::iterator end = m_Population.end();
   
    for(std::vector<GameObject*>::iterator it = m_Population.begin(); it != end; it++)
    {
        if ((**it).m_id == objectid){
            printf("Found %d robot!", objectid);
            this->m_Population.erase(it);
            break;
        }

    }

    /*
    for(std::vector<Robot*>::iterator it = m_Population.begin(); it != end; it++)
    {
        if ((**it).m_id == (*robotobj).m_id){
            printf("Found %d robot!", robotid);
            this->m_Population.erase(it);
            break;
        }

    }*/

    return 0;

}

const float& GridGame::getWorldSize() const
{
    return m_WorldSize;
}

void GridGame::printPopulation(){

	for (int i = 0; i < m_Population.size(); i++){
		
		m_Population[i]->printInfo();

	}
}

int readId(unsigned int id)
{
    int value = id & AND_OPERATOR;


}

