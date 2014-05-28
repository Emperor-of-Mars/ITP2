#include "bullethell.h"
#include <fstream>

using namespace std;

Settings::Settings(){
    read_settings();
}

void Settings::read_settings(){
    fstream setts;
    setts.open("settings.dat", fstream::in);
    if(!setts.is_open()){       //die datei ist nicht vorhanden, es werden default-werte verwendet
        available_heights.resize(1);
        available_widths.resize(1);
        available_heights[0] = 600;
        available_widths[0] = 800;
        actual_resolution = 0;
        maximal_resolution = 0;
    }
    else{
        //hier der code zum einlesen der settings
    }
    setts.close();
}

void Settings::write_settings(){
    fstream setts;
    setts.open("settings.dat", fstream::out);
    //hier die funktion zum ausschreiben der settings
    setts.close();
}

void Settings::decrease_resolution(){
    if(actual_resolution > 0){
        actual_resolution--;
    }
}

void Settings::increase_resolution(){
    if(actual_resolution < maximal_resolution){
        actual_resolution++;
    }
}

void Settings::settings_view(SDL_Event *event){

}

int Settings::get_resolution_height(){
    return available_heights[actual_resolution];
}
int Settings::get_resolution_width(){
    return available_widths[actual_resolution];
}


