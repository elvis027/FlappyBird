#ifndef Bird_H_INCLUDED
#define Bird_H_INCLUDED

#include "../Global/Global.h"

class Bird
{
public:
    Bird(ALLEGRO_EVENT_QUEUE* eq);
    ~Bird(void);

    void Draw(void);
    void Init(void);
    void Fini(void);

    ALLEGRO_TIMER* GetTimer(void);
    Rect GetRect(void);

    void UpdateState(void);
    void UpdatePos(float acceleration, float deltaTime);

private:
    ALLEGRO_SAMPLE* sample = nullptr;
    ALLEGRO_SAMPLE_INSTANCE* birdSFX = nullptr;
    ALLEGRO_BITMAP* bird[3] = {nullptr, nullptr, nullptr};
    ALLEGRO_EVENT_QUEUE* event_queue = nullptr;
    ALLEGRO_TIMER* timer = nullptr;

    int dir;
    int nowState;
    float velocity;
    float pos_x, pos_y;
    const float width = 92;
    const float height = 64;
};

#endif // Bird_H_INCLUDED
