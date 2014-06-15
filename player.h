#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "shot.h"
#include "gun.h"

using namespace std;

class Player{
	public:
		Player();
		~Player();
		bool init(Texture *tex, Texture *bullet, vector<Shot*> *Shot, float sx, float sy, float screenScaleX, float screenScaleY, int life, unsigned int animationSpeed);
		void setCol(int x, int y, int w, int h);
		void handleEvent(SDL_Event *e, int frameTime);
		bool colHandle(bool coll_ship);
		vector<SDL_Rect> *getCol();
        void render();
		int getWidth();
		int getHeight();
		int getLife();
		unsigned int getScore();
	private:
		int maxVel, mLife, mWidth, mHeight, mXpos, mYpos, SpritePos[2];
		unsigned int frameAnimPause, score;
		float mScaleX, mScaleY, mScreenScaleX, mScreenScaleY;
		Timer curAnimFrame;
		SDL_Rect clip;
		Texture *mTexture;
		vector<Gun*> mGun;
		vector<SDL_Rect> mCol;
};

#endif // PLAYER_H_INCLUDED
