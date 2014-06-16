
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

bool Explosion::render(){

    if(framecounter == 0) return true;

    Texture frame;
	stringstream file;
	string num;

    file << framecounter;
    file >> num;
    file.str("");
    file.clear();
    while(num.size() < 4) num.insert(0, "0");
    file << "res/Explosion/" << num << ".png";
    //cout << file.str() << endl;
    if(!frame.loadFromFile(file.str().c_str())) return false;
//    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
//    SDL_RenderClear(gRenderer);
    frame.render(1, xPos, yPos, xScale, yScale);
//    SDL_RenderPresent(gRenderer);

    framecounter++;

	return true;
}
