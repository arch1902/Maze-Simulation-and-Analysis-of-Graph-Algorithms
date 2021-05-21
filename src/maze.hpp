#pragma once

#include "global.hpp"
#include "image.hpp"
extern string network_state;
extern int socket_;


enum class maze_state {
  block, // #
  counter_food, // C
  food
};

class Maze {
  SDL_Renderer *renderer_;
  const ImageManager *image_manager_;
  maze_state block_[24][24];
  int home_distance_[24][24];

 public:
  Maze(SDL_Renderer *renderer, const ImageManager *image_manager) 
      : renderer_(renderer), image_manager_(image_manager) {}

  void init() ;

  void draw() const ;

    maze_state check_state(const Point &p) const  {
    return block_[p.y][p.x];
  }

    maze_state check_state(const Point &&p) const  {
    return check_state(p);
  }

    int get_home_distance(const Point &p) const  {
    return home_distance_[p.y][p.x];
    }

    int get_home_distance(const Point &&p) const  {
    return get_home_distance(p);
  }
  ~Maze()  {}
};
