#include "bullethell.h"
#include "settings.h"
#include <fstream>

using namespace std;

Settings::Settings(){
    read_settings();
}

void Settings::read_settings(){
    fstream setts;
    setts.open("settings.dat", fstream::in);
    if(!setts.is_open()){       //die datei ist nicht vorhanden, es werden default-werte verwendet
        available_heights.resize(1);
        available_widths.resize(1);
        available_heights[0] = 600;
        available_widths[0] = 800;
        actual_resolution = 0;
        maximal_resolution = 0;
    }
    else{
        //hier der code zum einlesen der settings
    }
    setts.close();
}

void Settings::write_settings(){
    fstream setts;
    setts.open("settings.dat", fstream::out);
    //hier die funktion zum ausschreiben der settings
    setts.close();
}

void Settings::decrease_resolution(){
    if(actual_resolution > 0){
        actual_resolution--;
    }
}

void Settings::increase_resolution(){
    if(actual_resolution < maximal_resolution){
        actual_resolution++;
    }
}

int Settings::settings_view(SDL_Event *event){
    int state = 0, frameTime = 0, MBUp = 0;
	bool quit = false;
	Timer frameTimer;
	SDL_Color textColor = {255, 88, 88, 255};
	Button setResLeft, setResRight, setFull, setVsync, apply, backToMenu;
	Texture resolution, warning, full, vsync, Background, buttonTexture, buttonTexture_kl;
	stringstream res_text;
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
		!resolution.loadFromRenderedText("1920 x 1080", textColor) ||
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
	resolution.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	setFull.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	full.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	backToMenu.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	setResLeft.setPosition(SCREEN_WIDTH * 0.5 - setResLeft.getWidth() - resolution.getWidth() * 0.6, SCREEN_HEIGHT * 0.1);
	setResRight.setPosition(SCREEN_WIDTH * 0.5 + resolution.getWidth() * 0.6, SCREEN_HEIGHT * 0.1);
	resolution.setPosition(SCREEN_WIDTH * 0.5 - resolution.getWidth() * 0.5, SCREEN_HEIGHT * 0.1 + setResLeft.getHeight() / 2 - resolution.getHeight() / 2);
	setFull.setPosition(SCREEN_WIDTH * 0.5 - (setFull.getWidth() * 0.6 + full.getWidth() * 0.5), SCREEN_HEIGHT * 0.2);
	full.setPosition(SCREEN_WIDTH * 0.5 + (setFull.getWidth() * 0.6 - full.getWidth() * 0.5), SCREEN_HEIGHT * 0.2 + setFull.getHeight() / 2 - full.getHeight() / 2);
	backToMenu.setPosition(SCREEN_WIDTH *0.5 - backToMenu.getWidth() * 0.5, SCREEN_HEIGHT * 0.8 - backToMenu.getHeight() / 2);
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
			if(setResLeft.handleEvent(event) == 1) decrease_resolution();
			if(setResRight.handleEvent(event)) increase_resolution();
			setFull.handleEvent(event);
			if(backToMenu.handleEvent(event) == 1)quit = true;
		}
//###############################################  Rendering
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear(gRenderer);

		Background.render(2);
		setResLeft.render();
		setResRight.render();
		resolution.render();
		setFull.render();
		full.render();
		backToMenu.render();

		SDL_RenderPresent(gRenderer);

		frameTime = frameTimer.getTicks();
		if(frameTime < 1000.f / MAX_FPS){
			SDL_Delay(1000.f / (float)MAX_FPS - (float)frameTime);
		}
	}
//###############################################  Gameloop end
	return state;
}

int Settings::get_resolution_height(){
    return available_heights[actual_resolution];
}
int Settings::get_resolution_width(){
    return available_widths[actual_resolution];
}


