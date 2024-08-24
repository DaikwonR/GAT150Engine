#pragma once

#include "fmod.h"
#include "Audio.h"
#include "Resources\Resource.h"

class AudioSource;

class AudioClip : public Resource
{
public:
	AudioClip() = default;
	~AudioClip();


	bool Load(const std::string& filename, class Audio& audio);

	friend Audio;
	friend AudioSource;

public:
	FMOD::Sound* m_sound{ nullptr };
    bool Create(std::string name, ...) override;

};