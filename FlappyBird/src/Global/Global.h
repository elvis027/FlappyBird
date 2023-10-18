#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <cstdio>
#include <cstdlib>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define TITLE "I2P2 Final Project Group7"
#define WIDTH 700
#define HEIGHT 896
#define FPS 60.0F

#define BLACK al_map_rgb(0, 0, 0)
#define WHITE al_map_rgb(255, 255, 255)

#define G 400.0F
#define H -4000.0F

// Message
typedef enum
{
    // Game Message
    GAME_CONTINUE,
    GAME_TERMINATE,

    // Error Message
    // Init and Create Error
    AL_INIT_ERROR,
    AL_INSTALL_AUDIO_ERROR,
    AL_INIT_ACODEC_ADDON_ERROR,
    AL_RESERVE_SAMPLES_ERROR,
    AL_CREATE_SAMPLE_INSTANCE_ERROR,
    AL_SET_SAMPLE_INSTANCE_PLAYMODE_ERROR,
    AL_ATTACH_SAMPLE_INSTANCE_TO_MIXER_ERROR,
    AL_INIT_PRIMITIVES_ADDON_ERROR,
    AL_INSTALL_KEYBOARD_ERROR,
    AL_INSTALL_MOUSE_ERROR,
    AL_INIT_IMAGE_ADDON_ERROR,
    AL_INIT_FONT_ADDON_ERROR,
    AL_INIT_TTF_ADDON_ERROR,
    AL_CREATE_DISPLAY_ERROR,
    AL_CREATE_EVENT_QUEUE_ERROR,
    AL_CREATE_TIMER_ERROR,
    // Load and Play Error
    AL_LOAD_SAMPLE_ERROR,
    AL_PLAY_SAMPLE_ERROR,
    AL_PLAY_SAMPLE_INSTANCE_ERROR,
    AL_STOP_SAMPLE_INSTANCE_ERROR,
    AL_LOAD_TTF_FONT_ERROR,
    AL_LOAD_BITMAP_ERROR,

    // Switch Window Message
    GOTO_MENU_WINDOW,
    GOTO_GAME_WINDOW,
    GOTO_RESULT_WINDOW,
    GOTO_ABOUT_WINDOW
} Message;

const char MsgToStr[][40] = {
    // Game Message
    "GAME_CONTINUE",
    "GAME_TERMINATE",

    // Error Message
    // Init and Create Error
    "AL_INIT_ERROR",
    "AL_INSTALL_AUDIO_ERROR",
    "AL_INIT_ACODEC_ADDON_ERROR",
    "AL_RESERVE_SAMPLES_ERROR",
    "AL_INIT_PRIMITIVES_ADDON_ERROR",
    "AL_INSTALL_KEYBOARD_ERROR",
    "AL_INSTALL_MOUSE_ERROR",
    "AL_INIT_IMAGE_ADDON_ERROR",
    "AL_INIT_FONT_ADDON_ERROR",
    "AL_INIT_TTF_ADDON_ERROR",
    "AL_CREATE_DISPLAY_ERROR",
    "AL_CREATE_EVENT_QUEUE_ERROR",
    "AL_CREATE_TIMER_ERROR",
    // Load and Play Error
    "AL_LOAD_SAMPLE_ERROR",
    "AL_PLAY_SAMPLE_ERROR",
    "AL_LOAD_TTF_FONT_ERROR",
    "AL_LOAD_BITMAP_ERROR",

    // Switch Window Message
    "GOTO_MENU_WINDOW",
    "GOTO_GAME_WINDOW",
    "GOTO_RESULT_WINDOW",
    "GOTO_ABOUT_WINDOW"
};

// Window
typedef enum
{
    MENU_WINDOW,
    GAME_WINDOW,
    RESULT_WINDOW,
    ABOUT_WINDOW
} Window;

// SelectedButton
typedef enum
{
    StartBtn,
    AboutBtn,
    ExitBtn,
    RestartBtn,
    BackBtn,
    NullBtn
} SelectedButton;

// Button
typedef struct
{
    char text[15];
    float text_x1, text_y1;  // position of text
    float x1, y1, x2, y2;  // position of rectangle
} Button;

typedef struct
{
    float x, y;
    float width, height;
} Rect;

typedef enum
{
    NotPass,
    Passed,
    Dumped
} PipeState;

void CheckErr(bool done, Message msg);

#endif // GLOBAL_H_INCLUDED
