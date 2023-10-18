#include "MenuWindow.h"

MenuWindow::MenuWindow(void)
{
    // Load the song
    CheckErr(sample = al_load_sample("resource/audio/game.mp3"), AL_LOAD_SAMPLE_ERROR);
    CheckErr(menuSong = al_create_sample_instance(sample), AL_CREATE_SAMPLE_INSTANCE_ERROR);
    CheckErr(al_set_sample_instance_playmode(menuSong, ALLEGRO_PLAYMODE_LOOP), AL_SET_SAMPLE_INSTANCE_PLAYMODE_ERROR);
    CheckErr(al_attach_sample_instance_to_mixer(menuSong, al_get_default_mixer()), AL_ATTACH_SAMPLE_INSTANCE_TO_MIXER_ERROR);

    // Load the playground
    CheckErr(background = al_load_bitmap("resource/img/background.png"), AL_LOAD_BITMAP_ERROR);

    // Load the title font
    CheckErr(titleFont = al_load_ttf_font("resource/font/pirulen.ttf", 50, 0), AL_LOAD_TTF_FONT_ERROR);

    // Load button font and initialize the buttons
    CheckErr(buttonFont = al_load_ttf_font("resource/font/pirulen.ttf", 35, 0), AL_LOAD_TTF_FONT_ERROR);
    startButton = Button{"Start",
                WIDTH / 2, HEIGHT / 2 - 30,
                WIDTH / 2 - 100, HEIGHT / 2 - 30, WIDTH / 2 + 100, HEIGHT / 2 + 10};
    aboutButton = Button{"About",
                WIDTH / 2, HEIGHT / 2 + 40,
                WIDTH / 2 - 100, HEIGHT / 2 + 40, WIDTH / 2 + 100, HEIGHT / 2 + 80};
    exitButton = Button{"Exit",
                WIDTH / 2, HEIGHT / 2 + 110,
                WIDTH / 2 - 100, HEIGHT / 2 + 110, WIDTH / 2 + 100, HEIGHT / 2 + 150};
}

MenuWindow::~MenuWindow(void)
{
    if(sample) al_destroy_sample(sample);
    if(menuSong) al_destroy_sample_instance(menuSong);
    if(background) al_destroy_bitmap(background);
    if(titleFont) al_destroy_font(titleFont);
    if(buttonFont) al_destroy_font(buttonFont);
}

void MenuWindow::Draw(void)
{
    // Draw the background
    al_draw_bitmap(background, 0, 0, 0);

    // Draw the title
    al_draw_text(titleFont, al_map_rgb(102, 34, 0), WIDTH / 2, HEIGHT / 2 - 180,
                    ALLEGRO_ALIGN_CENTER, "Super Mary Bird");

    // Draw the button
    DrawButton(&startButton);
    DrawButton(&aboutButton);
    DrawButton(&exitButton);

    // Show
    al_flip_display();
}

void MenuWindow::DrawButton(Button* btn)
{
    // Draw rectangle
    al_draw_rectangle(btn->x1, btn->y1, btn->x2, btn->y2, BLACK, 3);
    // Draw button text
    al_draw_text(buttonFont, BLACK, btn->text_x1, btn->text_y1, ALLEGRO_ALIGN_CENTER, btn->text);
}

void MenuWindow::Init(void)
{
    CheckErr(al_play_sample_instance(menuSong), AL_PLAY_SAMPLE_INSTANCE_ERROR);
}

void MenuWindow::Fini(void)
{
    CheckErr(al_stop_sample_instance(menuSong), AL_STOP_SAMPLE_INSTANCE_ERROR);
}

SelectedButton MenuWindow::GetBtn(int mouse_x, int mouse_y)
{
    if(mouse_x >= startButton.x1 && mouse_x <= startButton.x2 &&
       mouse_y >= startButton.y1 && mouse_y <= startButton.y2)
        return StartBtn;
    else if(mouse_x >= aboutButton.x1 && mouse_x <= aboutButton.x2 &&
       mouse_y >= aboutButton.y1 && mouse_y <= aboutButton.y2)
        return AboutBtn;
    else if(mouse_x >= exitButton.x1 && mouse_x <= exitButton.x2 &&
       mouse_y >= exitButton.y1 && mouse_y <= exitButton.y2)
        return ExitBtn;
    return NullBtn;
}
