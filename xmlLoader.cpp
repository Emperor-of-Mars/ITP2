#ifndef XMLLOADER_CPP
#define XMLLOADER_CPP

#include "xmlLoader.h"

using namespace std;

XmlDocument::XmlDocument(){

}

XmlDocument::~XmlDocument(){

}

bool XmlDocument::init(string location){

    //XML Parser
    result = doc.load_file(location.c_str());

    if(!result){
        cout << "Defined File: " << location << endl;
        cout << result.description() << endl;
        return false;
    }

    //PugiXML - Test
    cout << "Lvl1 name: " << doc.child("level").child_value("name") << endl;
    cout << "Lvl2 name: " << doc.last_child().child_value("name") << endl;
    cout << "Boss life: " << doc.child("level").child("enemies").child("boss").child_value("life") << endl;

    return true;
}

#endif
