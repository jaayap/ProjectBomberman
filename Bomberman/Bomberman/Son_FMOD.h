#include <string>
#include <list>
#include "FMOD/fmod.h"

class sound_mgr {
public:
	sound_mgr();
	~sound_mgr();
	int play(const std::string &);

	std::string getArtist();
	std::string getTitle();
	unsigned int getLength();
	unsigned int getCurrentPos();

	void pause();
	void resume();
	void avancer(unsigned int);
	void reculer(unsigned int);
	void setVolume(float);

	void update();
private:
	FMOD_SYSTEM  *sys;
	FMOD_SOUND   *sound;
	FMOD_CHANNEL *channel;
};