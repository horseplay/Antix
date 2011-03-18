#ifndef GAME_H_
#define GAME_H_

#include "Game/Team.h"
#include "Game/Puck.h"
#include <list>
#include <vector>
#include <stdint.h>

namespace Game
{
class Robotix
{
public:
    /**
     * All initializatoin of the game happens here.
     * Config options etc...
     */
    void init();
    
    /**
     * Main game loop. All game logic goes here.
     */
    void update();

    /**
     * Dtor. Delete the pucks and teams.
     */
    ~Robotix();

   //Used for iterating over our collections.
    std::list<Puck*>::iterator getFirstPuck();
    std::list<Puck*>::iterator getLastPuck();

    std::list<Team*>::iterator getFirstTeam();
    std::list<Team*>::iterator getLastTeam();

    Robot* getRobotAtIndex(int index);
    std::vector<Robot*>::iterator getFirstRobot();
    std::vector<Robot*>::iterator getLastRobot();

    /**
     * Add a robot to the general population.
     * Used when a team is initialized.
     */
    void addRobotToPop(Robot* robot);

    /**
     * Getters for config options.
     */
    const int& getWindowSize() const;
    const int& getRobOffset() const;
    const float& getWorldSize() const;
    const int& getTeamCount() const;
    const int& getPuckCount() const;
    const float& getRobFOV() const;
    const float& getRobRadius() const;
    const float& getRobSensorRange() const;
    const float& getRobPickupRange() const;
    const float& getHomeRadius() const;
    const int& getRobPop() const;

    /**
     * Setters for config options.
     */
    void setWindowSize(const int& windowSize);
    void setWorldSize(const float& worldSize);
    void setTeamCount(const int& teamCount);
    void setPuckCount(const int& puckCount);
    void setRobFOV(const float& robFOV);
    void setRobRadius(const float& robRadius);
    void setRobSensorRange(const float& robSRange);
    void setRobPickupRange(const float& robPRange);
    void setHomeRadius(const float& homeRadius);
    void setRobPop(const int& robPop);
    void setRobOffset(const int& team);

    /**
     * Singleton instance that allows access anywhere Game.h is included.
     */
    static Robotix* getInstance();
private:

    /**
     * Instance of our game.
     */
    static Robotix* m_Instance;

    /**
     * List of teams.
     */
    std::list<Team*> m_Teams;
    
    /**
     * List of pucks.
     */
    std::list<Puck*> m_Pucks;

    /**
     * List of all available robots.
     */
    std::vector<Robot*> m_Population;

    //Team the client is processing for.
    static int m_RobotOffset;

    //Total number of teams.
    static int m_TotalTeamCount;

    //Total number of pucks.
    static int m_TotalPuckCount;

    //The max size of our world.
    static float m_WorldSize;
    static uint64_t m_MaxUpdates;
    static uint64_t m_Updates;
    static int m_SleepMsec;

    //Is the game paused.
    static bool m_GamePaused;

    //TODO implement data.
    static bool m_ShowData;

    //Returns the max window size.
    static int m_WindowSize;

};

}
#endif
