#ifndef LEVEL_H
#define LEVEL_H

class Enemy;

#include "bullethell.h"
#include "enemy.h"

using namespace std;

class Level{

    public:
        Level();
        ~Level();
        Texture* getBackground();
        int getNumber();
        string getName();
        bool init(string backgroundlocation, int levelnumber, string levelname);

    private:
        int number;
        string name;
        Texture Background;
        vector<Enemy* > enemies;

};

#endif
