#ifndef XMLLOADER_CPP
#define XMLLOADER_CPP

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

            int maxVel, mLife, mWidth, mHeight, mXpos, mYpos, SpritePos[2], BulletFired;


            //DEBUG
            cout << "Enemy debug: " << enemy.name() << endl;



            if(enemy.value() == "enemy"){

                mLife = strtol(enemy.child_value("life"), NULL, 10);
                maxVel = strtol(enemy.child_value("speed"), NULL, 10);

                Enemy* newenemy = new Enemy;
                Enemies.push_back(newenemy);

                Texture* enemysprite = new Texture;
                enemysprite->loadFromFile(enemy.child_value("sprite"));


                //newenemy->init(enemysprite);


            }


        }

        if(!lvl->init(level.child_value("background"), levelnumber, level.child_value("name"))){
            cout << "Couldn't initate Level" << endl;
            return false;
        }

        levelnumber++;
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

#endif
