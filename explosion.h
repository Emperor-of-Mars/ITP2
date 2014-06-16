#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "bullethell.h"

class Explosion{

    public:
        Explosion(int mxPos, int myPos, double mxScale, double myScale);
        ~Explosion();
        bool render(vector<Texture*> *Boomanimation);

    private:
        int framecounter, xPos, yPos;
        double xScale, yScale;


};

#endif
