#include "GameWindow.h"

GameWindow::GameWindow(ALLEGRO_EVENT_QUEUE* eq)
{
    event_queue = eq;

    // Load the song
    CheckErr(sample = al_load_sample("resource/audio/game.mp3"), AL_LOAD_SAMPLE_ERROR);
    CheckErr(gameSong = al_create_sample_instance(sample), AL_CREATE_SAMPLE_INSTANCE_ERROR);
    CheckErr(al_set_sample_instance_playmode(gameSong, ALLEGRO_PLAYMODE_LOOP), AL_SET_SAMPLE_INSTANCE_PLAYMODE_ERROR);
    CheckErr(al_attach_sample_instance_to_mixer(gameSong, al_get_default_mixer()), AL_ATTACH_SAMPLE_INSTANCE_TO_MIXER_ERROR);

    // Load the playground
    CheckErr(background = al_load_bitmap("resource/img/background.png"), AL_LOAD_BITMAP_ERROR);

    // Load the title font
    CheckErr(scoreFont = al_load_ttf_font("resource/font/pirulen.ttf", 30, 0), AL_LOAD_TTF_FONT_ERROR);

    CheckErr(timer = al_create_timer(1.0 / FPS), AL_CREATE_TIMER_ERROR);
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    bird = new Bird(event_queue);
    pipe = new Pipe();

    score = 0;
}

GameWindow::~GameWindow(void)
{
    if(sample) al_destroy_sample(sample);
    if(gameSong) al_destroy_sample_instance(gameSong);
    if(background) al_destroy_bitmap(background);
    if(scoreFont) al_destroy_font(scoreFont);
    if(timer) al_destroy_timer(timer);
    if(bird) delete bird;
    if(pipe) delete pipe;
}

void GameWindow::Draw(void)
{
    // Draw the background
    al_draw_bitmap(background, 0, 0, 0);

    pipe->Draw();

    bird->Draw();

    // Draw the score
    char str[5];
    sprintf(str, "%d", score);
    al_draw_text(scoreFont, al_map_rgb(102, 34, 0), WIDTH / 2, 100,
                    ALLEGRO_ALIGN_CENTER, str);

    // Show
    al_flip_display();
}

void GameWindow::Init(void)
{
    al_start_timer(timer);
    CheckErr(al_play_sample_instance(gameSong), AL_PLAY_SAMPLE_INSTANCE_ERROR);

    score = 0;
    bird->Init();
    pipe->Init();
}

void GameWindow::Fini(void)
{
    al_stop_timer(timer);
    CheckErr(al_stop_sample_instance(gameSong), AL_STOP_SAMPLE_INSTANCE_ERROR);

    bird->Fini();
    pipe->Fini();
}

ALLEGRO_TIMER* GameWindow::GetBirdTimer(void)
{
    return bird->GetTimer();
}

ALLEGRO_TIMER* GameWindow::GetTimer(void)
{
    return timer;
}

int GameWindow::GetScore(void)
{
    return score;
}

void GameWindow::UpdateBirdState(void)
{
    bird->UpdateState();
}

void GameWindow::UpdateBird(float acceleration, float deltaTime)
{
    bird->UpdatePos(acceleration, deltaTime);
}

void GameWindow::UpdatePipe(float deltaTime)
{
    pipe->UpdatePos(deltaTime, score);
}

bool GameWindow::isCollided(void)
{
    Rect rectBird = bird->GetRect();
    Rect rectUpPipe = pipe->GetUpRect();
    Rect rectDownPipe = pipe->GetDownRect();
    bool judge = rectBird.y <= 0 || (rectBird.y + rectBird.height >= HEIGHT);
    return isCollided(rectBird, rectUpPipe) || isCollided(rectBird, rectDownPipe) || judge;
}

bool GameWindow::isCollided(Rect rect1, Rect rect2)
{
    if(rect1.x + rect1.width < rect2.x)
        return false;
    if(rect2.x + rect2.width < rect1.x)
        return false;
    if(rect1.y + rect1.height < rect2.y)
        return false;
    if(rect2.y + rect2.height < rect1.y)
        return false;
    return true;
}
