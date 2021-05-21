#pragma once

#include <SDL2/SDL_mixer.h>
#include "global.hpp"
#include "image.hpp"
#include "maze.hpp"
#include "mixer.hpp"


class Food {
  enum class food_state {
    nothing,
    food,
    counter_food,
  };

  food_state food_[24][24];
  const ImageManager *image_manager_;
  const MixerManager *mixer_manager_;

 public:
  Food(const ImageManager *image_manager, const MixerManager *mixer_manager) 
      : image_manager_(image_manager), mixer_manager_(mixer_manager) {}

   void init(const Maze &maze)  {
    for (int y = 0; y < 24; ++y) {
      for (int x = 0; x < 24; ++x) {
        switch (maze.check_state(Point{x, y})) {
          case maze_state::food:
            food_[y][x] = food_state::food;
            break;
          case maze_state::counter_food:
            food_[y][x] = food_state::counter_food;
            break;
          default:
            food_[y][x] = food_state::nothing;
            break;
        }
      }
    }
  }

   void draw()  {
    const SDL_Rect src = {0, 0, 20, 20};
    SDL_Texture *food_texture = image_manager_->get(6);
    SDL_Texture *food_counter_texture = image_manager_->get(7);
    for (int y = 0; y < 24; ++y) {
      for (int x = 0; x < 24; ++x) {
        SDL_Rect dst;
        dst.x = (20 * x);
        dst.y = (20 * y);
        switch (food_[y][x]) {
          case food_state::food: {
            break;
          }
          case food_state::counter_food: {
            SDL_QueryTexture(food_counter_texture, nullptr, nullptr, &dst.w, &dst.h);
            image_manager_->render_copy(*food_counter_texture, src, dst);
            break;
          }
          default:
            break;
        }
      }
    }
    SDL_DestroyTexture(food_texture);
    SDL_DestroyTexture(food_counter_texture);
  }



  ~Food()  {}
};
