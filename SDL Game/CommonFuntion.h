#ifndef COMMONFUNTION_H
#define COMMONFUNTION_H
#include "attributes.h"

class CommonFuntion {
public:
    CommonFuntion();
    ~CommonFuntion();

    void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; }
    SDL_Rect GetRect()const { return rect_; }
    bool loadImg(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* screen, const SDL_Rect* clip = NULL);
    void Clean();
protected:
    SDL_Rect rect_;
    SDL_Texture* object_;
};

#endif
