#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "bullethell.h"
#include "shot.h"
#include "gun.h"
#include "explosion.h"
#include "player.h"

using namespace std;

class Enemy{
	public:
		Enemy();
		~Enemy();
        bool init(Texture *tex, Texture *bullet, float sx, float sy, float screenScaleX,
                    float screenScaleY, int life, int velocity, unsigned int animationSpeed,
                    float wSpawn, float hSpawn, int score, vector<vector<float >> bewegungen, int startmove);
		void setCol(int x, int y, int w, int h);
		void handleEvent(SDL_Event *e, int frameTime);
		void shoot();
		bool colHandle(int dam, Player *player);
		bool movement(int frameTime);
		vector<SDL_Rect> *getCol();
		vector<Shot* > getShots();
        void render();
        int getX();
        int getY();
		int getWidth();
		int getHeight();
		int getLife();
		vector<vector<float >> getMovements();
		Explosion* explode();
		void delShot(int pos);

	private:
        int maxVel, mLife, mWidth, mHeight, mXpos, mYpos, SpritePos[2], BulletFired, score, spawnXpos, spawnYpos;
		unsigned int frameAnimPause;
		float mScaleX, mScaleY, mScreenScaleX, mScreenScaleY, spawnXscale, spawnYscale;
		Timer curAnimFrame;
		SDL_Rect clip;
		Texture *mTexture;
		vector<Gun*> mGun;
		vector<Shot* > Shots;
		vector<SDL_Rect> mCol;
		vector<vector<float >> movements;
		int movemodulo;
};

#endif // ENEMY_H_INCLUDED
