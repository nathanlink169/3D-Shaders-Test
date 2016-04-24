#ifndef __ChainLink_H_
#define __ChainLink_H_

class ChainLink : public GameObject
{
public:
    ChainLink() : m_NextLink(nullptr) {}
    ChainLink(Scene* pScene, std::string name, Vector3 pos, Vector3 rot, Vector3 scale, Mesh* pMesh, ShaderProgram* pShader, GLuint texture);
    ~ChainLink(){}

    ChainLink* GetNextLink() { return m_NextLink; }
    ChainLink* SetNextLink(ChainLink* aNextLink);
private:
    ChainLink* m_NextLink;
};

#endif