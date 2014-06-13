#ifndef XMLLOADER_CPP
#define XMLLOADER_CPP

#include "xmlLoader.h"

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

#endif
