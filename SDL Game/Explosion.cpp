#include "Explosion.h"

Explosion::Explosion() {
    frame_ = 16;
}
Explosion::~Explosion() {

}
void Explosion::set_clip() { // tạo ảnh động của vụ nổ 
    for (int i = 0; i < 4; i++) {
        clip_[i].x = i * WIDTH_FRAME_EXP;
        clip_[i].y = 0;
        clip_[i].w = WIDTH_FRAME_EXP;
        clip_[i].h = HEIGHT_FRAME_EXP;
    }
}

void Explosion::Show(SDL_Renderer* screen) { // load vụ nổ lên screen 
    frame_++;
    SDL_Rect renderQuad = { rect_.x ,rect_.y , WIDTH_FRAME_EXP ,HEIGHT_FRAME_EXP };
    SDL_RenderCopy(screen, object_, &clip_[frame_ / 2], &renderQuad);
}

