#ifndef __POOL_H_
#define __POOL_H_

#include <vector>

template <class T>
class Pool
{
public:
    Pool(){}
    virtual ~Pool()
    {
        npw::SafeDeleteVector(m_ActiveObjects);
        npw::SafeDeleteVector(m_DormantObjects);
    }

    T* AddNewObject()
    {
        T* object = new T();
        m_DormantObjects.push_back(object);
        return object;
    }

    T* AddNewObject(T* object)
    {
        m_DormantObjects.push_back(object);
        return object;
    }

    T* GetNew()
    {
        T* object;
		if (m_DormantObjects.empty())
			return nullptr;
        else
        {
            object = m_DormantObjects.back();
            m_DormantObjects.pop_back();
        }

        m_ActiveObjects.push_back(object);

        return object;
    }

    void Return(T* Object)
    {
        for (uint i = 0; i < m_ActiveObjects.size(); i++)
        {
            if (m_ActiveObjects[i] == Object)
            {
                m_ActiveObjects.erase(m_ActiveObjects.begin() + i);
                m_DormantObjects.push_back(Object);
                return;
            }
        }
    }

    void ReturnAllActiveObjects()
    {
        while (!(m_ActiveObjects.empty()))
        {
            Return m_ActiveObjects[0];
        }
    }

    T* GetActiveObject(unsigned int aIndex)
    {
        if (aIndex >= NumberOfActiveObjects())
            return nullptr;

        return m_ActiveObjects[aIndex];
    }

    unsigned int NumberOfActiveObjects()
    {
        return m_ActiveObjects.size();
    }

    unsigned int NumberOfDormantObjects()
    {
        return m_DormantObjects.size();
    }
private:
    std::vector<T*> m_ActiveObjects;
    std::vector<T*> m_DormantObjects;
};

#endif