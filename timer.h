/*
 * Author: Erik Skalla, Stefan Reinhold, Samuel Wambera, Martin Schwarz
 * Created: 01.05.2014
 * Last change: 01.05.2014 20:16
 * Purpose: Header
 */

#ifndef LIBS
#define LIBS

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#endif

#ifndef TIMER_H
#define TIMER_H

using namespace std;

class Timer{
	public:
		Timer();
		void start();
		void stop();
		void pause();
		void unpause();
		Uint32 getTicks();
		bool isStarted();
		bool isPaused();
	private:
		Uint32 mStartTicks;//The clock time when the timer started
		Uint32 mPausedTicks;//The ticks stored when the timer was paused
		bool mPaused;
		bool mStarted;
};

#endif