#ifndef LEVEL_CPP
#define LEVEL_CPP

#include "level.h"

using namespace std;

Level::Level(){

}

Level::~Level(){

}

bool Level::init(string backgroundlocation, int levelnumber, string levelname){

    name = levelname;
    number = levelnumber;

    if(!Background.loadFromFile(backgroundlocation.c_str())){

        cout << "Couldn't Load Background from " << backgroundlocation << endl;
        return false;
    }

    return true;

}

int Level::getNumber(){
    return number;
}

string Level::getName(){
    return name;
}

Texture* Level::getBackground(){

    Texture* ptr = &Background;

    return ptr;

}

#endif
