#include "Son_FMOD.h"
#include "FMOD/fmod.h"
#include <string>
#include <fstream>

using namespace std;

/*
constructeur et initialisateur de FmodEx
*/
sound_mgr::sound_mgr() {
	FMOD_System_Create(&sys);
	FMOD_System_Init(sys, 1, FMOD_INIT_NORMAL, NULL);
}

/*
destructeur
*/
sound_mgr::~sound_mgr() {
	FMOD_System_Release(sys);
	FMOD_Sound_Release(sound);
}

/*
pour lire un morceau
*/
int sound_mgr::play(const string &filename) {
	FMOD_System_CreateStream(sys, filename.c_str(), FMOD_DEFAULT | FMOD_LOOP_OFF | FMOD_2D, 0, &sound);
	FMOD_System_PlaySound(sys, NULL, false, 0, &channel);

	return 0;
}

/*
mettre un canal en pause
*/
void sound_mgr::pause() {
	FMOD_Channel_SetPaused(channel, true);
}

/*
reprendre la lecture sur un canal
*/
void sound_mgr::resume() {
	FMOD_Channel_SetPaused(channel, false);
}

/*
récupérer le nom de l'artiste du morceau courant
*/
string sound_mgr::getArtist() {
	FMOD_TAG         tag;
	FMOD_Sound_GetTag(sound, "ARTIST", 0, &tag);
	string s((char*)tag.data);

	return s;
}

/*
récupérer le titre du morceau courant
*/
string sound_mgr::getTitle() {
	FMOD_TAG         tag;
	FMOD_Sound_GetTag(sound, "TITLE", 0, &tag);
	string s((char*)tag.data);

	return s;
}

/*
récupérer la durée du morceau courant
*/
unsigned int sound_mgr::getLength() {
	unsigned int i;
	FMOD_Sound_GetLength(sound, &i, FMOD_TIMEUNIT_MS);
	return i;
}

/*
récupérer la position courante dans le morceau courant
*/
unsigned int sound_mgr::getCurrentPos() {
	unsigned int i;
	FMOD_Channel_GetPosition(channel, &i, FMOD_TIMEUNIT_MS);
	return i;
}

/*
pour avancer de i millisecondes
*/
void sound_mgr::avancer(unsigned int i) {
	unsigned int c = getCurrentPos();
	unsigned int l = getLength();
	if (c + i<l)
		FMOD_Channel_SetPosition(channel, c + i, FMOD_TIMEUNIT_MS);
}

/*
pour reculer de i millisecondes
*/
void sound_mgr::reculer(unsigned int i) {
	unsigned int c = getCurrentPos();
	if (c - i>0)
		FMOD_Channel_SetPosition(channel, c - i, FMOD_TIMEUNIT_MS);
}

/*
pour fixer le volume (entre 0.0 et 1.0)
*/
void sound_mgr::setVolume(float f) {
	FMOD_Channel_SetVolume(channel, f);
}

/*
pour mettre à jour le système (nécessaires aux callbacks)
*/
void sound_mgr::update() {
	FMOD_System_Update(sys);
}