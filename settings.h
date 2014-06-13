#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#endif // SETTINGS_H_INCLUDED

class Settings{
    public:
        Settings();
        int settings_view(SDL_Event *event);
        void read_settings();        //lesen der settings aus settings-datei
        void write_settings();       //schreiben der settings in settings-datei
        void decrease_resolution();
        void increase_resolution();
        int get_resolution_height();
        int get_resolution_width();
        int get_fullscreen();
        void toggle_fullscreen();
    private:
        int actual_resolution;
        int maximal_resolution;
        vector<int> available_heights;
        vector<int> available_widths;
        stringstream res_text;
        Texture *resolution;
        SDL_Color textColor;
        bool settings_found;
        int full_screen;
        string full_screen_string;
};
