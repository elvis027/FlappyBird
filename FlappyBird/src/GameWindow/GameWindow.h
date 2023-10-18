#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include "../Global/Global.h"
#include "../Bird/Bird.h"
#include "../Pipe/Pipe.h"

class GameWindow
{
public:
    GameWindow(ALLEGRO_EVENT_QUEUE* eq);
    ~GameWindow(void);

    void Draw(void);
    void Init(void);
    void Fini(void);

    ALLEGRO_TIMER* GetBirdTimer(void);
    ALLEGRO_TIMER* GetTimer(void);
    int GetScore(void);

    void UpdateBirdState(void);
    void UpdateBird(float acceleration, float deltaTime);
    void UpdatePipe(float deltaTime);
    bool isCollided(void);

private:
    bool isCollided(Rect rect1, Rect rect2);

    ALLEGRO_SAMPLE* sample = nullptr;
    ALLEGRO_SAMPLE_INSTANCE* gameSong = nullptr;
    ALLEGRO_BITMAP* background = nullptr;
    ALLEGRO_FONT* scoreFont = nullptr;

    ALLEGRO_EVENT_QUEUE* event_queue = nullptr;
    ALLEGRO_TIMER* timer = nullptr;

    Bird* bird = nullptr;
    Pipe* pipe = nullptr;

    int score;
};

#endif // GAMEWINDOW_H_INCLUDED
