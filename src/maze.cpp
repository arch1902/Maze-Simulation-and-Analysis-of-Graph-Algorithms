#include "maze.hpp"
#include <math.h>
#include <stdlib.h>
#include <string>
#include <queue>
#include "global.hpp"
#include "image.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include "mazegenerator.hpp"
using namespace std;
string s;
Point Steiner[6];


maze_state char_to_maze_state(const char c) {
  switch (c) {
    case '#':
      return maze_state::block;
    case 'C':
      return maze_state::counter_food;
    case '.':
      return maze_state::food;
    default:
      cerr << "error:"<<c <<" undefined character of maze" << '\n';
      exit(EXIT_FAILURE);
  }
}

void Maze::init()  {
    s = generator();
    int c = 0;
    for (int y = 0; y < 24; ++y) {
      for (int x = 0; x < 24; ++x) {
        block_[y][x] = char_to_maze_state(s[y * 24 + x]);
        if (block_[y][x] == maze_state::counter_food){
          Steiner[c] = Point{x,y};
          c+=1;
        }
      }
    }
  const string block_src = s;
}

void Maze::draw() const  {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);

  SDL_Texture *p_texture = nullptr;
  const unsigned int mod = 1;
  if (mod == 1) {
    p_texture = image_manager_->get(2);
  }
  {
    const SDL_Rect src[2] = {{0, 0, 20, 20},{20, 0, 20, 20}};
    for ( int y = 0; y < 24; ++y) {
      for ( int x = 0; x < 24; ++x) {
        const SDL_Rect dst = {(20 * x),(20 * y), 20, 20};
        switch (block_[y][x]) {
          case maze_state::counter_food:
            image_manager_->render_copy(*p_texture, src[0], dst);
            break;
          case maze_state::block:
            image_manager_->render_copy(*p_texture, src[1], dst);
            break;
        }
      }
    }
  }
  {
    const SDL_Rect src = {20, 20, 20,20 / 2};
    for ( int y = 0; y < 24 - 1; ++y) {
      for ( int x = 0; x < 24; ++x) {
        const maze_state block = block_[y][x];
        maze_state mut_under_block = block_[y + 1][x];
        switch (mut_under_block) {
          case maze_state::counter_food:
            mut_under_block = maze_state::food;
            break;
          default:
            break;
        }
        const maze_state under_block = mut_under_block;
        if ((block == maze_state::block) && (under_block == maze_state::food)) {
          const SDL_Rect dst = {(20 * x),(20 * y + 20 / 2),20,20};
          image_manager_->render_copy(*p_texture, src, dst);
        }
      }
    }
  }
  SDL_DestroyTexture(p_texture);
}
