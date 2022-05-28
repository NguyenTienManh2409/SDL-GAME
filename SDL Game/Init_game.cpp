#include "init_game.h"

init_game::init_game() {
    isRunning = true;
    bullet_level = 0;
    kill = 0;
    scrolling = -(BACKGROUND_HEIGHT - SCREEN_HEIGHT);
    time_end_game = 0;
    count_num_exp = 0;
    menu_number = 0;
}
init_game::~init_game() {
}
void init_game::init(std::string title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        isRunning = false;
    }
    else {
        gWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            isRunning = false;
        }
        else {
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                isRunning = false;
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    isRunning = false;
                }
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    isRunning = false;
                }
                g_sound_bullet[0] = Mix_LoadWAV("sound//fatal.wav");
                g_sound_bullet[1] = Mix_LoadWAV("sound//lazer.wav");
                g_sound_bullet[2] = Mix_LoadWAV("sound//echo.wav");
                g_sound_exp[0] = Mix_LoadWAV("sound//explosion.wav");
                g_sound_chicken_hit[0] = Mix_LoadWAV("sound//Chicken1.wav");
                g_sound_chicken_hit[1] = Mix_LoadWAV("sound//Chicken2.wav");
                g_sound_chicken_hit[2] = Mix_LoadWAV("sound//Chicken3.wav");
                g_sound_level_up = Mix_LoadWAV("sound//level_up.wav");
                g_music_start = Mix_LoadMUS("sound//start.wav");

                if (g_sound_bullet[0] == NULL
                    || g_sound_bullet[1] == NULL
                    || g_sound_bullet[2] == NULL
                    || g_sound_exp[0] == NULL
                    || g_sound_chicken_hit[0] == NULL
                    || g_sound_chicken_hit[1] == NULL
                    || g_sound_chicken_hit[2] == NULL
                    || g_sound_level_up == NULL
                    || g_music_start == NULL) {
                    isRunning = false;
                }
                if (TTF_Init() < 0) {
                    isRunning = false;
                }
                g_font_text = TTF_OpenFont("font//font.ttf", 24);
                g_font_menu = TTF_OpenFont("font//font.ttf", 50);
                g_font_end_game = TTF_OpenFont("font//font.ttf", 100);
                if (g_font_text == NULL || g_font_menu == NULL || g_font_end_game == NULL) {
                    isRunning = false;
                }
            }
        }
    }

    //init background and main_object
    background.loadImg("image//background.png", gRenderer);
    spaceship.loadImg("image//spaceship.png", gRenderer);

    //boss
    boss.loadImg("image//boss.png", gRenderer);
    boss.set_clips();
    boss.SetRect(-WIDTH_BOSS, -HEIGHT_BOSS);
    boss.set_y_val(BOSS_SPEED);
    boss.set_x_val(BOSS_SPEED * 3);
    boss.set_heart(BOSS_HEART);
    bullet* p_bullet = new bullet();
    boss.InitBullet(p_bullet, gRenderer);

    //init chicken
    int t = 0;
    int y_row = 0;
    for (int c = 0; c < NUMBER_OF_CHICKEN; c++) {
        Chicken* p_chicken = new Chicken();
        if (p_chicken) {
            p_chicken->loadImg("image//chicken.png", gRenderer);
            p_chicken->set_clips();
            int rand_x = rand() % SCREEN_WIDTH; 
            p_chicken->SetRect(rand_x,0 - c * 200);
            p_chicken->set_y_val(CHICKEN_SPEED);
            p_chicken->set_x_val(CHICKEN_SPEED);
            p_chicken->set_heart(CHICKEN_HEART);
            int random = rand() % 10;
            if (random < 3) {
                bullet* p_bullet = new bullet();
                p_chicken->InitBullet(p_bullet, gRenderer);
            }
            p_chicken_list.push_back(p_chicken);
            t++;
        }
    }

    //init explosion
    exp.loadImg("image//exp.png", gRenderer);
    exp.set_clip();
    exp_boss.loadImg("image//exp.png", gRenderer);
    exp_boss.set_clip();
    gift.set_clip();

    //init taskbar
    taskbar.loadImg("image//taskbar.png", gRenderer);
    taskbar.SetRect(-20, 10);
    kill_text.SetColor(Text::WHITE);
    heart_text.SetColor(Text::WHITE);
    lighting_text.SetColor(Text::WHITE);
    hint.SetColor(Text::WHITE);
    end_game.SetColor(Text::WHITE);
    isRunning = true;
}
bool init_game::check_collision(const SDL_Rect& object1, const SDL_Rect& object2) { // kiểm tra sự va chạm 
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    if (left_a > right_b || right_a < left_b || top_a > bottom_b || bottom_a < top_b) {
        return false;
    }
    return true;
}

bool init_game::check_mouse_vs_item(const int& x, const int& y, const SDL_Rect& rect) {
    if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) {
        return true;
    }
    return false;
}

// init menu
void init_game::menu(const std::string& item) { 
    CommonFuntion menu;
    CommonFuntion menu2;
    if (!menu.loadImg("image//menu.png", gRenderer)) {
        isRunning = false;
        return;
    }
    if (!menu2.loadImg("image//menu2.png", gRenderer)) {
        isRunning = false;
        return;
    }

    const int number_of_item = 4;
    SDL_Rect pos_arr[number_of_item];
    Text text_menu[number_of_item];

    text_menu[0].SetText(item);
    text_menu[0].SetColor(Text::WHITE);
    text_menu[0].loadText_showText(g_font_menu, gRenderer);
    pos_arr[0].x = SCREEN_WIDTH / 2 - text_menu[0].GetRect().w / 2;
    pos_arr[0].y = SCREEN_HEIGHT - 250;
    text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

    text_menu[1].SetText("Information");
    text_menu[1].SetColor(Text::WHITE);
    text_menu[1].loadText_showText(g_font_menu, gRenderer);
    pos_arr[1].x = SCREEN_WIDTH / 2 - text_menu[1].GetRect().w / 2;
    pos_arr[1].y = SCREEN_HEIGHT - 175;
    text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

    text_menu[2].SetText("Exit");
    text_menu[2].SetColor(Text::WHITE);
    text_menu[2].loadText_showText(g_font_menu, gRenderer);
    pos_arr[2].x = SCREEN_WIDTH / 2 - text_menu[2].GetRect().w / 2;
    pos_arr[2].y = SCREEN_HEIGHT - 100;
    text_menu[2].SetRect(pos_arr[2].x, pos_arr[2].y);

    text_menu[3].SetText("Return");
    text_menu[3].SetColor(Text::WHITE);
    text_menu[3].loadText_showText(g_font_menu, gRenderer);
    pos_arr[3].x = 10;
    pos_arr[3].y = 10;
    text_menu[3].SetRect(pos_arr[3].x, pos_arr[3].y);

    int xm = 0;
    int ym = 0;
    Mix_PlayMusic(g_music_start, -1);
    bool quit = true;
    while (quit) {
        if (menu_number == 0) {
            menu.Render(gRenderer);
            for (int i = 0; i < number_of_item - 1; i++) {
                text_menu[i].loadText_showText(g_font_menu, gRenderer);
            }
        }
        else if (menu_number == 1) {
            menu2.Render(gRenderer);
            text_menu[3].loadText_showText(g_font_menu, gRenderer);
        }
        while (SDL_PollEvent(&gEvent) != 0) {
            spaceship.Control(gEvent, gRenderer, g_sound_bullet, bullet_level, g_sound_level_up);
            if (gEvent.type == SDL_QUIT) {
                isRunning = false;
                quit = false;
            }
            else if (gEvent.type == SDL_MOUSEMOTION) {
                xm = gEvent.motion.x;
                ym = gEvent.motion.y;

                for (int i = 0; i < number_of_item; i++) {
                    if (check_mouse_vs_item(xm, ym, text_menu[i].GetRect())) { text_menu[i].SetColor(Text::BLACK); }
                    else { text_menu[i].SetColor(Text::WHITE); }
                }
            }
            if (gEvent.type == SDL_MOUSEBUTTONDOWN) {
                xm = gEvent.button.x;
                ym = gEvent.button.y;

                for (int i = 0; i < number_of_item; i++) {
                    if (menu_number == 0) {
                        if (check_mouse_vs_item(xm, ym, text_menu[i].GetRect())) {
                            if (i == 0) { isRunning = true; quit = false; }
                            else if (i == 1) { menu_number = 1; }
                            else if (i == 2) { isRunning = false; quit = false; }
                            Mix_PlayChannel(-1, g_sound_level_up, 0);
                        }
                    }
                    else if (menu_number == 1) {
                        if (check_mouse_vs_item(xm, ym, text_menu[3].GetRect())) {
                            menu_number = 0;
                            Mix_PlayChannel(-1, g_sound_level_up, 0);
                        }
                    }
                }
            }
        }
        SDL_RenderPresent(gRenderer);
    }
    Mix_PauseMusic();
}

// play again
void init_game::reset_game() {
    bullet_level = 0;
    kill = 0;
    count_num_exp = 0;
    scrolling = -(BACKGROUND_HEIGHT - SCREEN_HEIGHT);
    time_end_game = 0;
    spaceship.set_bul_type(FATAL);
    spaceship.SetRect(SCREEN_WIDTH / 2, SCREEN_HEIGHT - HEIGHT_MAIN);
    spaceship.set_status(true);
    spaceship.set_heart(CHICKEN_HEART);
    boss.SetRect(-WIDTH_BOSS, -HEIGHT_BOSS);
    boss.set_heart(BOSS_HEART);
    for (int i = 0; i < boss.get_bullet_list().size(); i++) {
        bullet* p_bullet = boss.get_bullet_list().at(i);
        if (p_bullet) {
            p_bullet->SetRect(boss.GetRect().x + WIDTH_BOSS / 2, boss.GetRect().y + HEIGHT_BOSS);
        }
    }
    int t = 0;
    for (int c = 0; c < NUMBER_OF_CHICKEN; c++) {
        Chicken* p_chicken = p_chicken_list.at(c);
        int rand_x = rand() % SCREEN_WIDTH;
        p_chicken->SetRect(rand_x, 0 - c * 150);
        p_chicken->set_heart(CHICKEN_HEART);
        p_chicken->set_status_right();
        t++;
        for (int i = 0; i < p_chicken->get_bullet_list().size(); i++) {
            bullet* p_bullet = p_chicken->get_bullet_list().at(i);
            if (p_bullet) {
                p_bullet->SetRect(p_chicken->GetRect().x + WIDTH_CHICKEN / 2 - p_bullet->GetRect().w / 2, p_chicken->GetRect().y + HEIGHT_CHICKEN);
            }
        }
    }
}
// event
void init_game::handle_event() {
    while (SDL_PollEvent(&gEvent)) {
        if (gEvent.type == SDL_QUIT) {
            isRunning = false;
        }
        spaceship.Control(gEvent, gRenderer, g_sound_bullet, bullet_level, g_sound_level_up);
    }
}

//boss
void init_game::handle_boss() { 
    if (kill >= TOTAL_CHICHKEN && boss.get_heart() >= 0) {
        boss.show_heart_boss(gRenderer, 420, 20, boss.get_heart(), 6);

        boss.Move();
        boss.Show(gRenderer);
        boss.MakeBullet(gRenderer);

        // kiểm tra sự va chạm của tàu với đạn của boss 
        bool Col1 = false;
        std::vector<bullet*> boss_bullet_list = boss.get_bullet_list();
        for (int b = 0; b < boss_bullet_list.size(); b++) {
            bullet* p_bullet = boss_bullet_list.at(b);
            if (p_bullet) {
                Col1 = check_collision(p_bullet->GetRect(), spaceship.GetRect());
            }
        }
        // kiểm tra sự va chạm của tàu với boss 
        bool Col2 = check_collision(spaceship.GetRect(), boss.GetRectFrame());
        if (Col1 || Col2) { //tạo explosion
            Mix_PlayChannel(-1, g_sound_exp[0], 0);
            int x_pos = (spaceship.GetRect().x + WIDTH_MAIN / 2) - WIDTH_FRAME_EXP / 2;
            int y_pos = (spaceship.GetRect().y + HEIGHT_MAIN / 2) - HEIGHT_FRAME_EXP / 2;
            exp.SetRect(x_pos, y_pos);
            exp.set_frame(0);

            spaceship.SetRect(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
            spaceship.set_status(false);
            spaceship.decrease_heart();
            if (spaceship.get_heart() >= 0) {
                bullet_level = bullet_level < 2 ? 0 : (bullet_level - 1);
            }
        }
        //kiểm tra sự va chạm của đạn của tàu với boss
        std::vector<bullet*> s_bullet_list = spaceship.get_bullet_list();
        for (int sb = 0; sb < s_bullet_list.size(); sb++) {
            bullet* p_bullet = s_bullet_list.at(sb);
            if (p_bullet != NULL) {
                bool Col3 = check_collision(p_bullet->GetRect(), boss.GetRectFrame());
                if (Col3) {
                    boss.Decrease((spaceship.get_bullet_damage()) + bullet_level * BULLET_DAMAGE_LEVEL_UP);
                    Mix_PlayChannel(-1, g_sound_chicken_hit[rand() % 2], 0);
                    spaceship.RemoveBullet(sb);

                    if (boss.get_heart() < 0) {
                        kill++;
                        //set exp
                        int x_pos = (boss.GetRect().x + WIDTH_BOSS / 2) - WIDTH_FRAME_EXP / 2;
                        int y_pos = (boss.GetRect().y + HEIGHT_BOSS / 2) - HEIGHT_FRAME_EXP / 2;
                        exp_boss.SetRect(x_pos, y_pos);
                        exp_boss.set_frame(0);
                        boss.SetRect(SCREEN_WIDTH / 2, -SCREEN_HEIGHT);
                        Mix_PlayChannel(-1, g_sound_exp[0], 0);
                    }
                }
            }
        }
    }
}

//chicken 
void init_game::handle_chicken() { 
    if (kill < TOTAL_CHICHKEN) {
        for (int ck = 0; ck < p_chicken_list.size(); ck++) {
            Chicken* p_chicken = p_chicken_list.at(ck);
            if (p_chicken) {
                p_chicken->Move();
                p_chicken->Show(gRenderer);
                p_chicken->HandleBullet(gRenderer);
            }

            //kiểm tra sự va chạm của tàu với đạn của chicken 
            bool Col1 = false;
            std::vector<bullet*> bullet_list = p_chicken->get_bullet_list();
            for (int b = 0; b < bullet_list.size(); b++) {
                bullet* p_bullet = bullet_list.at(b);
                if (p_bullet) {
                    Col1 = check_collision(p_bullet->GetRect(), spaceship.GetRect());
                    if (Col1 == true) {
                        p_chicken->RemoveBullet(b);
                        break;
                    }
                }
            }

            //kiểm tra sự va chạm của tàu với chicken 
            bool Col2 = check_collision(spaceship.GetRect(), p_chicken->GetRectFrame());
            if (Col1 || Col2) {
                Mix_PlayChannel(-1, g_sound_exp[0], 0);

                //set exp
                int x_pos = (spaceship.GetRect().x + WIDTH_MAIN / 2) - WIDTH_FRAME_EXP / 2;
                int y_pos = (spaceship.GetRect().y + HEIGHT_MAIN / 2) - HEIGHT_FRAME_EXP / 2;
                exp.SetRect(x_pos, y_pos);
                exp.set_frame(0);

                spaceship.SetRect(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
                spaceship.set_status(false);
                spaceship.decrease_heart();
                if (spaceship.get_heart() >= 0) {
                    bullet_level = bullet_level < 2 ? 0 : (bullet_level - 1);
                }
            }

            //kiểm tra sự va chạm của đạn của tàu với chicken 
            std::vector<bullet*> s_bullet_list = spaceship.get_bullet_list();
            for (int sb = 0; sb < s_bullet_list.size(); sb++) {
                bullet* p_bullet = s_bullet_list.at(sb);
                if (p_bullet != NULL) {
                    bool Col3 = check_collision(p_bullet->GetRect(), p_chicken->GetRectFrame());
                    if (Col3) {
                        p_chicken->Decrease((spaceship.get_bullet_damage()) + bullet_level * BULLET_DAMAGE_LEVEL_UP);
                        Mix_PlayChannel(-1, g_sound_chicken_hit[rand() % 2], 0);
                        spaceship.RemoveBullet(sb);

                        if (p_chicken->get_heart() <= 0) {
                            p_chicken->set_heart(CHICKEN_HEART);
                            kill++;
                            Mix_PlayChannel(-1, g_sound_chicken_hit[2], 0);

                            p_chicken->SetRect(p_chicken->GetRect().x, -3 * SCREEN_HEIGHT);
                            if (kill > TOTAL_CHICHKEN) {
                                p_chicken->set_come_back(false);
                            }

                            if (kill % ONE_TURN_GIFT == 0) { //trao gift khi tiêu diệt địch đến số lượng nhất định 
                                gift.set_gift_type(gift.random_gift());
                                gift.loadImgGift(gRenderer);
                                gift.set_y_val(GIFT_SPEED);
                                gift.SetRect((rand() % (SCREEN_WIDTH - 2 * GIFT_WIDTH) + GIFT_WIDTH), -GIFT_HEIGHT);
                                gift.set_come_back(true);
                            }
                        }
                    }
                }
            }
        }
    }
}
void init_game::handle_game() {
    SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
    SDL_RenderClear(gRenderer);

    // cuộn background 
    scrolling += SCREEN_SPEED;
    if (scrolling < 0) {
        background.Render(gRenderer);
        background.SetRect(0, scrolling);
    }
    else {
        background.Render(gRenderer);
        background.SetRect(0, 0);
    }

    //handle spaceship 
    spaceship.Move();
    spaceship.Show(gRenderer);
    spaceship.HandleBullet(gRenderer);

    //enemy
    handle_chicken();
    handle_boss();

    //show explosion 
    if (exp.get_frame() < NUMBER_OF_FRAME * 2) {
        exp.Show(gRenderer);
    }
    if (exp_boss.get_frame() < NUMBER_OF_FRAME * 2) {
        exp_boss.Show(gRenderer);
        if (exp_boss.get_frame() >= NUMBER_OF_FRAME * 2 && count_num_exp < NUMBER_OF_EXP) {
            Mix_PlayChannel(-1, g_sound_exp[0], 0);
            exp_boss.set_frame(0);
            count_num_exp++;
        }
    }

    //game over
    if (spaceship.get_heart() == 0) {
        if (time_end_game < 300) {
            time_end_game++;
            end_game.SetText("Game Over !");
            end_game.SetRect(310, SCREEN_HEIGHT / 5);
            end_game.loadText_showText(g_font_end_game, gRenderer);
        }
        else {
            menu("Play Again");
            reset_game();
        }
    }
    else {
        if (spaceship.get_status() == false) {
            hint.SetText("Press 'ENTER' to revive !");
            hint.SetRect(310, SCREEN_HEIGHT / 4);
            hint.loadText_showText(g_font_menu, gRenderer);
        }
    }
    // game win
    if (boss.get_heart() <= 0) {
        if (time_end_game < 300) {
            time_end_game++;
            end_game.SetText("Victory !");
            end_game.SetRect(310, SCREEN_HEIGHT / 5);
            end_game.loadText_showText(g_font_end_game, gRenderer);
        }
        else {
            menu("Play Again");
            reset_game();
        }
    }

    //handle gift
    gift.Move(SCREEN_WIDTH, SCREEN_HEIGHT);
    gift.Show(gRenderer);

    bool Col4 = check_collision(spaceship.GetRect(), gift.get_gift_type() < LEVEL_UP ? gift.GetRect() : gift.GetRectFrame());
    if (Col4) {
        gift.SetRect(-GIFT_WIDTH, -GIFT_HEIGHT);
        if (bullet_level < 3 && ((gift.get_gift_type() == spaceship.get_bul_type()) || gift.get_gift_type() == LEVEL_UP)) {
            bullet_level++;
        }
        Mix_PlayChannel(-1, g_sound_level_up, 0);
        if (gift.get_gift_type() < LEVEL_UP) {
            spaceship.set_bul_type(gift.get_gift_type());
        }

        gift.set_come_back(false);
    }

    // show taskbar
    taskbar.Render(gRenderer);
    heart_text.SetText(std::to_string(spaceship.get_heart()));
    heart_text.SetRect(195, 15);
    heart_text.loadText_showText(g_font_text, gRenderer);
    kill_text.SetText(std::to_string(kill));
    kill_text.SetRect(50, 15);
    kill_text.loadText_showText(g_font_text, gRenderer);
    lighting_text.SetText(std::to_string(bullet_level));
    lighting_text.SetRect(280, 15);
    lighting_text.loadText_showText(g_font_text, gRenderer);


    SDL_RenderPresent(gRenderer);
}
void init_game::clean() {
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    gWindow = NULL;
    gRenderer = NULL;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}
