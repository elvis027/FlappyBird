#ifndef RESULTWINDOW_H_INCLUDED
#define RESULTWINDOW_H_INCLUDED

#include "../Global/Global.h"

class ResultWindow
{
public:
    ResultWindow(void);
    ~ResultWindow(void);

    void Draw(int score);
    void Init(void);
    void Fini(void);

    SelectedButton GetBtn(int mouse_x, int mouse_y);

private:
    void DrawButton(Button* btn);

    ALLEGRO_SAMPLE* sample = nullptr;
    ALLEGRO_SAMPLE_INSTANCE* resultSong = nullptr;
    ALLEGRO_BITMAP* background = nullptr;
    ALLEGRO_FONT* scoreFont = nullptr;
    ALLEGRO_FONT* buttonFont = nullptr;

    Button restartButton;
    Button backButton;
};

#endif // RESULTWINDOW_H_INCLUDED
