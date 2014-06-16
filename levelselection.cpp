
#include "levelselection.h"

Levelselection::Levelselection(){

}

int Levelselection::levelselection_view(SDL_Event *event, int anzahl){
    SDL_Color textColor = {255, 64, 64, 255};
    int frameTime = 0;      // MBUp = 0;
    Timer frameTimer;
    Texture t_button, t_background, t_text;
    vector<string> text;
    string level_text = "Level ";
    stringstream temp_text;
    vector <Button*> buttons;
    int button_x = 0;
    int button_y = 0;
    bool quit;
    int return_wert = 0;

    if(!(gFont = TTF_OpenFont("res/kenpixel_future.ttf", 24)) || !t_background.loadFromFile("res/Stars_Background.png") || !t_button.loadFromFile("res/button.png")){
		cout << "Failed to load resources in levelselection!" << endl;
		close_SDL();
		return -1;
	}

    for(int i = 0; i < 2; i++){
        text.push_back(level_text);
        temp_text.str("");
        temp_text << i;
        text[i] += temp_text.str();
    }

    t_button.setBlendMode(SDL_BLENDMODE_BLEND);

    cout << "debug levelselection: anzahl: " << anzahl << endl;
    for(int i = 0; i < 2; i++){
        buttons.push_back(new Button);
        buttons[i]->init(&t_button, 225, text[i].c_str(), textColor);
        buttons[i]->setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
        buttons[i]->setPosition(button_x, button_y);
        button_x += buttons[i]->getWidth();
        if(button_x >= (SCREEN_WIDTH * 0.8)){
            button_x = 0;
            button_y += buttons[i]->getHeight();
        }
        if(button_y >= (SCREEN_WIDTH * 0.8)){
            break;
        }
    }

    while(!quit){
        frameTime = frameTimer.getTicks();
		frameTimer.start();

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

		//if(event->type == SDL_MOUSEBUTTONUP) MBUp = 1;           //wenn event Mousebutton up ist
		//if(MBUp == 1){                                          //welcher button angeklickt wurde
			for(int i = 0; i < anzahl; i++){
                if(buttons[i]->handleEvent(event)){
                    return_wert = i;
                    quit = 1;
                }
			}
		//}
        while(SDL_PollEvent(event)){}

        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear(gRenderer);

        t_background.render(2);

        for(int i = 0; i < 2; i++){
            buttons[i]->render();
        }

        SDL_RenderPresent(gRenderer);

        frameTime = frameTimer.getTicks();
        if(frameTime < 1000.f / MAX_FPS){
            SDL_Delay(1000.f / (float)MAX_FPS - (float)frameTime);
        }

        /*while(1){
            SDL_PollEvent(event);
            //if(event->type == SDL_MOUSEBUTTONUP) return;
            if(event->type == SDL_KEYDOWN) return;
        }*/
    }
    return return_wert;
}
