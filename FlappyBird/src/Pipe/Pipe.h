#ifndef PIPE_H_INCLUDED
#define PIPE_H_INCLUDED

#include "../Global/Global.h"

class Pipe
{
public:
    Pipe(void);
    ~Pipe(void);

    void Draw(void);
    void Init(void);
    void Fini(void);

    Rect GetUpRect(void);
    Rect GetDownRect(void);

    void UpdatePos(float deltaTime, int& score);

private:
    ALLEGRO_BITMAP* upPipe = nullptr;
    ALLEGRO_BITMAP* downPipe = nullptr;

    float pos_x;
    float up_pos_y, down_pos_y;
    PipeState nowState;

    const int min_y = HEIGHT / 2;
    const int max_y = HEIGHT / 2 + 300;
    const float moveVelocity = 200;
    const float width = 138;
    const float height = 792;
};

#endif // PIPE_H_INCLUDED
