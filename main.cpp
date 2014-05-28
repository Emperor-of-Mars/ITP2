/*
 * Author: Erik Skalla, Stefan Reinhold, Samuel Wambera, Martin Schwarz
 * Created: 01.05.2014
 * Last change: 01.05.2014 20:16
 * Purpose: Main Function
 */

#include "bullethell.h"

int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;
Settings settings;

//###############################################  Main
int main(int argc, char *argv[]){
	SDL_Event event;
	int frameTime = 0, subMenu = 0, MBUp = 1;
	float FPS = 0;
	bool quit = false;
	stringstream FPS_text;
	Timer frameTimer;
	Texture buttonTexture, fps, Background;
	Button play_button, settings_button, credits_button, close_button;
	SDL_Color textColor = {255, 88, 88, 255};
//###############################################  Initialize
	if(!init_SDL()){
		cout << "Failed to initialize SDL!" << endl;
		close_SDL();
		return 1;
	}
//###############################################  Load resources
	if((gFont = TTF_OpenFont("res/kenpixel_future.ttf", 24)) == NULL ||
		!Background.loadFromFile("res/Menu.png") ||
		!buttonTexture.loadFromFile("res/button.png") ||
		!play_button.init(&buttonTexture, 225, "Play", textColor) ||
		!settings_button.init(&buttonTexture, 225, "Settings", textColor) ||
		!credits_button.init(&buttonTexture, 225, "Credits", textColor) ||
		!close_button.init(&buttonTexture, 225, "Close", textColor))
	{
		cout << "Failed to load resources!" << endl;
		close_SDL();
		return 1;
	}
//###############################################  Set stuff
	buttonTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	play_button.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	settings_button.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	credits_button.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	close_button.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	play_button.setPosition(SCREEN_WIDTH * 0.5 - play_button.getWidth() / 2, SCREEN_HEIGHT * 0.2 - play_button.getHeight() / 2);
	settings_button.setPosition(SCREEN_WIDTH * 0.5 - settings_button.getWidth() / 2, SCREEN_HEIGHT * 0.4 - settings_button.getHeight() / 2);
	credits_button.setPosition(SCREEN_WIDTH * 0.5 - credits_button.getWidth() / 2, SCREEN_HEIGHT * 0.6 - credits_button.getHeight() / 2);
	close_button.setPosition(SCREEN_WIDTH * 0.5 - close_button.getWidth() / 2, SCREEN_HEIGHT * 0.8 - close_button.getHeight() / 2);
	fps.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	PlayVideo();
//###############################################  Gameloop
	while(!quit){
		frameTime = frameTimer.getTicks();
		frameTimer.start();
		FPS = 1000.f / (float)frameTime;
		FPS_text.str("");
		FPS_text << FPS;
		while(SDL_PollEvent(&event) != 0){
			if(event.type == SDL_QUIT)quit = true;
			else if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
				case SDLK_q:
					quit = true;
					break;
				}
			}
		}
		if(event.type == SDL_MOUSEBUTTONUP) MBUp = 1;           //wenn event Mousebutton up ist
		if(MBUp == 1){                                          //welcher button angeklickt wurde
			if(play_button.handleEvent(&event) == 1) subMenu = 1;
			if(settings_button.handleEvent(&event) == 1) subMenu = 2;
			if(credits_button.handleEvent(&event) == 1) subMenu = 3;
			if(close_button.handleEvent(&event) == 1) subMenu = 4;
		}

		switch(subMenu){
		case 0:
			break;
		case 1:
			MBUp = 0;
			if(run(&event) == 1) quit = true;
			subMenu = 0;
			break;
		case 2:
			MBUp = 0;
			settings_view(&event);
			subMenu = 0;
			break;
		case 3:
			//MBUp = 0;
			break;
		case 4:
			MBUp = 0;
			quit = true;
			break;
		}
//###############################################  Rendering
		fps.loadFromRenderedText(FPS_text.str().c_str(), textColor);

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear(gRenderer);

		Background.render(2);
		play_button.render();
		settings_button.render();
		credits_button.render();
		close_button.render();
		fps.render(0);

		SDL_RenderPresent(gRenderer);

		frameTime = frameTimer.getTicks();
		if(frameTime < 1000.f / MAX_FPS){
			SDL_Delay(1000.f / (float)MAX_FPS - (float)frameTime);
		}
	}
//###############################################  Gameloop end
	close_SDL();
	return 0;
}

//###############################################  Gameplay function
int run(SDL_Event *event){
	int state = 0;
	int frameTime = 0;
	float FPS = 0;
	bool quit = false;
	SDL_Color textColor = {255, 64, 64, 255};
	stringstream FPS_text;
	Timer frameTimer;
	Texture Background, fps, player_ship, gun_tex;
	Player player;
	vector<Shot*> shots;
	vector<SDL_Rect> aaa;//collision test only
	SDL_Rect col_a = {300, 400, 200, 200};//collision test only
	aaa.push_back(col_a);//collision test only
	if(!Background.loadFromFile("res/Stars_Background.png") ||
		!player_ship.loadFromFile("res/player.png") ||
		!gun_tex.loadFromFile("res/bullet.png") ||
		!player.init(&player_ship, &gun_tex, &shots, (float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT, (float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT, 120))
	{
		cout << "Failed to load resources!" << endl;
		close_SDL();
		return 1;
	}
//###############################################  Set stuff
	player.setCol(0, 0, player.getWidth(), player.getHeight());
//###############################################  Gameloop
	while(!quit){
		frameTime = frameTimer.getTicks();
		frameTimer.start();
		FPS = 1000.f / (float)frameTime;
		FPS_text.str("");
		FPS_text << FPS;
//###############################################  Input handling
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
		fps.loadFromRenderedText(FPS_text.str().c_str(), textColor);
		player.handleEvent(event, frameTime);

		for(unsigned int i = 0; i < shots.size(); i++){
			if(!shots[i]->move(frameTime)){
				delete shots[i];
				shots.erase(shots.begin() + i);
			}
		}
//###############################################  Collission detection
		if(check_col(player.getCol(), &aaa)){
			if(player.colHandle(51)) quit = true;
		}
		for(unsigned int i = 0; i < shots.size(); i++){
			if(check_col(shots[i]->getCol(), &aaa)){
				delete shots[i];
				shots.erase(shots.begin() + i);
			}
		}
//###############################################  Rendering
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear(gRenderer);

		Background.render(2);
		fps.render();
		player.render();

		player_ship.render(1, 300, 400, 0.2, 0.2);//collision test only

		for(unsigned int i = 0; i < shots.size(); i++){
			shots[i]->render();
		}
		SDL_RenderPresent(gRenderer);

		frameTime = frameTimer.getTicks();
		if(frameTime < 1000.f / MAX_FPS){
			SDL_Delay(1000.f / (float)MAX_FPS - (float)frameTime);
		}
	}
//###############################################  Gameloop end
	for(unsigned int i = 0; i < shots.size(); i++){
		delete shots[i];
		shots.erase(shots.begin() + i);
	}
	return state;
}

int settings_view(SDL_Event *event){
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
			if(setResLeft.handleEvent(event) == 1) settings.decrease_resolution();
			if(setResRight.handleEvent(event)) settings.increase_resolution();
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

//###############################################  Initialize SDL
bool init_SDL(){
	SCREEN_WIDTH = 1960;
	SCREEN_HEIGHT = 1080;
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
		cout << "SDL failed to initialize! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
	gWindow = SDL_CreateWindow("Bullethell", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_BORDERLESS);
	if(gWindow == NULL){
		cout << "Failed to create window! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(gRenderer == NULL){
		cout << "Failed to create renderer! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if(!(IMG_Init(imgFlags) & imgFlags)){
		cout << "SDL_image failed to initialize! SDL_image Error: " << IMG_GetError() << endl;
		return false;
	}
	if(TTF_Init() < 0){
		cout << "SDL_TTF failed to initialize! SDL_TTF Error: " << TTF_GetError() << endl;
		return false;
	}
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
		cout << "SDL_mixer failed to initialize! SDL_mixer Error: " << Mix_GetError() << endl;
		return false;
	}
	return true;
}

//###############################################  Close SDL
void close_SDL(){
    //Destroy Window and Renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	//Quit SDL
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
	return;
}














