#include "CommonHeader.h"

std::map<std::string, std::map<uint, Mesh*>> Label::s_Meshes;

std::string Label::m_CurrentFontLoading;
uint Label::m_CurrentCodePoint;
std::mutex Label::m_CodePointMutex;
std::mutex Label::m_MapMutex;