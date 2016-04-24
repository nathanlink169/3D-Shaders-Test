#ifndef __ContactListener_H__
#define __ContactListener_H__

#include <Box2D\Box2D.h>

class ContactListener : public b2ContactListener
{
public:
    // Called when two fixtures begin to touch
    virtual void BeginContact(b2Contact* contact);

    // Called when two fixtures cease to touch
    virtual void EndContact(b2Contact* contact);
};

#endif