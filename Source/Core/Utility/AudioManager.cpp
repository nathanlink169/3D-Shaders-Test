#include "CommonHeader.h"

std::map<std::string, Mix_Music*> AudioManager::s_BGM;  // Background Music
std::map<std::string, Mix_Chunk*> AudioManager::s_ME;	// Music Effects
std::map<std::string, SoundGroup*> AudioManager::s_SE;	// Sound Effects

std::string AudioManager::s_CurrentBGM;
int AudioManager::s_MusicEffectChannel;