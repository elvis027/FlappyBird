#include "AboutWindow.h"

AboutWindow::AboutWindow(void)
{
    // Load the background
    CheckErr(background = al_load_bitmap("resource/img/background.png"), AL_LOAD_BITMAP_ERROR);

    // Load the font
    CheckErr(titleFont = al_load_ttf_font("resource/font/pirulen.ttf", 40, 0), AL_LOAD_TTF_FONT_ERROR);
    CheckErr(textFont = al_load_ttf_font("resource/font/pirulen.ttf", 20, 0), AL_LOAD_TTF_FONT_ERROR);
}

AboutWindow::~AboutWindow(void)
{
    if(background) al_destroy_bitmap(background);
    if(titleFont) al_destroy_font(titleFont);
    if(textFont) al_destroy_font(textFont);
}

void AboutWindow::Draw(void)
{
    // Draw the background
    al_draw_bitmap(background, 0, 0, 0);

    // Draw text
    al_draw_text(titleFont, BLACK, WIDTH / 2, 100,
                    ALLEGRO_ALIGN_CENTER, "ABOUT");

    al_draw_text(textFont, BLACK, WIDTH / 2, 300,
                    ALLEGRO_ALIGN_CENTER, "That is an interesting bird game!");

    // Show
    al_flip_display();
}

void AboutWindow::Init(void)
{

}

void AboutWindow::Fini(void)
{

}
