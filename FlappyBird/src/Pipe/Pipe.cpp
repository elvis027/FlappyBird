#include "Pipe.h"

Pipe::Pipe(void)
{
    CheckErr(upPipe = al_load_bitmap("resource/img/upPipe.png"), AL_LOAD_BITMAP_ERROR);
    CheckErr(downPipe = al_load_bitmap("resource/img/downPipe.png"), AL_LOAD_BITMAP_ERROR);
}

Pipe::~Pipe(void)
{
    if(upPipe) al_destroy_bitmap(upPipe);
    if(downPipe) al_destroy_bitmap(downPipe);
}

void Pipe::Draw(void)
{
    al_draw_bitmap(upPipe, pos_x, up_pos_y, 0);
    al_draw_bitmap(downPipe, pos_x, down_pos_y, 0);
}

void Pipe::Init(void)
{
    pos_x = WIDTH + 100;
    down_pos_y = rand() % (max_y - min_y + 1) + min_y;
    up_pos_y = down_pos_y - 1100;
    nowState = NotPass;
}

void Pipe::Fini(void)
{

}

Rect Pipe::GetUpRect(void)
{
    return Rect{
        .x = pos_x,
        .y = up_pos_y,
        .width = width,
        .height = height
    };
}

Rect Pipe::GetDownRect(void)
{
    return Rect{
        .x = pos_x,
        .y = down_pos_y,
        .width = width,
        .height = height
    };
}

void Pipe::UpdatePos(float deltaTime, int& score)
{
    if(nowState == NotPass) {
        if(pos_x < WIDTH / 2 - 50)
            nowState = Passed;
    }
    else if(nowState == Passed) {
        score++;
        nowState = Dumped;
    }

    pos_x -= deltaTime * moveVelocity;

    if(pos_x < -150)
        Init();
}
