#include "credits.h"

extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;

Credits::Credits(){

}

void Credits::credits_view(SDL_Event *event){
    bool quit = false;
    Timer frametimer;
    Texture t_background, t_credits_betreuer, t_credits_teamleader, t_credits_programmer, t_credits_programmer_name, buttonTexture;
    Button backToMenu;
    SDL_Color textColor = {255, 64, 64, 255};
    string credits_betreuer = "Betreuer:        Rebin Jaber";
    string credits_teamleader = "Teamleader:   Erik Skalla";
    string credits_programmer = "Executive Programmer:";
    if(!t_background.loadFromFile("res/Stars_Background.png") ||
       !buttonTexture.loadFromFile("res/button.png") ||
       !backToMenu.init(&buttonTexture, 225, "Back", textColor)){
		cout << "Failed to load resources!" << endl;
		close_SDL();
		return;
	}
	t_credits_betreuer.loadFromRenderedText(credits_betreuer.c_str(), textColor);
	t_credits_teamleader.loadFromRenderedText(credits_teamleader.c_str(), textColor);
	t_credits_programmer.loadFromRenderedText(credits_programmer.c_str(), textColor);
	t_credits_programmer_name.loadFromRenderedText("Martin Schwarz", textColor);
	t_credits_betreuer.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH * 2.5, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT * 3);
	t_credits_teamleader.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH * 2.5, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT * 3);
	t_credits_programmer.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH * 2.5, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT * 3);
	t_credits_programmer_name.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH * 2.5, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT * 3);
	t_credits_betreuer.setPosition((float)SCREEN_WIDTH * 0.1, (float)SCREEN_HEIGHT * 0.1);
	t_credits_teamleader.setPosition((float)SCREEN_WIDTH * 0.1, (float)SCREEN_HEIGHT * 0.25);
	t_credits_programmer.setPosition((float)SCREEN_WIDTH * 0.1, (float)SCREEN_HEIGHT * 0.4);
	t_credits_programmer_name.setPosition((float)SCREEN_WIDTH * 0.3, (float)SCREEN_HEIGHT * 0.5);

    backToMenu.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
    backToMenu.setPosition(SCREEN_WIDTH *0.1 - backToMenu.getWidth() * 0.5, SCREEN_HEIGHT * 0.8 - backToMenu.getHeight() / 2);
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear(gRenderer);

    while(!quit){
        frametimer.start();
		while(SDL_PollEvent(event) != 0){
			if(event->type == SDL_QUIT)quit = true;
			else if(event->type == SDL_KEYDOWN){
				switch(event->key.keysym.sym){
				case SDLK_q:
					quit = true;
					break;
				}
			}
		}

    if(backToMenu.handleEvent(event) == 1)quit = true;

    t_background.render(2);
    t_credits_betreuer.render();
    t_credits_teamleader.render();
    t_credits_programmer.render();
    t_credits_programmer_name.render();
    t_credits_programmer_name.loadFromRenderedText("Erik Skalla", textColor);
    t_credits_programmer_name.setPosition((float)SCREEN_WIDTH * 0.3, (float)SCREEN_HEIGHT * 0.6);
    t_credits_programmer_name.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH * 2.5, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT * 3);
    t_credits_programmer_name.render();
    t_credits_programmer_name.loadFromRenderedText("Stefan Reinhold", textColor);
    t_credits_programmer_name.setPosition((float)SCREEN_WIDTH * 0.3, (float)SCREEN_HEIGHT * 0.7);
    t_credits_programmer_name.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH * 2.5, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT * 3);
    t_credits_programmer_name.render();
    t_credits_programmer_name.loadFromRenderedText("Samuel Wambera", textColor);
    t_credits_programmer_name.setPosition((float)SCREEN_WIDTH * 0.3, (float)SCREEN_HEIGHT * 0.8);
    t_credits_programmer_name.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH * 2.5, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT * 3);
    t_credits_programmer_name.render();

    backToMenu.render();
    SDL_RenderPresent(gRenderer);

    }
}
