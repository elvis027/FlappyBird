#ifndef ABOUTWINDOW_H_INCLUDED
#define ABOUTWINDOW_H_INCLUDED

#include "../Global/Global.h"

class AboutWindow
{
public:
    AboutWindow(void);
    ~AboutWindow(void);

    void Draw(void);
    void Init(void);
    void Fini(void);

private:
    ALLEGRO_BITMAP* background = nullptr;
    ALLEGRO_FONT* titleFont = nullptr;
    ALLEGRO_FONT* textFont = nullptr;
};

#endif // ABOUTWINDOW_H_INCLUDED
