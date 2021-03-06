#pragma once

#include "global.hpp"

class Wipe {
  enum class wipe_type { in, out };

  wipe_type wipe_variation_;
  unsigned int wipe_count_;
  unsigned int wipe_count_reach_;
  SDL_Renderer *renderer_;

 public:
  Wipe(SDL_Renderer *renderer)  : renderer_(renderer) {}

   void set_wipe_in()  {
    wipe_variation_ = wipe_type::in;
    wipe_count_ = 480 / 10;
    wipe_count_reach_ = 0;
  }

   void set_wipe_out()  {
    wipe_variation_ = wipe_type::out;
    wipe_count_ = 0;
    wipe_count_reach_ = 480 / 10;
  }

   void draw(const unsigned int limit_x) const  {
    SDL_Rect dst = {0, 0, static_cast<Uint16>(limit_x),static_cast<Uint16>(wipe_count_)};
    const unsigned int dy = 480 / 10;
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    for (dst.y = 0; dst.y < 480; dst.y += dy) {
      SDL_RenderFillRect(renderer_, &dst);
    }
  }

   bool update()  {
    if (wipe_count_ == wipe_count_reach_) {
      return true;
    }

    switch (wipe_variation_) {
      case wipe_type::in:
        wipe_count_--;
        break;
      case wipe_type::out:
        wipe_count_++;
        break;
    }
    return false;
  }

  ~Wipe()  {}
};
