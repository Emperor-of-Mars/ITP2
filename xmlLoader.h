#ifndef XMLLOADER_H
#define XMLLOADER_H

#include "./pugixml/pugixml.hpp"
#include "./pugixml/pugiconfig.hpp"
#include <iostream>

using namespace std;

class XmlDocument{

    public:
        XmlDocument();
        ~XmlDocument();
        bool init(string location);

    private:
        string location;
        pugi::xml_document doc;
        pugi::xml_parse_result result;

};

#endif
