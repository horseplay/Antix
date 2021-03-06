#ifndef SPEED_H_
#define SPEED_H_

namespace Math
{
class Speed 
{
public:
    /**
     * Initialize with 0.0 forward and rotational velocity.
     */
    Speed();

    Speed(const float fwSpeed, const float rotSpeed);

    /**
     * Set rotational velocity to 'rot'.
     */
    void setRotSpeed(const float& rot);

    /**
     * Set forward velocity to 'forw'.
     */
    void setForwSpeed(const float& forw); 

    /**
     * Return the forward velocity.
     */
    const float& getForwSpeed() const;

    /**
     * Return the rotational velocity.
     */
    const float& getRotSpeed() const;
private:

    /**
     * Forward velocity of the object.
     */
    float m_ForwSpeed;

    /**
     * Rotational velocity of the object.
     */
    float m_RotSpeed;
};
}

#endif
