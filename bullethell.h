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

#define BASE_SCREEN_WIDTH 1920
#define BASE_SCREEN_HEIGHT 1080
#define MAX_FPS 240
#define UPDATE_TIME 8

using namespace std;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern TTF_Font *gFont;

#include "timer.h"
#include "texture.h"
#include "button.h"
#include "settings.h"

bool init_SDL();
void close_SDL();
void PlayVideo();
int run(SDL_Event *event);
int settings_view(SDL_Event *event);
bool check_col(vector<SDL_Rect> *col1, vector<SDL_Rect> *col2);

class Shot{
	public:
		Shot(Texture *tex, int posX, int posY, float sX = 1, float sY = 1, int vel = 10, int dam = 10);
		void setCol(int x, int y, int w, int h);
		bool move(float frameTime);
		vector<SDL_Rect> *getCol();
		void render();
		int getDamage();
	private:
		int maxVel, Damage, mXpos, mYpos, mWidth, mHeight, SpritePos, frameAnimPause;
		float mScaleX, mScaleY;
		Timer curAnimFrame;
		SDL_Rect clip;
		Texture *mTexture;
		vector<SDL_Rect> mCol;
};

class Gun{
	public:
		Gun(vector<Shot*> *Shots, Texture *tex = NULL, int posX = 0, int posY = 0, float ScaleX = 1, float ScaleY = 1);
		void fire(float posX, float posY, float mScaleX = 1, float mScaleY = 1);
	private:
		int maxVel, Damage;
		float mXpos, mYpos, mScaleX, mScaleY;
		Timer coolDown;
		Texture *mTexture;
		vector<Shot*> *mShots;
};

class Player{
	public:
		Player();
		~Player();
		bool init(Texture *tex, Texture *bullet, vector<Shot*> *Shot = NULL, float sx = 1, float sy = 1, float screenScaleX = 1, float screenScaleY = 1, int life = 100, int animationSpeed = 120);
		void setCol(int x, int y, int w, int h);
		void handleEvent(SDL_Event *e, int frameTime);
		bool colHandle(int dam);
		vector<SDL_Rect> *getCol();
        void render();
		int getWidth();
		int getHeight();
		int getLife();
	private:
		int maxVel, mLife, mWidth, mHeight, mXpos, mYpos, SpritePos[2], BulletFired;
		unsigned int frameAnimPause;
		float mScaleX, mScaleY, mScreenScaleX, mScreenScaleY;
		Timer curAnimFrame;
		SDL_Rect clip;
		Texture *mTexture;
		vector<Gun*> mGun;
		vector<SDL_Rect> mCol;
};

class Enemy{
	public:
		Enemy();
		~Enemy();
		bool init(Texture *tex, vector<SDL_Rect> *col, Texture *bullet, vector<Shot*> *Shot = NULL, float sx = 1, float sy = 1, float screenScaleX = 1, float screenScaleY = 1, int animationSpeed = 120);
		void move(int frameTime);
        void render(float frameTime);
	private:
		int maxVel, mWidth, mHeight, mXpos, mYpos, SpritePos[2], BulletFired;
		unsigned int frameAnimPause;
		float mScaleX, mScaleY, mScreenScaleX, mScreenScaleY;
		Timer curAnimFrame;
		SDL_Rect clip;
		Texture *mTexture;
		vector<Gun*> mGun;
		vector<SDL_Rect> *mCol;
};













