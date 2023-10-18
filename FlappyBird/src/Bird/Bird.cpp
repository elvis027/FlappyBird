#include "Bird.h"

Bird::Bird(ALLEGRO_EVENT_QUEUE* eq)
{
    event_queue = eq;

    // Load the SFX
    CheckErr(sample = al_load_sample("resource/audio/jump.wav"), AL_LOAD_SAMPLE_ERROR);
    CheckErr(birdSFX = al_create_sample_instance(sample), AL_CREATE_SAMPLE_INSTANCE_ERROR);
    CheckErr(al_set_sample_instance_playmode(birdSFX, ALLEGRO_PLAYMODE_ONCE), AL_SET_SAMPLE_INSTANCE_PLAYMODE_ERROR);
    CheckErr(al_attach_sample_instance_to_mixer(birdSFX, al_get_default_mixer()), AL_ATTACH_SAMPLE_INSTANCE_TO_MIXER_ERROR);

    CheckErr(bird[0] = al_load_bitmap("resource/img/bird1.png"), AL_LOAD_BITMAP_ERROR);
    CheckErr(bird[1] = al_load_bitmap("resource/img/bird2.png"), AL_LOAD_BITMAP_ERROR);
    CheckErr(bird[2] = al_load_bitmap("resource/img/bird3.png"), AL_LOAD_BITMAP_ERROR);

    CheckErr(timer = al_create_timer(0.05), AL_CREATE_TIMER_ERROR);
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
}

Bird::~Bird(void)
{
    if(sample) al_destroy_sample(sample);
    if(birdSFX) al_destroy_sample_instance(birdSFX);
    if(bird[0]) al_destroy_bitmap(bird[0]);
    if(bird[1]) al_destroy_bitmap(bird[1]);
    if(bird[2]) al_destroy_bitmap(bird[2]);
    if(timer) al_destroy_timer(timer);
}

void Bird::Draw(void)
{
    al_draw_bitmap(bird[nowState], pos_x, pos_y, 0);
}

void Bird::Init(void)
{
    al_start_timer(timer);

    nowState = 1;
    dir = 1;
    UpdatePos(G, 0);
}

void Bird::Fini(void)
{
    al_stop_timer(timer);
}

ALLEGRO_TIMER* Bird::GetTimer(void)
{
    return timer;
}

Rect Bird::GetRect(void)
{
    return Rect{
        .x = pos_x,
        .y = pos_y,
        .width = width,
        .height = height
    };
}

void Bird::UpdateState(void)
{
    nowState += dir;
    if(nowState == 2)
        dir = -1;
    else if(nowState == 0)
        dir = 1;
}

void Bird::UpdatePos(float acceleration, float deltaTime)
{
    if(deltaTime <= 1e-6) {
        velocity = 0;
        pos_x = WIDTH / 2;
        pos_y = HEIGHT / 2;
    }
    else {
        if(acceleration == H)
            CheckErr(al_play_sample_instance(birdSFX), AL_PLAY_SAMPLE_INSTANCE_ERROR);
        pos_y += velocity * deltaTime + 0.5 * acceleration * deltaTime * deltaTime;
        velocity += acceleration * deltaTime;
    }
}
