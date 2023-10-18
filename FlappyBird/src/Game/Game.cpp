#include "Game.h"

Game::Game(void)
{
    CheckErr(al_init(), AL_INIT_ERROR);
    CheckErr(al_install_audio(), AL_INSTALL_AUDIO_ERROR);
    CheckErr(al_init_acodec_addon(), AL_INIT_ACODEC_ADDON_ERROR);
    CheckErr(al_reserve_samples(3), AL_RESERVE_SAMPLES_ERROR);
    CheckErr(al_init_primitives_addon(), AL_INIT_PRIMITIVES_ADDON_ERROR);
    CheckErr(al_install_keyboard(), AL_INSTALL_KEYBOARD_ERROR);
    CheckErr(al_install_mouse(), AL_INSTALL_MOUSE_ERROR);
    CheckErr(al_init_image_addon(), AL_INIT_IMAGE_ADDON_ERROR);
    CheckErr(al_init_font_addon(), AL_INIT_FONT_ADDON_ERROR);
    CheckErr(al_init_ttf_addon(), AL_INIT_TTF_ADDON_ERROR);

    // Create display and event_queue
    CheckErr(display = al_create_display(WIDTH, HEIGHT), AL_CREATE_DISPLAY_ERROR);
    CheckErr(event_queue = al_create_event_queue(), AL_CREATE_EVENT_QUEUE_ERROR);

    // Initialize display settings
    al_set_window_position(display, 20, 10);
    al_set_window_title(display, TITLE);

    // Register event
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    // Initialize other windows
    menuWindow = new MenuWindow();
    aboutWindow = new AboutWindow();
    gameWindow = new GameWindow(event_queue);
    resultWindow = new ResultWindow();

    nowWindow = MENU_WINDOW;
    menuWindow->Init();
}

Game::~Game(void)
{
    // Environment
    if(display) al_destroy_display(display);
    if(event_queue) al_destroy_event_queue(event_queue);

    // Window
    if(menuWindow) delete menuWindow;
    if(aboutWindow) delete aboutWindow;
    if(gameWindow) delete gameWindow;
    if(resultWindow) delete resultWindow;
}

void Game::GamePlay(void)
{
    printf("Game Start...\n");

    Message msg = GAME_CONTINUE;

    while(msg != GAME_TERMINATE) {
        msg = GameRun();
    }

    printf("Game Over...\n");
}

Message Game::GameRun(void)
{
    Message msg = GAME_CONTINUE;

    if(nowWindow == MENU_WINDOW) {
        if(!al_is_event_queue_empty(event_queue)) {
            msg = ProcessEvent();
            menuWindow->Draw();
            if(msg == GOTO_GAME_WINDOW) {
                menuWindow->Fini();
                nowWindow = GAME_WINDOW;
                gameWindow->Init();
                gameWindow->Draw();
            }
            else if(msg == GOTO_ABOUT_WINDOW) {
                nowWindow = ABOUT_WINDOW;
                aboutWindow->Init();
                aboutWindow->Draw();
            }
        }
    }
    else if(nowWindow == GAME_WINDOW) {
        if(!al_is_event_queue_empty(event_queue)) {
            msg = ProcessEvent();
            gameWindow->Draw();
            if(msg == GOTO_RESULT_WINDOW) {
                gameWindow->Fini();
                nowWindow = RESULT_WINDOW;
                resultWindow->Init();
                resultWindow->Draw(gameWindow->GetScore());
            }
            else if(msg == GOTO_MENU_WINDOW) {
                gameWindow->Fini();
                nowWindow = MENU_WINDOW;
                menuWindow->Init();
                menuWindow->Draw();
            }
        }
    }
    else if(nowWindow == RESULT_WINDOW) {
        if(!al_is_event_queue_empty(event_queue)) {
            msg = ProcessEvent();
            resultWindow->Draw(gameWindow->GetScore());
            if(msg == GOTO_GAME_WINDOW) {
                resultWindow->Fini();
                nowWindow = GAME_WINDOW;
                gameWindow->Init();
                gameWindow->Draw();
            }
            else if(msg == GOTO_MENU_WINDOW) {
                resultWindow->Fini();
                nowWindow = MENU_WINDOW;
                menuWindow->Init();
                menuWindow->Draw();
            }
        }
    }
    else if(nowWindow == ABOUT_WINDOW) {
        if(!al_is_event_queue_empty(event_queue)) {
            msg = ProcessEvent();
            if(msg == GOTO_MENU_WINDOW) {
                aboutWindow->Fini();
                nowWindow = MENU_WINDOW;
                menuWindow->Draw();
            }
        }
    }

    return msg;
}

Message Game::ProcessEvent(void)
{
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);

    if(nowWindow == MENU_WINDOW) {
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(event.mouse.button == 1) {
                SelectedButton SelectedBtn = menuWindow->GetBtn(mouse_x, mouse_y);
                if(SelectedBtn == StartBtn)
                    return GOTO_GAME_WINDOW;
                else if(SelectedBtn == AboutBtn)
                    return GOTO_ABOUT_WINDOW;
                else if(SelectedBtn == ExitBtn)
                    return GAME_TERMINATE;
            }
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    return GAME_TERMINATE;
            }
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            return GAME_TERMINATE;
        }
    }
    else if(nowWindow == GAME_WINDOW) {
        if(event.type == ALLEGRO_EVENT_TIMER) {
            if(event.timer.source == gameWindow->GetTimer()) {
                if(gameWindow->isCollided())
                    return GOTO_RESULT_WINDOW;
                float deltaTime = 1.0 / FPS;
                gameWindow->UpdateBird(G, deltaTime);
                gameWindow->UpdatePipe(deltaTime);
            }
            else if(event.timer.source == gameWindow->GetBirdTimer()) {
                gameWindow->UpdateBirdState();
            }
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE: {
                    float deltaTime = 0.1;
                    gameWindow->UpdateBird(H, deltaTime);
                    break;
                }
                case ALLEGRO_KEY_ESCAPE:
                    return GOTO_MENU_WINDOW;
            }
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(event.mouse.button == 1) {
                float deltaTime = 0.1;
                gameWindow->UpdateBird(H, deltaTime);
            }
        }
        else if(event.type == ALLEGRO_EVENT_KEY_UP) {
            switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_SPACE:
                break;
            }
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            return GAME_TERMINATE;
        }
    }
    else if(nowWindow == RESULT_WINDOW) {
        if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(event.mouse.button == 1) {
                SelectedButton SelectedBtn = resultWindow->GetBtn(mouse_x, mouse_y);
                if(SelectedBtn == RestartBtn)
                    return GOTO_GAME_WINDOW;
                else if(SelectedBtn == BackBtn)
                    return GOTO_MENU_WINDOW;
            }
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouse_x = event.mouse.x;
            mouse_y = event.mouse.y;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    return GAME_TERMINATE;
            }
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            return GAME_TERMINATE;
        }
    }
    else if(nowWindow == ABOUT_WINDOW) {
        if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            return GOTO_MENU_WINDOW;
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            return GOTO_MENU_WINDOW;
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            return GAME_TERMINATE;
        }
    }

    return GAME_CONTINUE;
}
