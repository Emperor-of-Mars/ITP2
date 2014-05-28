#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#endif // SETTINGS_H_INCLUDED


//in den settings wird stehen: auflösung aktuell, auflösungen möglich,
class Settings{
    public:
        Settings();
        void settings_view(SDL_Event *event);
        void read_settings();        //lesen der settings aus settings-datei
        void write_settings();       //schreiben der settings in settings-datei
        void decrease_resolution();
        void increase_resolution();
        int get_resolution_height();
        int get_resolution_width();
    private:
        int actual_resolution;
        int maximal_resolution;
        vector<int> available_heights;
        vector<int> available_widths;
};
