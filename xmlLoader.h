#ifndef XMLLOADER_H
#define XMLLOADER_H

#include "./pugixml/pugixml.hpp"
#include "./pugixml/pugiconfig.hpp"
#include "bullethell.h"
#include "level.h"

using namespace std;

class XmlDocument{

    public:
        XmlDocument();
        ~XmlDocument();
        bool init(string location);
        vector<Level* > getLevels();
        vector<Enemy* > getEnemies();

    private:
        string location;
        pugi::xml_document doc;
        pugi::xml_parse_result result;
        vector<Level* > Levels;
        vector<Enemy* > Enemies;
};

#endif
