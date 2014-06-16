
#include "explosion.h"
#include "texture.h"

Explosion::Explosion(int mxPos, int myPos, double mxScale, double myScale){
    framecounter = 1;
    xPos = mxPos;
    yPos = myPos;
    xScale = mxScale;
    yScale = myScale;
}

Explosion::~Explosion(){

}

bool Explosion::render(vector<Texture*> *Boomanimation){

    if(framecounter == 0) return true;

    if(framecounter >= Boomanimation->size()) return false;

    (*Boomanimation)[framecounter]->render(1, xPos, yPos, xScale, yScale);


    framecounter++;

	return true;
}
