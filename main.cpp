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
#include "explosion.h"
#include "highscores.h"

using namespace std;

int run(SDL_Event *event, Level* lvl);

int SCREEN_WIDTH = 0;
int SCREEN_HEIGHT = 0;
int LEFT_SCREEN_WIDTH;
int RIGHT_SCREEN_WIDTH;
float SCREENSCALE_X = 0;
float SCREENSCALE_Y = 0;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;
Settings *settings = NULL;
XmlHighscore *highsxml = NULL;
vector<Level* > Levels;


//###############################################  Main
int main(int argc, char *argv[]){
	SDL_Event event;
	int frameTime = 0, subMenu = 0;
	bool quit = false;
	int level = -1;             //zur levelauswahl zum speichern des rückgabewerts von levelselection
	settings = new Settings;
	SCREEN_HEIGHT = settings->get_resolution_height();
	SCREEN_WIDTH = settings->get_resolution_width();
	LEFT_SCREEN_WIDTH = SCREEN_WIDTH/32*7;
	RIGHT_SCREEN_WIDTH = SCREEN_WIDTH - SCREEN_WIDTH/32*7;
	SCREENSCALE_X = SCREEN_WIDTH / BASE_SCREEN_WIDTH;
	SCREENSCALE_Y = SCREEN_HEIGHT / BASE_SCREEN_HEIGHT;

	Timer frameTimer;
	Credits credits;
	Highscores highscores;
	Levelselection lvlselect;
	highsxml = new XmlHighscore();
	XmlDocument *levelsxml = NULL;
	Texture buttonTexture, fps, Background;
	Button play_button, settings_button, highscores_button, credits_button, close_button;
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
        !highscores_button.init(&buttonTexture, 225, "Highscores", textColor) ||
		!credits_button.init(&buttonTexture, 225, "Credits", textColor) ||
		!close_button.init(&buttonTexture, 225, "Close", textColor) ||
        !highsxml->init("res/highscores.xml"))
	{
		cout << "Failed to load resources!" << endl;
		close_SDL();
		return 1;
	}
//###############################################  Set stuff




	buttonTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	play_button.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	settings_button.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	highscores_button.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	credits_button.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	close_button.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	Background.setScale((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
	play_button.setPosition(SCREEN_WIDTH * 0.5 - play_button.getWidth() / 2, SCREEN_HEIGHT * 0.1 - play_button.getHeight() / 2);
	settings_button.setPosition(SCREEN_WIDTH * 0.5 - settings_button.getWidth() / 2, SCREEN_HEIGHT * 0.3 - settings_button.getHeight() / 2);
	highscores_button.setPosition(SCREEN_WIDTH * 0.5 - settings_button.getWidth() / 2, SCREEN_HEIGHT * 0.5 - settings_button.getHeight() / 2);
	credits_button.setPosition(SCREEN_WIDTH * 0.5 - credits_button.getWidth() / 2, SCREEN_HEIGHT * 0.7 - credits_button.getHeight() / 2);
	close_button.setPosition(SCREEN_WIDTH * 0.5 - close_button.getWidth() / 2, SCREEN_HEIGHT * 0.9 - close_button.getHeight() / 2);
//###############################################  Gameloop
	while(!quit){
		frameTime = frameTimer.getTicks();
		frameTimer.start();
		while(SDL_PollEvent(&event) != 0){
			if(event.type == SDL_QUIT)quit = true;
			else if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
				case SDLK_q:
					quit = true;
					break;
				}
			}
		}                                         //welcher button angeklickt wurde
        if(play_button.handleEvent(&event) == 1) subMenu = 1;
        if(settings_button.handleEvent(&event) == 1) subMenu = 2;
        if(credits_button.handleEvent(&event) == 1) subMenu = 3;
        if(close_button.handleEvent(&event) == 1) subMenu = 4;
        if(highscores_button.handleEvent(&event) == 1) subMenu = 5;
        while(SDL_PollEvent(&event)){}
		switch(subMenu){
		case 0:
			break;
		case 1:

            levelsxml = new XmlDocument;

            if(!levelsxml->init("res/levels.xml")){
                cout << "Failed to load resources!" << endl;
                close_SDL();
                return 1;
            }

            Levels = levelsxml->getLevels();

			delete levelsxml;

			level = lvlselect.levelselection_view(&event, Levels.size());
			if(run(&event, Levels[level]) == 1) quit = true;
			subMenu = 0;
			break;
		case 2:
			settings->settings_view(&event);
			subMenu = 0;
			break;
		case 3:
			credits.credits_view(&event);
			subMenu = 0;
			break;
		case 4:
			quit = true;
			break;
        case 5:
			highscores.highscores_view(&event, highsxml);
			subMenu = 0;
			break;
		}
//###############################################  Rendering
		//fps.loadFromRenderedText(FPS_text.str().c_str(), textColor);

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear(gRenderer);

		Background.render(2);
		play_button.render();
		settings_button.render();
		highscores_button.render();
		credits_button.render();
		close_button.render();

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
    cout << "in run gegangen" << endl;
	int state = 0;
	int frameTime = 0;
	bool quit = false;
    int scrollingOffset = 0;
	//Textausgabe
    //float sx = round(SCREEN_WIDTH/BASE_SCREEN_WIDTH); //euivalent 0.711111111111111111 bei 768 hoehe
	stringstream life;
	stringstream score;
	SDL_Color textColor = {255, 64, 64, 255};
	vector<Shot*> enemyshots;

	Timer frameTimer, enemy_shoot;
	Texture str1, str2, player_ship, gun_tex, border1, border2;
	Texture* Background;
	Player *player = new Player;
	vector<Shot*> shots;
	vector<Enemy* > Enemies;
	vector<Explosion* > Explosions;
	Background = lvl->getBackground();
	if(!Background ||
        !border1.loadFromFile("res/Border.png")||
        !border2.loadFromFile("res/Border.png")||
		!player_ship.loadFromFile("res/player_01.png") ||
		!gun_tex.loadFromFile("res/Bullet_01.png") ||
		!player->init(&player_ship, &gun_tex, &shots, (float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT, (float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT, 100, 20))
	{
		cout << "Failed to load resources!" << endl;
		close_SDL();
		return 1;
	}
//###############################################  Set stuff

    Enemies = lvl->getEnemies();
    if(Enemies[0]){
        for(unsigned int i = 0; i < Enemies.size(); i++){
            Enemies[i]->setCol(Enemies[i]->getX(), Enemies[i]->getY(), Enemies[i]->getWidth(), Enemies[i]->getHeight());
        }
    }

    vector<Texture* > Boomanimation;

    stringstream file;
	string num;
	int framecounter = 1;

	while(1){

        Texture* frame = new Texture;
        file << framecounter;
        file >> num;
        file.str("");
        file.clear();
        while(num.size() < 4) num.insert(0, "0");
        file << "res/Explosion/" << num << ".png";
        cout << file.str() << endl;
        if(!frame->loadFromFile(file.str().c_str())) break;
        Boomanimation.push_back(frame);

        file.str("");
		num = "";
		file.clear();
        framecounter++;
	}

    enemy_shoot.start();

    cout << "vor while in run" << endl;
//###############################################  Gameloop
    scrollingOffset = 0;
	while(!quit){
		frameTime = frameTimer.getTicks();
		frameTimer.start();
		life.str("");
        life << "Leben: " << player->getLife();
		score.str("");
		score << "Score: " << player->getScore();
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

		str1.loadFromRenderedText(life.str().c_str(), textColor);
		str2.loadFromRenderedText(score.str().c_str(), textColor);
		str1.setScale(((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH) * 1.2, ((float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT) * 1.2);
		str2.setScale(((float)SCREEN_WIDTH / BASE_SCREEN_WIDTH) * 1.2, ((float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT) * 1.2);
		str1.setPosition(SCREEN_WIDTH * 0.05, SCREEN_HEIGHT * 0.1);
		str2.setPosition(SCREEN_WIDTH * 0.05, SCREEN_HEIGHT * 0.2);
		player->handleEvent(event, frameTime);

        if(enemy_shoot.getTicks() > 1000){
            for(unsigned int i = 0; i < Enemies.size(); i++){       //alle enemies schießen lassen
                Enemies[i]->shoot();
            }
            enemy_shoot.start();
        }

        cout << "gegner bewegen" << endl;
        for(unsigned int i = 0; i < Enemies.size(); i++){       //gegner bewegen
            if(Enemies[i]->movement(frameTime)){
	            delete Enemies[i];
				Enemies.erase(Enemies.begin() + i);
				i--;
				continue;
            }
        }

        cout << "bewegen der schüsse: " << endl;
		for(int i = 0; i < (int)shots.size(); i++){         //bewegen der schüsse
			cout << i << endl;
			if(!shots[i]->move(frameTime)){   //wenn eine 0 zurückkommt, heißt das, der schuss ist aus dem spielfeld raus -> schuss wird gelöscht
                cout << "shot out of screen: " << i << endl;
				delete shots[i];
				shots.erase(shots.begin() + i);
				i--;
			}
		}

        cout << "bewegen der enemyschüsse" << endl;
		for(int i = 0; i < (int)Enemies.size(); i++){
            enemyshots = Enemies[i]->getShots();
            for(int j = 0; j < (int)enemyshots.size(); j++){
                cout << "shot: " << j << "from enemy: " << i << endl;
                if(!enemyshots[j]->move(frameTime)){   //wenn eine 0 zurückkommt, heißt das, der schuss ist aus dem spielfeld raus -> schuss wird gelöscht
                    Enemies[i]->delShot(j);
                    break;
                }
            }
		}
//###############################################  Collission detection
        //cout << "coll player gegner" << endl;
		for(unsigned int i = 0; i < Enemies.size(); i++){           //collision-detection für kollision zwischen player und gegner
            if(check_col(player->getCol(), Enemies[i]->getCol())){
                if(player->colHandle(true)) quit = true;
                if(Enemies[i]->colHandle(50,player)){
                    cout << "collision zwischen player und enemy: " << i << endl;
                    Explosions.push_back(Enemies[i]->explode());
                    delete Enemies[i];
                    Enemies.erase(Enemies.begin() + i);
                    break;
                }
            }
        }

        //cout << "coll schuss von player" << endl;
		for(unsigned int i = 0; i < shots.size(); i++){             //collision-detection für schuß von player
            for(unsigned int j = 0; j < Enemies.size(); j++){
                if(check_col(shots[i]->getCol(), Enemies[j]->getCol())){
                    cout << "schuss: " << i << " hat gegner: " << j << " getroffen" << endl;
                    Explosions.push_back(shots[i]->explode());
                    delete shots[i];
                    shots.erase(shots.begin() + i);
                    if(Enemies[j]->colHandle(5, player)){
                        Explosions.push_back(Enemies[j]->explode());
                        delete Enemies[j];
                        Enemies.erase(Enemies.begin() + j);
                    }
                    cout << "shot collision with enemy: " << i << endl;
                    break;
                }
            }
		}
        cout << "coll schuss von gegner" << endl;
        for(int i = 0; i < (int)Enemies.size(); i++){
            enemyshots = Enemies[i]->getShots();
            for(int j = 0; j < (int)enemyshots.size(); j++){
                cout << "shot: " << j << "from enemy: " << i << endl;
                if(check_col(enemyshots[j]->getCol(), player->getCol())){
                    cout << "schuss hat player getroffen: " << j << endl;
                    Enemies[i]->delShot(j);
                    if(player->colHandle(false)) quit = true;
                    break;
                }
            }
		}
//###############################################  Rendering
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear(gRenderer);
        cout << "rendering: 1";
		Background->render(1,0,scrollingOffset - SCREEN_HEIGHT, (float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
		Background->render(1,0,scrollingOffset, (float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
		border1.render(1,0,0,(float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
		border2.render(1,RIGHT_SCREEN_WIDTH,0,(float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
		player->render();
		cout << " 2 ";
        for(unsigned int i = 0; i < Enemies.size(); i++){
            Enemies[i]->render();
        }
        cout << " 3 ";
		for(unsigned int i = 0; i < shots.size(); i++){
			shots[i]->render();
		}
        cout << " 4 ";
		for(int i = 0; i < (int)Enemies.size(); i++){
            enemyshots = Enemies[i]->getShots();
            for(int j = 0; j < (int)enemyshots.size(); j++){
                enemyshots[j]->render();
            }
		}
        cout << " 5 ";
		for(unsigned int i = 0; i < Explosions.size(); i++){
            if(!Explosions[i]->render(&Boomanimation)){
                delete Explosions[i];
                Explosions.erase(Explosions.begin()+i);
                i--;
            }
		}
		border1.render(1,0,0,(float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
		border2.render(1,RIGHT_SCREEN_WIDTH,0,(float)SCREEN_WIDTH / BASE_SCREEN_WIDTH, (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT);
		str1.render();
		str2.render();

		SDL_RenderPresent(gRenderer);

		frameTime = frameTimer.getTicks();
		if(frameTime < 1000.f / MAX_FPS){
			SDL_Delay(1000.f / (float)MAX_FPS - (float)frameTime);
		}
		cout << "nach rendering" << endl;
    if (scrollingOffset<SCREEN_HEIGHT) scrollingOffset++;
    else scrollingOffset = 0;
	}
//###############################################  Gameloop end
    highsxml->writeScore("res/highscores.xml", player->getScore());

    //aufräumen

    cout << "aufräumen" << endl;
	while(shots.size() > 0){
        delete shots[0];
		shots.erase(shots.begin());
	}
	while(Levels.size() > 0){
        delete Levels[0];
        Levels.erase(Levels.begin());
	}
	return state;
}

//###############################################  Initialize SDL
bool init_SDL(){
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
		cout << "SDL failed to initialize! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
	Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;//flags for SDL_CreateWindow
	if(settings->get_fullscreen() == 1) flags = flags | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS;//add fullscreen flags if set
	gWindow = SDL_CreateWindow("Bullethell", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);
	//if(settings->get_fullscreen() == 1) SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	//else SDL_SetWindowFullscreen(gWindow, 0);
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

	//vector<Enemy* > Enemies;

    /*for(unsigned int i = 0; i < Levels.size(); i++){

        Enemies = Levels[i]->getEnemies();

        while(Enemies.size() > 0){
            delete Enemies[0];
            Enemies.erase(Enemies.begin());
        }

        delete Levels[i];
    }*/
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
	Texture frame;
	stringstream file;
	string num;
	int frameTime = 0;
	Timer frameTimer, tim;
	tim.start();
	int i = 10;
	while(1){
		frameTimer.start();
		file << i;
		file >> num;
		file.str("");
		file.clear();
		while(num.size() < 4) num.insert(0, "0");
		file << "res/Introsequenz/" << num << ".jpg";
		//cout << file.str() << endl;
		if(!frame.loadFromFile(file.str().c_str())) break;
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear(gRenderer);
		frame.render(2);
		SDL_RenderPresent(gRenderer);
		file.str("");
		num = "";
		file.clear();
		i++;
		frameTime = frameTimer.getTicks();
		if(frameTime < 1000.f / 25){
			//cout << 1000.f / (float)25 - (float)frameTime << endl;
			SDL_Delay(1000.f / (float)25 - (float)frameTime);
		}
	}
	//cout << tim.getTicks() << endl;
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










