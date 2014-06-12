#include "bullethell.h"
#include "settings.h"
#include <fstream>

using namespace std;

extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;

Settings::Settings(){
    read_settings();
}

void Settings::read_settings(){
    fstream setts;
    setts.open("settings.dat", fstream::in);
    int temp_w[] = {640, 1024, 1280, 1366, 1600, 1920, 3840};
    int temp_h[] = {480, 576, 720, 768, 900, 1080, 2160};
    maximal_resolution = 7;
    for(int i = 0; i < maximal_resolution; i++){
        available_heights.push_back(temp_h[i]);
        available_widths.push_back(temp_w[i]);
    }
    if(!setts.is_open()){       //die datei ist nicht vorhanden, es werden default-werte verwendet
        actual_resolution = 4;
        settings_found = false;
    }
    else{
        char temp[5];
        char temp_c;
        for(int i = 0; i < 5; i++){
            temp_c = setts.get();
            if((temp_c == EOF) || (temp_c == '\n')){
                temp[i] = '\0';
            }
            else{
                temp[i] = temp_c;
            }
        }
        available_widths.push_back(atoi(temp));
        for(int i = 0; i < 5; i++){
            temp_c = setts.get();
            if((temp_c == EOF) || (temp_c == '\n')){
                temp[i] = '\0';
            }
            else{
                temp[i] = temp_c;
            }
        }
        available_heights.push_back(atoi(temp));
        actual_resolution = 7;
        maximal_resolution++;
        settings_found = true;
    }
    setts.close();
}

void Settings::write_settings(){
    fstream setts;
    setts.open("settings.dat", fstream::out);
    //hier die funktion zum ausschreiben der settings
    if(settings_found == false){
        setts << available_widths[actual_resolution] << '\n' << available_heights[actual_resolution] << '\n';
    }
    setts.close();
}

void Settings::decrease_resolution(){
    if(actual_resolution > 0){
        actual_resolution--;
    }
    res_text.str("");
    res_text << available_widths[actual_resolution] << " x " << available_heights[actual_resolution];
    resolution->loadFromRenderedText(res_text.str().c_str(), textColor);
}

void Settings::increase_resolution(){
    if(actual_resolution < maximal_resolution-1){
        actual_resolution++;
    }
    res_text.str("");
    res_text << available_widths[actual_resolution] << " x " << available_heights[actual_resolution];
    resolution->loadFromRenderedText(res_text.str().c_str(), textColor);
}

int Settings::settings_view(SDL_Event *event){
    int state = 0, frameTime = 0, MBUp = 0;
	bool quit = false;
	Timer frameTimer;
	textColor = {255, 88, 88, 255};
	Button setResLeft, setResRight, setFull, setVsync, apply, backToMenu;
	Texture warning, full, vsync, Background, buttonTexture, buttonTexture_kl;
	resolution = new Texture;
	res_text << available_widths[actual_resolution] << " x " << available_heights[actual_resolution];

//###############################################  Load resources
	if(!Background.loadFromFile("res/Settings.png") ||
		!buttonTexture.loadFromFile("res/button.png") ||
		!buttonTexture_kl.loadFromFile("res/button_kl.png") ||
		!setResLeft.init(&buttonTexture_kl, 112.5, "<", textColor) ||
		!setResRight.init(&buttonTexture_kl, 112.5, ">", textColor) ||
		!setFull.init(&buttonTexture, 225, "Fullscreen:", textColor) ||
		!setVsync.init(&buttonTexture, 225, "Vsync:", textColor) ||
		!apply.init(&buttonTexture, 225, "Apply Changes", textColor) ||
		!warning.loadFromRenderedText("Warning: Some settings will apply only after restart!", textColor) ||
		!full.loadFromRenderedText("on", textColor) ||
		!resolution->loadFromRenderedText(res_text.str().c_str(), textColor) ||
		!vsync.loadFromRenderedText("on", textColor) ||
		!backToMenu.init(&buttonTexture, 225, "Back", textColor))
	{
		cout << "Failed to load resources!" << endl;
		close_SDL();
		return 1;
	}
	buttonTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	buttonTexture_kl.setBlendMode(SDL_BLENDMODE_BLEND);
	setResLeft.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	setResRight.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	resolution->setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	setFull.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	full.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	backToMenu.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	//apply.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	setResLeft.setPosition(SCREEN_WIDTH * 0.5 - setResLeft.getWidth() - resolution->getWidth() * 0.6, SCREEN_HEIGHT * 0.1);
	setResRight.setPosition(SCREEN_WIDTH * 0.5 + resolution->getWidth() * 0.6, SCREEN_HEIGHT * 0.1);
	resolution->setPosition(SCREEN_WIDTH * 0.5 - resolution->getWidth() * 0.5, SCREEN_HEIGHT * 0.1 + setResLeft.getHeight() / 2 - resolution->getHeight() / 2);
	setFull.setPosition(SCREEN_WIDTH * 0.5 - (setFull.getWidth() * 0.6 + full.getWidth() * 0.5), SCREEN_HEIGHT * 0.2);
	full.setPosition(SCREEN_WIDTH * 0.5 + (setFull.getWidth() * 0.6 - full.getWidth() * 0.5), SCREEN_HEIGHT * 0.2 + setFull.getHeight() / 2 - full.getHeight() / 2);
	//apply.setPosition(SCREEN_WIDTH * 0.5 - apply.getWidth() / 2, SCREEN_HEIGHT * 0.6 - apply.getHeight() / 2);
	backToMenu.setPosition(SCREEN_WIDTH *0.1 - backToMenu.getWidth() * 0.5, SCREEN_HEIGHT * 0.8 - backToMenu.getHeight() / 2);
//###############################################  Gameloop
	while(!quit){
		frameTimer.start();
		while(SDL_PollEvent(event) != 0){
			if(event->type == SDL_QUIT)quit = true;
			else if(event->type == SDL_KEYDOWN){
				switch(event->key.keysym.sym){
				case SDLK_q:
					quit = true;
					state = 0;
					break;
				}
			}
		}
		if(event->type == SDL_MOUSEBUTTONUP) MBUp = 1;
		if(MBUp == 1){
			if(setResLeft.handleEvent(event) == 1){
                decrease_resolution();
                resolution->setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
                resolution->setPosition(SCREEN_WIDTH * 0.5 - resolution->getWidth() * 0.5, SCREEN_HEIGHT * 0.1 + setResLeft.getHeight() / 2 - resolution->getHeight() / 2);
                while(event->button.state == SDL_PRESSED){SDL_PollEvent(event);}
			}
			if(setResRight.handleEvent(event)){
                increase_resolution();
                resolution->setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
                resolution->setPosition(SCREEN_WIDTH * 0.5 - resolution->getWidth() * 0.5, SCREEN_HEIGHT * 0.1 + setResLeft.getHeight() / 2 - resolution->getHeight() / 2);
                while(event->button.state == SDL_PRESSED){SDL_PollEvent(event);}
			}
			if(setFull.handleEvent(event));
			//if(apply.handleEvent(event));
			if(backToMenu.handleEvent(event) == 1)quit = true;
		}
//###############################################  Rendering
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear(gRenderer);

		Background.render(2);
		setResLeft.render();
		setResRight.render();
		resolution->render();
		setFull.render();
		full.render();
		//apply.render();
		backToMenu.render();

		SDL_RenderPresent(gRenderer);

		frameTime = frameTimer.getTicks();
		if(frameTime < 1000.f / MAX_FPS){
			SDL_Delay(1000.f / (float)MAX_FPS - (float)frameTime);
		}
	}
	write_settings();
//###############################################  Gameloop end
	return state;
}

int Settings::get_resolution_height(){
    return available_heights[actual_resolution];
}
int Settings::get_resolution_width(){
    return available_widths[actual_resolution];
}


