#ifndef HIGHSCORES_H_INCLUDED
#define HIGHSCORES_H_INCLUDED
#include "bullethell.h"
#include "xmlLoader.h"

using namespace std;

class Highscores {
    public:
        Highscores();
        ~Highscores();
        void highscores_view(SDL_Event *event, XmlHighscore *highsxml);
};

#endif // HIGHSCORES_H_INCLUDED
