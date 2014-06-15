/*
 * Author: Erik Skalla, Stefan Reinhold, Samuel Wambera, Martin Schwarz
 * Created: 01.05.2014
 * Last change: 01.05.2014 20:16
 * Purpose: Main Function
 */

#include "bullethell.h"
#include "settings.h"
#include "player.h"
#include "credits.h"
#include "xmlLoader.h"
#include "level.h"
#include "levelselection.h"

using namespace std;

int run(SDL_Event *event, Level* lvl);

int SCREEN_WIDTH = 0;
int SCREEN_HEIGHT = 0;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;
Settings *settings = NULL;
vector<Level* > Levels;

//###############################################  Main
int main(int argc, char *argv[]){
	SDL_Event event;
	int frameTime = 0, subMenu = 0, MBUp = 1;
	//float FPS = 0;
	bool quit = false;
	//stringstream FPS_text;
	settings = new Settings;
	SCREEN_HEIGHT = settings->get_resolution_height();
	SCREEN_WIDTH = settings->get_resolution_width();

    XmlDocument levelsxml;
	Timer frameTimer;
	Credits credits;
	Levelselection lvlselect;
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
		!close_button.init(&buttonTexture, 225, "Close", textColor) ||
        !levelsxml.init("res/levels.xml"))
	{
		cout << "Failed to load resources!" << endl;
		close_SDL();
		return 1;
	}
//###############################################  Set stuff

    Levels = levelsxml.getLevels();
	buttonTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	play_button.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	settings_button.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	credits_button.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	close_button.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	Background.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	play_button.setPosition(SCREEN_WIDTH * 0.5 - play_button.getWidth() / 2, SCREEN_HEIGHT * 0.2 - play_button.getHeight() / 2);
	settings_button.setPosition(SCREEN_WIDTH * 0.5 - settings_button.getWidth() / 2, SCREEN_HEIGHT * 0.4 - settings_button.getHeight() / 2);
	credits_button.setPosition(SCREEN_WIDTH * 0.5 - credits_button.getWidth() / 2, SCREEN_HEIGHT * 0.6 - credits_button.getHeight() / 2);
	close_button.setPosition(SCREEN_WIDTH * 0.5 - close_button.getWidth() / 2, SCREEN_HEIGHT * 0.8 - close_button.getHeight() / 2);
	//fps.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	PlayVideo();
//###############################################  Gameloop
	while(!quit){
		frameTime = frameTimer.getTicks();
		frameTimer.start();
		//FPS = 1000.f / (float)frameTime;
		//FPS_text.str("");
		//FPS_text << FPS;
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
        while(SDL_PollEvent(&event)){}
		switch(subMenu){
		case 0:
			break;
		case 1:
			MBUp = 0;
//			lvlselect.levelselection_view(&event);
			if(run(&event, Levels[0]) == 1) quit = true;
			subMenu = 0;
			break;
		case 2:
			MBUp = 0;
			settings->settings_view(&event);
			subMenu = 0;
			break;
		case 3:
			MBUp = 0;
			credits.credits_view(&event);
			subMenu = 0;
			break;
		case 4:
			MBUp = 0;
			quit = true;
			break;
		}
//###############################################  Rendering
		//fps.loadFromRenderedText(FPS_text.str().c_str(), textColor);

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear(gRenderer);

		Background.render(2);
		play_button.render();
		settings_button.render();
		credits_button.render();
		close_button.render();
		//fps.render(0);

		SDL_RenderPresent(gRenderer);

		frameTime = frameTimer.getTicks();
		if(frameTime < 1000.f / MAX_FPS){
			SDL_Delay(1000.f / (float)MAX_FPS - (float)frameTime);
		}
	}
//###############################################  Gameloop end
	close_SDL();
	settings->write_settings();
	return 0;
}

//###############################################  Gameplay function
int run(SDL_Event *event, Level* lvl){
	int state = 0;
	int frameTime = 0;
	//float FPS = 0;
	bool quit = false;
	//SDL_Color textColor = {255, 64, 64, 255};
	//stringstream FPS_text;
	Timer frameTimer;
	Texture fps, player_ship, gun_tex, collision_temp;
	Texture* Background;
	Player player;
	vector<Shot*> shots;
	vector<SDL_Rect> aaa;//collision test only
	SDL_Rect col_a = {400, 200, 200, 200};//collision test only
	aaa.push_back(col_a);//collision test only
	Background = lvl->getBackground();
	if(!Background ||
		!player_ship.loadFromFile("res/player.png") ||
		!gun_tex.loadFromFile("res/bullet.png") ||
		!collision_temp.loadFromFile("res/werbung.png") ||
		!player.init(&player_ship, &gun_tex, &shots, (float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT, (float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT, 100, 20))
	{
		cout << "Failed to load resources!" << endl;
		close_SDL();
		return 1;
	}
//###############################################  Set stuff
	player.setCol(player.getWidth() * 0.15, player.getHeight() * 0.1, player.getWidth() * 0.7, player.getHeight() * 0.6);
	//Background->setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
//###############################################  Gameloop
	while(!quit){
		frameTime = frameTimer.getTicks();
		frameTimer.start();
		//FPS = 1000.f / (float)frameTime;
		//FPS_text.str("");
		//FPS_text << FPS;
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
		//fps.loadFromRenderedText(FPS_text.str().c_str(), textColor);
		player.handleEvent(event, frameTime);

		for(unsigned int i = 0; i < shots.size(); i++){
			if(!shots[i]->move(frameTime)){
				delete shots[i];
				shots.erase(shots.begin() + i);
			}
		}
//###############################################  Collission detection
		if(check_col(player.getCol(), &aaa)){       //aaa is im prinzip der gegner im mom (einfach ein rect)
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

		Background->render(2);
		//fps.render();
		player.render();

		collision_temp.render(1, 400, 200, 1, 1);//collision test only

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

//###############################################  Initialize SDL
bool init_SDL(){
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
		cout << "SDL failed to initialize! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
	gWindow = SDL_CreateWindow("Bullethell", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_MINIMIZED);
	if(settings->get_fullscreen() == 1) SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else SDL_SetWindowFullscreen(gWindow, 0);
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

void PlayVideo(){
	return;
}

bool check_col(vector<SDL_Rect> *col1, vector<SDL_Rect> *col2){     //die funktion zur collision-detection
	for(unsigned int i = 0; i < col1->size(); i++){
		for(unsigned int j = 0; j < col2->size(); j++){
			if(((*col1)[i].x + (*col1)[i].w) < (*col2)[j].x) return false;
			if((*col1)[i].x > ((*col2)[j].x + (*col2)[j].w)) return false;
			if(((*col1)[i].y + (*col1)[i].h) < (*col2)[j].y) return false;
			if((*col1)[i].y > (*col2)[j].y + (*col2)[j].h) return false;
		}
	}
	return true;
}










