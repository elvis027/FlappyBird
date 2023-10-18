#include "ResultWindow.h"

ResultWindow::ResultWindow(void)
{
    // Load the song
    CheckErr(sample = al_load_sample("resource/audio/result.mp3"), AL_LOAD_SAMPLE_ERROR);
    CheckErr(resultSong = al_create_sample_instance(sample), AL_CREATE_SAMPLE_INSTANCE_ERROR);
    CheckErr(al_set_sample_instance_playmode(resultSong, ALLEGRO_PLAYMODE_LOOP), AL_SET_SAMPLE_INSTANCE_PLAYMODE_ERROR);
    CheckErr(al_attach_sample_instance_to_mixer(resultSong, al_get_default_mixer()), AL_ATTACH_SAMPLE_INSTANCE_TO_MIXER_ERROR);

    // Load the playground
    CheckErr(background = al_load_bitmap("resource/img/background.png"), AL_LOAD_BITMAP_ERROR);

    // Load the title font
    CheckErr(scoreFont = al_load_ttf_font("resource/font/pirulen.ttf", 50, 0), AL_LOAD_TTF_FONT_ERROR);

    // Load button font and initialize the buttons
    CheckErr(buttonFont = al_load_ttf_font("resource/font/pirulen.ttf", 35, 0), AL_LOAD_TTF_FONT_ERROR);
    restartButton = Button{"Restart",
                WIDTH / 2, HEIGHT / 2 - 30,
                WIDTH / 2 - 120, HEIGHT / 2 - 30, WIDTH / 2 + 120, HEIGHT / 2 + 10};
    backButton = Button{"Back",
                WIDTH / 2, HEIGHT / 2 + 40,
                WIDTH / 2 - 120, HEIGHT / 2 + 40, WIDTH / 2 + 120, HEIGHT / 2 + 80};
}

ResultWindow::~ResultWindow(void)
{
    if(sample) al_destroy_sample(sample);
    if(resultSong) al_destroy_sample_instance(resultSong);
    if(background) al_destroy_bitmap(background);
    if(scoreFont) al_destroy_font(scoreFont);
    if(buttonFont) al_destroy_font(buttonFont);
}

void ResultWindow::Draw(int score)
{
    // Draw the background
    al_draw_bitmap(background, 0, 0, 0);

    // Draw the score
    char str[50];
    sprintf(str, "Your Score is %d", score);
    al_draw_text(scoreFont, al_map_rgb(102, 34, 0), WIDTH / 2, HEIGHT / 2 - 180,
                    ALLEGRO_ALIGN_CENTER, str);

    // Draw the button
    DrawButton(&restartButton);
    DrawButton(&backButton);

    // Show
    al_flip_display();
}

void ResultWindow::DrawButton(Button* btn)
{
    // Draw rectangle
    al_draw_rectangle(btn->x1, btn->y1, btn->x2, btn->y2, BLACK, 3);
    // Draw button text
    al_draw_text(buttonFont, BLACK, btn->text_x1, btn->text_y1, ALLEGRO_ALIGN_CENTER, btn->text);
}

void ResultWindow::Init(void)
{
    CheckErr(al_play_sample_instance(resultSong), AL_PLAY_SAMPLE_INSTANCE_ERROR);
}

void ResultWindow::Fini(void)
{
    CheckErr(al_stop_sample_instance(resultSong), AL_STOP_SAMPLE_INSTANCE_ERROR);
}

SelectedButton ResultWindow::GetBtn(int mouse_x, int mouse_y)
{
    if(mouse_x >= restartButton.x1 && mouse_x <= restartButton.x2 &&
       mouse_y >= restartButton.y1 && mouse_y <= restartButton.y2)
        return RestartBtn;
    else if(mouse_x >= backButton.x1 && mouse_x <= backButton.x2 &&
       mouse_y >= backButton.y1 && mouse_y <= backButton.y2)
        return BackBtn;
    return NullBtn;
}
