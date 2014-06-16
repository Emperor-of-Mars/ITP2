#include "highscores.h"
#include <cstdlib>
extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;

Highscores::Highscores(){

}

Highscores::~Highscores() {

}

void Highscores::highscores_view(SDL_Event *event, XmlHighscore *highsxml){
    Timer frametimer;
    Texture t_background, t_Beschreibung, t_Scores;
    SDL_Color textColor = {255, 64, 64, 255};
    string Beschreibung = "Highscores: ";
    string Scores = to_string(highsxml->showScore(0));
    if(!t_background.loadFromFile("res/Stars_Background.png")){
		cout << "Failed to load resources!" << endl;
		close_SDL();
		return;
	}
	t_Beschreibung.loadFromRenderedText(Beschreibung.c_str(), textColor);
	t_Beschreibung.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH * 2.5, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT * 3);
	t_Beschreibung.setPosition((float)SCREEN_WIDTH * 0.1, (float)SCREEN_HEIGHT * 0.45);

    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(gRenderer);
    t_background.render(2);
    t_Beschreibung.render();

    for (int i = 0; i<10; i++) {
    Scores = to_string(highsxml->showScore(i));
    t_Scores.loadFromRenderedText(Scores.c_str(), textColor);
    t_Scores.setPosition((float)SCREEN_WIDTH * 0.6, (float)SCREEN_HEIGHT * i/10);
    t_Scores.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH * 2.5, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT * 3);
    t_Scores.render();
    }
    SDL_RenderPresent(gRenderer);

    while(1){
        SDL_PollEvent(event);
        if(event->type == SDL_KEYDOWN) return;
    }
}
