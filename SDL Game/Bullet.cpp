#include "bullet.h"

bullet::bullet() {
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    bullet_type_ = FATAL;
}
bullet::~bullet() {

}

void bullet::loadImgBullet(SDL_Renderer* screen, int bullet_level) { // Load các kiểu đạn của nhân vật chính 
    if (bullet_type_ == FATAL) {
        std::string fatal_str = "image//fatal" + std::to_string(bullet_level) + ".png";
        loadImg(fatal_str, screen);
    }
    else if (bullet_type_ == LAZER) {
        std::string lazer_str = "image//lazer" + std::to_string(bullet_level) + ".png";
        loadImg(lazer_str, screen);
    }
    else if (bullet_type_ == ECHO) {
        std::string echo_str = "image//echo" + std::to_string(bullet_level) + ".png";
        loadImg(echo_str, screen);
    }
}

void bullet::HandleMoveSpaceShipBullet() { // Di chuyển đạn cuả nhân vật chính 
    rect_.y += y_val_;
    if (rect_.y < -rect_.h) {
        is_move_ = false;
    }
}
void bullet::HandleMoveChickenBullet() { // Di chuyển đạn của kẻ địch 
    rect_.y += y_val_;
    if (rect_.y > SCREEN_HEIGHT) {
        is_move_ = false;
    }
}
void bullet::HandleMoveBossBullet(const int& x_border, const int& y_border) { // Di chuyển đạn của Boss
    rect_.y += y_val_;
    if (rect_.y > y_border) {
        is_move_ = false;
    }
}
