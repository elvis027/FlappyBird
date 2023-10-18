#ifndef MENUWINDOW_H_INCLUDED
#define MENUWINDOW_H_INCLUDED

#include "../Global/Global.h"

class MenuWindow
{
public:
    MenuWindow(void);
    ~MenuWindow(void);

    void Draw(void);
    void Init(void);
    void Fini(void);

    SelectedButton GetBtn(int mouse_x, int mouse_y);

private:
    void DrawButton(Button* btn);

    ALLEGRO_SAMPLE* sample = nullptr;
    ALLEGRO_SAMPLE_INSTANCE* menuSong = nullptr;
    ALLEGRO_BITMAP* background = nullptr;
    ALLEGRO_FONT* titleFont = nullptr;
    ALLEGRO_FONT* buttonFont = nullptr;

    Button startButton;
    Button aboutButton;
    Button exitButton;
};

#endif // MENUWINDOW_H_INCLUDED
