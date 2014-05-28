/*
 * Author: Erik Skalla, Stefan Reinhold, Samuel Wambera, Martin Schwarz
 * Created: 01.05.2014
 * Last change: 01.05.2014 20:16
 * Purpose: Header
 */

#include "timer.h"

//###############################################  Timer:
Timer::Timer(){
	mStartTicks = 0;
	mPausedTicks = 0;
	mPaused = false;
	mStarted = false;
}

void Timer::start(){
	mStarted = true;
	mPaused = false;
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
	return;
}

void Timer::stop(){
	mStarted = false;
	mPaused = false;
	mStartTicks = 0;
	mPausedTicks = 0;
	return;
}

void Timer::pause(){
	if(mStarted && !mPaused){
		mPaused = true;
		mStartTicks = 0;
		mPausedTicks = SDL_GetTicks() - mStartTicks;//Calculate the paused ticks
	}
	return;
}

void Timer::unpause(){
	if(mStarted && mPaused){
		mPaused = false;
		mStartTicks = SDL_GetTicks() - mPausedTicks;
		mPausedTicks = 0;
	}
	return;
}

Uint32 Timer::getTicks(){
	Uint32 time = 0;
	if(mStarted){
		if(mPaused){
			time = mPausedTicks;
		}
		else{
			time = SDL_GetTicks() - mStartTicks;
		}
	}
	return time;
}

bool Timer::isStarted(){
	return mStarted;//Timer is running and paused or unpaused
}

bool Timer::isPaused(){
	return mPaused && mStarted;//Timer is running and paused
}












