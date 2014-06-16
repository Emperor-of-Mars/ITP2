#ifndef EXPLOSION_H
#define EXPLOSION_H

class Explosion{

    public:
        Explosion(int mxPos, int myPos, double mxScale, double myScale);
        ~Explosion();
        bool render();

    private:
        int framecounter, xPos, yPos;
        double xScale, yScale;


};

#endif
