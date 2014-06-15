#ifndef XMLLOADER_CPP
#define XMLLOADER_CPP

#include <limits>
#include "xmlLoader.h"
#include "enemy.h"

using namespace std;

XmlDocument::XmlDocument(){

}

XmlDocument::~XmlDocument(){

}

bool XmlDocument::init(string location){

    result = doc.load_file(location.c_str());

    if(!result){
        cout << "Defined File: " << location << endl;
        cout << result.description() << endl;
        return false;
    }

    int levelnumber = 1;

    for (pugi::xml_node level = doc.first_child(); level; level = level.next_sibling()) {

        Level* lvl = new Level();
        Levels.push_back(lvl);

        for (pugi::xml_node enemy = level.child("enemies").first_child(); enemy; enemy = enemy.next_sibling()) {

            int maxVel, mLife;


            //DEBUG
            cout << "Enemy debug: " << enemy.name() << endl;



            if(strcmp(enemy.value(), "enemy")){

                mLife = strtol(enemy.child_value("life"), NULL, 10);
                maxVel = strtol(enemy.child_value("speed"), NULL, 10);

                Enemy* newenemy = new Enemy;
                Enemies.push_back(newenemy);

                Texture* enemysprite = new Texture;
                enemysprite->loadFromFile(enemy.child_value("sprite"));
                Texture* bulletsprite = new Texture;
                bulletsprite->loadFromFile(enemy.child_value("bulletsprite"));

                if(!newenemy->init(enemysprite, bulletsprite, (float)SCREEN_WIDTH / BASE_SCREEN_WIDTH,
                            (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT,
                            (float)SCREEN_WIDTH / BASE_SCREEN_WIDTH,
                            (float)SCREEN_HEIGHT / BASE_SCREEN_HEIGHT, mLife, maxVel, 20)){

                                cout << "Failed initiating enemy" << endl;
                                return false;

                            }

            }

        }


        if(!lvl->init(level.child_value("background"), levelnumber, level.child_value("name"), Enemies)){
            cout << "Couldn't initate Level" << endl;
            return false;
        }

        levelnumber++;
        Enemies.clear();
    }

    //DEBUGAUSGABE
    for(unsigned int i = 0; i < Levels.size(); i++){
        cout << Levels[i]->getName() << endl;
    }
    //DEBUGAUSGABE ENDE

    return true;
}

vector<Level* > XmlDocument::getLevels(){

    return Levels;
}

vector<Enemy* > XmlDocument::getEnemies(){

    return Enemies;
}

XmlHighscore::XmlHighscore() {

}

XmlHighscore::~XmlHighscore() {

}

bool XmlHighscore::init(string location){

    result = doc.load_file(location.c_str());

    if(!result){
        cout << "Defined File: " << location << endl;
        cout << result.description() << endl;
        return false;
    }
    return true;
}

void XmlHighscore::showScore(){
    int scorenumber = 0;
    int maxscore = numeric_limits<int>::max();
    int minscore = 0;
    int value = 0;

    for (scorenumber = 0; scorenumber<10; scorenumber++) {
        for (pugi::xml_node score = doc.first_child(); score; score = score.next_sibling()) {
            value = atoi(score.value());
            if(minscore <= value && minscore < maxscore) minscore = value;
        }
    if (maxscore > minscore) maxscore = minscore;
    scorenumber++;
    }
}

void XmlHighscore::writeScore(string location, int score){
    pugi::xml_node newsc = doc.append_child("score");
    newsc.append_child(pugi::node_pcdata).text().set(score);
    doc.save_file(location.c_str());
}
#endif
