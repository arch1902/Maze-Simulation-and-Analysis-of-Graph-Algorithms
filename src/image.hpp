
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

using namespace std;


class ImageManager {
  vector<SDL_Surface *> images_;
  SDL_Renderer *renderer_;

   void load(const char *path, const unsigned char image_type)  {
    SDL_Surface *image = IMG_Load(path);
    if (!image) {
      cerr << "error: " << IMG_GetError() << '\n';
      exit(EXIT_FAILURE);
    }
    images_[image_type] = image;
  }

 public:
  ImageManager(SDL_Renderer *renderer)  : renderer_(renderer) {
    images_.reserve(16);

    const int flag = IMG_INIT_PNG;
    if ((IMG_Init(flag) & flag) != flag) {
      cerr << "error: " << IMG_GetError() << '\n';
      exit(EXIT_FAILURE);
    }

    load("./data/1.png", 0);
    load("./data/2.png", 1);
    load("./data/bg_green.png", 2);
    load("./data/bg_red.png", 3);
    load("./data/bg_green.png", 4);
    load("./data/bg_blue.png", 5);
    load("./data/Food1.png", 6);
    load("./data/fc.png", 7);
    load("./data/akabei.png", 8);
    load("./data/pinky.png", 9);
    load("./data/aosuke.png", 10);
    load("./data/guzuta.png", 11);
    load("./data/mon_run.png", 12);
    load("./data/plate3.png", 13);
    load("./data/bullet.png",14);
    load("./data/b1.png",15);
  }

   SDL_Texture *get(const unsigned char image_type) const  {
    return SDL_CreateTextureFromSurface(renderer_, images_[image_type]);
  }

   void render_copy(SDL_Texture &texture, const SDL_Rect &src,
                          const SDL_Rect &dst) const  {
    SDL_RenderCopy(renderer_, &texture, &src, &dst);
  }

  ~ImageManager()  { atexit(IMG_Quit); }
};
