#include "CommonHeader.h"

void ContactListener::BeginContact(b2Contact* contact)
{
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData)
    {
        static_cast<GameObject*>(bodyUserData)->OnBeginContact(contact);
    }

    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if (bodyUserData)
    {
        static_cast<GameObject*>(bodyUserData)->OnBeginContact(contact);
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData)
    {
        static_cast<GameObject*>(bodyUserData)->OnEndContact(contact);
    }

    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if (bodyUserData)
    {
        static_cast<GameObject*>(bodyUserData)->OnEndContact(contact);
    }
}