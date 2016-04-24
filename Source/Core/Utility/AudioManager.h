#ifndef __AudioManager_H__
#define __AudioManager_H__

enum SoundGroups
{
    SoundGroup_Music = 0,
    SoundGroup_Effects = 1
};

class SoundGroup
{
public:
    SoundGroup(){}
    ~SoundGroup()
    {
        for (uint i = 0; i < m_Sounds.size(); i++)
            Mix_FreeChunk(m_Sounds[i]);
        npw::SafeDeleteVector(m_Sounds);
    }

    void AddSound(Mix_Chunk* aChunk)
    {
        m_Sounds.push_back(aChunk);
    }

    Mix_Chunk* GetRandomSound()
    {
        return m_Sounds[npw::Random(0, m_Sounds.size())];
    }
private:
    std::vector<Mix_Chunk*> m_Sounds;
};

class AudioManager
{
public:
	
private:
	static std::map<std::string, Mix_Music*> s_BGM; // Background Music
	static std::map<std::string, Mix_Chunk*> s_ME;	// Music Effects
	static std::map<std::string, SoundGroup*> s_SE;	// Sound Effects

	static std::string s_CurrentBGM;
    static int s_MusicEffectChannel;
public:
	static bool InitializeManager()
	{
		if (!LOAD_SOUND)
			return false;
        s_CurrentBGM.clear();
        s_MusicEffectChannel = -1;

		if (SDL_Init(SDL_INIT_AUDIO) == -1)
			return false;
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
			return false;

        int numChannels = Mix_GroupCount(-1);
        Mix_GroupChannel(0, SoundGroup_Music);
        Mix_GroupChannels(1, numChannels - 1, SoundGroup_Effects);

		return true;
	}
	static void ClearManager()
	{
		if (!LOAD_SOUND)
			return;
		for each(auto iterator in s_BGM)
			Mix_FreeMusic(iterator.second);
		npw::SafeDeleteMap(s_BGM);
		
		for each(auto iterator in s_ME)
			Mix_FreeChunk(iterator.second);
		npw::SafeDeleteMap(s_ME);

		npw::SafeDeleteMap(s_SE);

		Mix_CloseAudio();
		SDL_Quit();
	}

	static bool AddBGM(std::string aMusicName, std::string aFileName)
	{
		if (!LOAD_SOUND)
			return false;

        if (s_BGM.find(aMusicName) != s_BGM.end())
            return false;

        aFileName = "Data/Audio/BGM/" + aFileName + ".wav";

        const char* file = aFileName.c_str();

        Mix_Music* music = Mix_LoadMUS(file);
        npw::BreakIfTrue(music == NULL);

        s_BGM[aMusicName] = music;
		return true;
	}

	static bool AddME(std::string aEffectName, std::string aFileName)
	{
		if (!LOAD_SOUND)
			return false;

        if (s_ME.find(aEffectName) != s_ME.end())
            return false;

        aFileName = "Data/Audio/ME/" + aFileName + ".wav";

        const char* file = aFileName.c_str();

        Mix_Chunk* music = Mix_LoadWAV(file);
        npw::BreakIfTrue(music == NULL);

        s_ME[aEffectName] = music;
		return true;
	}

	static bool AddSE(std::string aEffectName, std::string aFileName)
	{
		if (!LOAD_SOUND)
			return false;

        SoundGroup* group = s_SE[aEffectName];
        if (group == nullptr)
        {
            s_SE[aEffectName] = new SoundGroup();
            group = s_SE[aEffectName];
        }

        aFileName = "Data/Audio/SE/" + aFileName + ".wav";

        const char* file = aFileName.c_str();

        Mix_Chunk* sound = Mix_LoadWAV(file);
        npw::BreakIfTrue(sound == NULL);

        group->AddSound(sound);
		return true;
	}

	static bool PlayBGM(std::string aName)
	{
		if (!LOAD_SOUND)
			return false;

        if (s_BGM.find(aName) == s_BGM.end())
            return false;

        if (s_MusicEffectChannel != -1)
            return false;

        Mix_Music* music = s_BGM[aName];
        if (Mix_PlayingMusic() != 0)
            Mix_HaltMusic();

        Mix_PlayMusic(music, -1);

        s_CurrentBGM = aName;
		return true;
	}

	static bool PlayME(std::string aName)
	{
		if (!LOAD_SOUND)
			return false;

        if (s_ME.find(aName) == s_ME.end())
            return false;

        Mix_Chunk* sound = s_ME[aName];

        if (Mix_Playing(s_MusicEffectChannel) && s_MusicEffectChannel != -1)
        {
            Mix_HaltChannel(s_MusicEffectChannel);
        }
        else
        {
            if (Mix_PlayingMusic())
                Mix_PauseMusic();
        }

        int channel = Mix_GroupAvailable(SoundGroup_Effects); 
        if (channel == -1)
            channel = Mix_GroupOldest(SoundGroup_Effects);

        s_MusicEffectChannel = Mix_PlayChannel(channel, sound, 0);
		return true;
	}

	static bool PlaySE(std::string aName)
	{
		if (!LOAD_SOUND)
			return false;

        if (s_SE.find(aName) == s_SE.end())
            return false;

        Mix_Chunk* sound = s_SE[aName]->GetRandomSound(); 
        
        int channel = Mix_GroupAvailable(SoundGroup_Effects);
        if (channel == -1)
            channel = Mix_GroupOldest(SoundGroup_Effects);

        Mix_PlayChannel(channel, sound, 0);
        return true;
	}

    static void Update(double aDelta)
	{
		if (!LOAD_SOUND)
			return;

        if (s_MusicEffectChannel != -1)
        {
            if (!(Mix_Playing(s_MusicEffectChannel)))
            {
                s_MusicEffectChannel = -1;
                Mix_ResumeMusic();
            }
        }
    }

	static std::string GetBGMName() 
	{
		if (!LOAD_SOUND)
			return false;

		return s_CurrentBGM; 
	}

	static void StopBGM() 
	{
		if (!LOAD_SOUND)
			return;

        Mix_HaltMusic();
    }
    static void StopME()
	{
		if (!LOAD_SOUND)
			return;

        if (s_MusicEffectChannel != -1)
            Mix_HaltChannel(s_MusicEffectChannel);
    }
    static void StopAllSE()
	{
		if (!LOAD_SOUND)
			return;

        Mix_HaltChannel(-1);
    }
};

#endif