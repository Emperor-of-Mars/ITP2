#ifndef LEVELSELECTION_H
#define LEVELSELECTION_H

#include "bullethell.h"
#include "level.h"

class Levelselection{
    public:
        Levelselection();
        int levelselection_view(SDL_Event *event, int anzahl);
};

#endif
