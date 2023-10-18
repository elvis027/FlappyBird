#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "../Global/Global.h"
#include "../MenuWindow/MenuWindow.h"
#include "../AboutWindow/AboutWindow.h"
#include "../GameWindow/GameWindow.h"
#include "../ResultWindow/ResultWindow.h"

class Game
{
public:
    Game(void);
    ~Game(void);
    void GamePlay(void);

private:
    Message GameRun(void);
    Message ProcessEvent(void);

    ALLEGRO_DISPLAY* display = nullptr;
    ALLEGRO_EVENT_QUEUE* event_queue = nullptr;

    Window nowWindow;
    MenuWindow* menuWindow = nullptr;
    AboutWindow* aboutWindow = nullptr;
    GameWindow* gameWindow = nullptr;
    ResultWindow* resultWindow = nullptr;

    int mouse_x, mouse_y;
};

#endif // GAME_H_INCLUDED
